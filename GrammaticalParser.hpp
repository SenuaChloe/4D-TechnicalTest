#pragma once

#include <vector>

#include "JSONWord.hpp"


namespace GrammaticalParser
{
    // Exception thrown when there is a grammatical error
    struct grammatical_exception : public std::exception {};

    // Main function of the grammatical parsing feature
    void computeGrammaticalAnalysis(const std::vector<JSONWord::Type> & lexical_json_input);

};

