#include <iostream>
#include <string>

#include "LexicalParser.hpp"
#include "GrammaticalParser.hpp"

int main(int argc, char *argv[])
{
    std::string json_input;

    for (int i_arg = 1 ; i_arg < argc ; ++i_arg)
        json_input += argv[i_arg];

    try
    {
    auto lexical_json_input = LexicalParser::computeLexicalAnalysis(json_input);
    GrammaticalParser::computeGrammaticalAnalysis(lexical_json_input);
    }
    catch (LexicalParser::lexical_exception&)
    {
        std::cout << "Parsing failed: lexical error" << std::endl;
        return 1;
    }
    catch (GrammaticalParser::grammatical_exception&)
    {
        std::cout << "Parsing failed: grammatical error" << std::endl;
        return 2;
    }

    std::cout << "Parsing complete : input is a valid JSON object" << std::endl;
    return 0;
}
