#pragma once

#include <vector>

#include "JSONWord.hpp"


namespace LexicalParser
{
    struct lexical_exception : std::exception {};

    std::vector<JSONWord> computeLexicalAnalysis(std::string json_input) throw();

};

