#include "../../GrammaticalParser.hpp"

#include "Test_BasicGrammatical.hpp"


Test_BasicGrammatical::Test_BasicGrammatical() : AbstractTest("Test_BasicGrammatical")
{
}

Test_BasicGrammatical::~Test_BasicGrammatical()
{
}

void Test_BasicGrammatical::run() noexcept
{
    std::vector<JSONWord::Type> input;

    input.push_back(JSONWord::Type::OBJECT_BEGIN);
    input.push_back(JSONWord::Type::STRING);
    input.push_back(JSONWord::Type::WHITESPACE);
    input.push_back(JSONWord::Type::COLON);
    input.push_back(JSONWord::Type::ARRAY_BEGIN);
    input.push_back(JSONWord::Type::NUMBER);
    input.push_back(JSONWord::Type::COMMA);
    input.push_back(JSONWord::Type::NUMBER);
    input.push_back(JSONWord::Type::COMMA);
    input.push_back(JSONWord::Type::STRING);
    input.push_back(JSONWord::Type::COMMA);
    input.push_back(JSONWord::Type::WHITESPACE);
    input.push_back(JSONWord::Type::OBJECT_BEGIN);
    input.push_back(JSONWord::Type::WHITESPACE);
    input.push_back(JSONWord::Type::OBJECT_END);
    input.push_back(JSONWord::Type::ARRAY_END);
    input.push_back(JSONWord::Type::OBJECT_END);

    try
    {
        GrammaticalParser::computeGrammaticalAnalysis(input);
    }
    catch (GrammaticalParser::grammatical_exception&)
    {
        std::cout << "NOK: Parsing is supposed to succeed, but failed instead" << std::endl;
        m_test_status = TestStatus::NOK;
        return;
    }
    catch (...)
    {
        std::cout << "NOK: Unknown error" << std::endl;
        m_test_status = TestStatus::NOK;
        return;
    }

    m_test_status = TestStatus::OK;
}
