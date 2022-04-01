#include <iostream>

#include "Test_BasicLexical.hpp"


void check_result(const AbstractTest & test)
{
    switch (test.get_status())
    {
    break; case TestStatus::NOT_COMPLETE:
        std::cout << "ERROR - Incomplete test: " << test.get_name() << std::endl;
    break; case TestStatus::NOK:
        std::cout << "NOK - Test failed: " << test.get_name() << std::endl;
    break; case TestStatus::OK:
        std::cout << "OK - Test succeeded: " << test.get_name() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    {
        Test_BasicLexical test;
        test.run();
        check_result(test);
    }
    {
        Test_BasicLexical test;
        test.run();
        check_result(test);
    }
}
