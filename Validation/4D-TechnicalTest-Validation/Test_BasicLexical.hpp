#pragma once

#include "AbstractTest.hpp"

class Test_BasicLexical : public AbstractTest
{
    ~Test_BasicLexical() override;
    void run() noexcept final;
};
