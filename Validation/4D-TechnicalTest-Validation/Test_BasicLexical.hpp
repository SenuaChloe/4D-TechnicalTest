#pragma once

#include "AbstractTest.hpp"

// To activate a dump of the results (both expected and actual), define this macro
#undef ACTIVATE_DUMP

struct Test_BasicLexical : public AbstractTest
{
    Test_BasicLexical();
    ~Test_BasicLexical();
    void run() noexcept final;
};
