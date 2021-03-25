#include "test.hpp"
#include "..\\src\\TestValidator.hpp"

#include <sstream>

bool spaceTest(){
    std::stringstream input, output;
    input << "  ";
    TestValidator::Validator validator(input, output);

    if(!validator.readSpaceChar()) return false;
    if(!validator.readSpaceChar()) return false;

    return true;
}

int main(){
    test::addTest("Space reading test", spaceTest);
    return test::runTests();
}