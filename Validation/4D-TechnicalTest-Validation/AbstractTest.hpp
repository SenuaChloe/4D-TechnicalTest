#pragma once

#include <iostream>
#include <string_view>

enum class TestStatus
{
    NOT_COMPLETE,
    OK,
    NOK
};

class AbstractTest
{
public:
    AbstractTest(std::string_view test_names) : m_test_status(TestStatus::NOT_COMPLETE), m_test_name(test_names) {}

    virtual ~AbstractTest() {};
    virtual void run() noexcept = 0 ;
    TestStatus get_status() const { return m_test_status; };
    std::string_view get_name() const { return m_test_name; };

protected:
    TestStatus m_test_status;
    std::string m_test_name;
};
