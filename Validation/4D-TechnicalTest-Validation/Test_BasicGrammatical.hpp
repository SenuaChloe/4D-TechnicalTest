#pragma once

#include "AbstractTest.hpp"


struct Test_BasicGrammatical : public AbstractTest
{
    Test_BasicGrammatical();
    ~Test_BasicGrammatical();
    void run() noexcept final;
};
