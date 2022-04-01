#include <algorithm>

#include "GrammaticalParser.hpp"


enum class ExpectationType
{
    VALUE,
    COMMA,
    COLON,
    WHITESPACE,
    STRING,
    OBJECT_END,
    ARRAY_END
};

enum class NestType
{
    OBJECT,
    OBJECT_COLON,
    ARRAY
};



using WT = JSONWord::Type;




// Auxiliary function to know if a syntax is expected or not
static bool expected(ExpectationType given_type, const std::vector<ExpectationType> & expectation_list)
{
    return std::find(begin(expectation_list), end(expectation_list), given_type) != end(expectation_list);
}

// Auxiliary function to know if the nest stack is consistent or not
static bool consistent_stack(NestType closing_entity, const std::vector<NestType> & nest_stack)
{
    if (nest_stack.size() == 0 || nest_stack.back() != closing_entity)
        return false;
    else
        return true;
}


// Auxiliary functions to build expectation lists
static std::vector<ExpectationType> make_expectation_list(ExpectationType type)
{
    std::vector<ExpectationType> result;
    result.push_back(type);
    return result;
}
template <typename... ExpectationTypes>
static std::vector<ExpectationType> make_expectation_list(ExpectationType head, ExpectationTypes... tail)
{
    std::vector<ExpectationType> result = make_expectation_list(tail...);
    result.push_back(head);
    return result;
}


// AUxiliary function that looks at the environment to know which entity is expected nes
static std::vector<ExpectationType> rebuild_expectation_list(const std::vector<NestType> & nest_stack)
{
    if (nest_stack.size() == 0)
        return std::vector<ExpectationType>();
    else if (nest_stack.back() == NestType::ARRAY)
        return make_expectation_list(ExpectationType::ARRAY_END, ExpectationType::COMMA, ExpectationType::WHITESPACE);
    else if (nest_stack.back() == NestType::OBJECT_COLON)
        return make_expectation_list(ExpectationType::OBJECT_END, ExpectationType::WHITESPACE);
    else // NestType::OBJECT
        return make_expectation_list(ExpectationType::COLON, ExpectationType::WHITESPACE, ExpectationType::OBJECT_END);
}


void GrammaticalParser::computeGrammaticalAnalysis(const std::vector<WT> & lexical_json_input)
{
    if (lexical_json_input.size() == 0)
        return;

    std::vector<NestType> nest_stack;
    std::vector<ExpectationType> expectation_list;

    // Initial expectartion is value
    expectation_list.push_back(ExpectationType::VALUE);

    for (auto current_word : lexical_json_input)
    {
        switch (current_word)
        {

        case WT::OBJECT_BEGIN:
            if (!expected(ExpectationType::VALUE, expectation_list))
                throw grammatical_exception();
            nest_stack.push_back(NestType::OBJECT);
            expectation_list = make_expectation_list(ExpectationType::WHITESPACE, ExpectationType::STRING, ExpectationType::OBJECT_END);
            break;


        case WT::OBJECT_END:
            if (!expected(ExpectationType::OBJECT_END, expectation_list))
                throw grammatical_exception();
            if (!consistent_stack(NestType::OBJECT, nest_stack) && !consistent_stack(NestType::OBJECT_COLON, nest_stack))
                throw grammatical_exception();
            if (nest_stack.back() == NestType::OBJECT_COLON)
            {
                nest_stack.pop_back();
                if (!consistent_stack(NestType::OBJECT, nest_stack))
                    throw grammatical_exception();
            }
            nest_stack.pop_back();
            expectation_list = rebuild_expectation_list(nest_stack);
            break;


        case WT::ARRAY_BEGIN:
            if (!expected(ExpectationType::VALUE, expectation_list))
                throw grammatical_exception();
            nest_stack.push_back(NestType::ARRAY);
            expectation_list = make_expectation_list(ExpectationType::WHITESPACE, ExpectationType::VALUE, ExpectationType::ARRAY_END);
            break;


        case WT::ARRAY_END:
            if (!expected(ExpectationType::ARRAY_END, expectation_list))
                throw grammatical_exception();
            if (!consistent_stack(NestType::ARRAY, nest_stack))
                throw grammatical_exception();
            nest_stack.pop_back();
            expectation_list = rebuild_expectation_list(nest_stack);
            break;


        case WT::NUMBER:
        case WT::TRUE:
        case WT::FALSE:
        case WT::NULL_VALUE:
            if (!expected(ExpectationType::VALUE, expectation_list))
                throw grammatical_exception();
            expectation_list = rebuild_expectation_list(nest_stack);
            break;


        case WT::STRING:
            if (!expected(ExpectationType::VALUE, expectation_list) && !expected(ExpectationType::STRING, expectation_list))
                throw grammatical_exception();
            expectation_list = rebuild_expectation_list(nest_stack);
            break;


        case WT::WHITESPACE:
            if (!expected(ExpectationType::WHITESPACE, expectation_list))
                throw grammatical_exception();
            // Technically we COULD allow double whitespace, but this has no impact (imposible for the lexical parser)
            break;

        case WT::COMMA:
            if (!expected(ExpectationType::COMMA, expectation_list))
                throw grammatical_exception();
            expectation_list = make_expectation_list(ExpectationType::VALUE, ExpectationType::WHITESPACE);
            break;


        case WT::COLON:
            if (!expected(ExpectationType::COLON, expectation_list))
                throw grammatical_exception();
            expectation_list = make_expectation_list(ExpectationType::VALUE);
            break;
        }
    }
    if (!expectation_list.empty())
        throw grammatical_exception();
}
