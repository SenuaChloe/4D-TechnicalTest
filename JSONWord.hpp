#pragma once

#include <optional>
#include <string>

struct JSONWord
{
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
    std::optional<std::string> data; // Needed to check the strings and constants

    JSONWord(Type type) : type(type), data(std::nullopt) {}
    JSONWord(Type type, std::string_view data) : type(type), data(data) {}
};

