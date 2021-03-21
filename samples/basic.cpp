#include <iostream>

#include "..\\src\\TestValidator.hpp"

int main(){
    TestValidator::Validator validator(std::cin, std::cout);
    int x;
    validator.readIntegerInRange(x, 1, 50, "Hello");
    validator.readEndOfFile();

    return 0;
}