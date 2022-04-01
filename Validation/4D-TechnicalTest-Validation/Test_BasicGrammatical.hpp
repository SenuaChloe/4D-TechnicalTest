
#pragma once

#include "AbstractTest.hpp"


struct Test_BasicGrammatical : public AbstractTest
{
    Test_BasicGrammatical();
    ~Test_BasicGrammatical() override;
    void run() noexcept final;
};
