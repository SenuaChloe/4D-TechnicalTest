#pragma once

#include <vector>

#include "JSONWord.hpp"


namespace LexicalParser
{
    // Exception thrown when there is a lexical error
    struct lexical_exception : public std::exception {};

    // Main function of the lexical parsing feature
    std::vector<JSONWord::Type> computeLexicalAnalysis(std::string json_input);

};

