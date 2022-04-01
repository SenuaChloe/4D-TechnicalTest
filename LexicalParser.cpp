#include "LexicalParser.hpp"

#include <optional>
#include <algorithm>




using WT = JSONWord::Type;


// Auxiliary function to check constants, save current word, and RAZ word current word data
static void save_current_word(std::vector<JSONWord> & result, std::optional<WT> & current_word_type, std::string & current_word)
{
    // Checking constant values in case they are incomplete
    if (   (current_word_type == WT::TRUE && current_word != "true")
        || (current_word_type == WT::FALSE && current_word != "false")
        || (current_word_type == WT::NULL_VALUE && current_word != "null") )
            throw LexicalParser::lexical_exception();

    if (current_word_type)
    {
        result.push_back(JSONWord(*current_word_type, current_word));
        current_word_type = std::nullopt;
    }
    current_word = "";
}



// Parsing auxiliary functions
static void parse_simple_symbol(std::vector<JSONWord> & result, std::optional<WT> & current_word_type, std::string & current_word, WT actual_type);
static void parse_string(std::vector<JSONWord> & result, std::optional<WT> & current_word_type, std::string & current_word);
static void parse_whitespace(std::vector<JSONWord> & result, char c, std::optional<WT> & current_word_type, std::string & current_word);
static void parse_other(std::vector<JSONWord> & result, char c, std::optional<WT> & current_word_type, std::string & current_word);



// Mais function of the parser
std::vector<WT> LexicalParser::computeLexicalAnalysis(std::string json_input)
{
    std::vector<JSONWord> aux_result;

    std::optional<WT> current_word_type;
    std::string current_word;

    for (char c : json_input)
    {
        if (current_word_type == WT::STRING && c != '"')
        {
            current_word += c;
        }
        else
        {
            switch (c)
            {
            case '{':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::OBJECT_BEGIN);
                break;

            case '}':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::OBJECT_END);
                break;

            case '[':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::ARRAY_BEGIN);
                break;

            case ']':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::ARRAY_END);
                break;

            case ',':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::COMMA);
                break;

            case ':':
                parse_simple_symbol(aux_result, current_word_type, current_word, WT::COLON);
                break;

            case '"':
                parse_string(aux_result, current_word_type, current_word);
                break;

            // WHITESPACE
            case ' ':
            case '\t':
            case '\s':
            case '\n':
            case '\r':
                parse_whitespace(aux_result, c, current_word_type, current_word);
                break;

            // Other characters (for NUMBERs and constants)
            default:
                parse_other(aux_result, c, current_word_type, current_word);
            }
        }
    }


    // TODO Reparsing NUMBERs in order to detect inconsistencies

    std::vector<WT> result(aux_result.size());
    std::transform(begin(aux_result), end(aux_result), begin(result), [](const JSONWord & word){ return word.type; });
    return std::move(result);
}


// Parses a simple symbol that contains no data
void parse_simple_symbol(std::vector<JSONWord> & result, std::optional<WT> & current_word_type, std::string & current_word, WT actual_type)
{
    save_current_word(result, current_word_type, current_word);
    result.push_back(JSONWord(actual_type));
}


// Parses the beginning of the end of a STRING
void parse_string(std::vector<JSONWord> & result, std::optional<WT> & current_word_type, std::string & current_word)
{
    if (current_word_type == WT::STRING)
    {
        save_current_word(result, current_word_type, current_word);
    }
    else
    {
        save_current_word(result, current_word_type, current_word);
        current_word_type = WT::STRING;
    }
}


// Parse a set of whitespaces
void parse_whitespace(std::vector<JSONWord> & result, char c, std::optional<WT> & current_word_type, std::string & current_word)
{
    if (current_word_type != WT::WHITESPACE)
    {
        save_current_word(result, current_word_type, current_word);
        current_word_type = WT::WHITESPACE;
    }
    current_word += c;
}



// Parses any other value (i.e. numbers or constant such as true, false and null)
void parse_other(std::vector<JSONWord> & result, char c, std::optional<WT> & current_word_type, std::string & current_word)
{
    switch (*current_word_type)
    {
    // Middle of a NUMBER
    case WT::NUMBER:
        if ( (c < '0' || c > '9') && c != '.' && c != 'e' && c != 'E' && c != '-' && c != '+' )
            throw LexicalParser::lexical_exception();
        break;

    // Middle of TRUE
    case WT::TRUE:
        if (       !(c == 'r' && current_word == "t")
                && !(c == 'u' && current_word == "tr")
                && !(c == 'e' && current_word == "tru") )
            throw LexicalParser::lexical_exception();
        current_word += c;
        if (current_word == "true")
            save_current_word(result, current_word_type, current_word);
        break;

    // Middle of FALSE
    case WT::FALSE:
        if (       !(c == 'a' && current_word == "f")
                && !(c == 'l' && current_word == "fa")
                && !(c == 's' && current_word == "fal")
                && !(c == 'e' && current_word == "fals") )
            throw LexicalParser::lexical_exception();
        current_word += c;
        if (current_word == "false")
            save_current_word(result, current_word_type, current_word);
        break;

    // Middle of NULL
    case WT::NULL_VALUE:
        if ( !(c == 'u' && current_word == "n") && !(c == 'l' && ( current_word == "nu" || current_word == "nul") ) )
            throw LexicalParser::lexical_exception();
        current_word += c;
        if (current_word == "null")
            save_current_word(result, current_word_type, current_word);
        break;

    default:
        // Forcing new word
        save_current_word(result, current_word_type, current_word);

        current_word += c;

        // Beginning of a number
        if ( (c >= '0' && c <= '9') || c == '-' )
            current_word_type = WT::NUMBER;
        // Beginning of a true
        else if (c == 't')
            current_word_type = WT::TRUE;
        // Beginning of a false
        else if (c == 'f')
            current_word_type = WT::FALSE;
        // Beginning of a null
        else if (c == 'n')
            current_word_type = WT::NULL_VALUE;
        else
            throw LexicalParser::lexical_exception();
    }
}

