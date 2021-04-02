#include <iostream>
#include <sstream>

#include "..\\src\\TestValidator.hpp"

int main(){
    TestValidator::Validator testValidator(std::cin, std::cout);
    char x;
    testValidator.readCharAndMatchClass(x, "a-");
    return 0;
}