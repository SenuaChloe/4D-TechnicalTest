#pragma once

#include <vector>

#include "JSONWord.hpp"


namespace GrammaticalParser
{
    struct grammatical_exception : std::exception {};

    void computeGrammaticalAnalysis(const std::vector<JSONWord::Type> & lexical_json_input) throw();

};

