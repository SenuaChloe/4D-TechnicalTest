#pragma once

#include <optional>
#include <string>

struct JSONWord
{
    // Types of JSON symbols & words
    enum class Type
    {
        OBJECT_BEGIN,
        OBJECT_END,
        ARRAY_BEGIN,
        ARRAY_END,
        STRING,
        NUMBER,
        TRUE,
        FALSE,
        NULL_VALUE,
        WHITESPACE,
        COMMA,
        COLON
    };

    Type type;
    std::optional<std::string> data; // Needed to check the numbers and constants

    // Constructor with empty data
    JSONWord(Type type) : type(type), data(std::nullopt) {}
    // Constructor with data
    JSONWord(Type type, std::string_view data) : type(type), data(data) {}
};

