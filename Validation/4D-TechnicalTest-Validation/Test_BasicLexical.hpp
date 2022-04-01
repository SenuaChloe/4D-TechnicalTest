#pragma once

#include "AbstractTest.hpp"


struct Test_BasicLexical : public AbstractTest
{
    Test_BasicLexical();
    ~Test_BasicLexical() override;
    void run() noexcept final;
};
