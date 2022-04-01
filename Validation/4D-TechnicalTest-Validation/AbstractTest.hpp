#pragma once


enum class TestStatus
{
    NOT_COMPLETE,
    OK,
    NOK
};

class AbstractTest
{
public:
    AbstractTest() : m_test_status(TestStatus::NOT_COMPLETE) {}

    virtual ~AbstractTest() = 0;
    virtual void run() noexcept = 0 ;
    TestStatus get_status() const { return m_test_status; };

protected:
    TestStatus m_test_status;
};
