#include "../../LexicalParser.hpp"
#include "../../JSONWord.hpp"

#include "Test_BasicLexical.hpp"


Test_BasicLexical::Test_BasicLexical() : AbstractTest("Test_BasicLexical")
{
}

Test_BasicLexical::~Test_BasicLexical()
{
}

void Test_BasicLexical::run() noexcept
{
    std::string input = "{\"test\" :[1,2.3e-15,\"foo\", {  }]}";
    std::vector<JSONWord::Type> expected_result, actual_result;

    expected_result.push_back(JSONWord::Type::OBJECT_BEGIN);
    expected_result.push_back(JSONWord::Type::STRING);
    expected_result.push_back(JSONWord::Type::WHITESPACE);
    expected_result.push_back(JSONWord::Type::COLON);
    expected_result.push_back(JSONWord::Type::ARRAY_BEGIN);
    expected_result.push_back(JSONWord::Type::NUMBER);
    expected_result.push_back(JSONWord::Type::COMMA);
    expected_result.push_back(JSONWord::Type::NUMBER);
    expected_result.push_back(JSONWord::Type::COMMA);
    expected_result.push_back(JSONWord::Type::STRING);
    expected_result.push_back(JSONWord::Type::COMMA);
    expected_result.push_back(JSONWord::Type::WHITESPACE);
    expected_result.push_back(JSONWord::Type::OBJECT_BEGIN);
    expected_result.push_back(JSONWord::Type::WHITESPACE);
    expected_result.push_back(JSONWord::Type::OBJECT_END);
    expected_result.push_back(JSONWord::Type::ARRAY_END);
    expected_result.push_back(JSONWord::Type::OBJECT_END);

    try
    {
        actual_result = LexicalParser::computeLexicalAnalysis(input);
    }
    catch (LexicalParser::lexical_exception&)
    {
        std::cout << "NOK: Parsing is supposed to succeed, but failed instead" << std::endl;
        m_test_status = TestStatus::NOK;
        return;
    }

    std::cerr << "== DUMP == (input)" << std::endl;
    std::cerr << input << std::endl;
    std::cerr << "== DUMP == (expected)" << std::endl;
    for (auto word : expected_result)
        std::cerr << static_cast<int>(word)  << " ";
    std::cerr << std::endl << "== DUMP == (actual)" << std::endl;
    for (auto word : actual_result)
        std::cerr << static_cast<int>(word) << " ";
    std::cerr << std::endl;

    if (expected_result.size() != actual_result.size())
    {
        std::cout << "NOK: Expected result and actual result have different sizes" << std::endl;
        m_test_status = TestStatus::NOK;
        return;
    }

    for (size_t i_res = 0 ; i_res < expected_result.size() ; ++i_res)
    {
        if (expected_result[i_res] != actual_result[i_res])
        {
            std::cout << "NOK: Expected result and actual result are different at index " << i_res << std::endl;
            m_test_status = TestStatus::NOK;
            return;
        }
    }

    m_test_status = TestStatus::OK;
}
