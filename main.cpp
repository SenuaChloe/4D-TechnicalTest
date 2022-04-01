#include <iostream>
#include <string>

#include "LexicalParser.hpp"
#include "GrammaticalParser.hpp"

int main(int argc, char *argv[])
{
    std::string json_input;

    for (int i_arg = 1 ; i_arg < argc ; ++i_arg)
        json_input += argv[i_arg];

    auto lexical_json_input = LexicalParser::computeLexicalAnalysis(json_input);
    GrammaticalParser::computeGrammaticalAnalysis(lexical_json_input);

    std::cout << "Parsing complete : input is a valid JSON object" << std::endl;
    return 0;
}
