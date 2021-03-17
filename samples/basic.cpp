#include <iostream>

#include "..\\src\\TestValidator.hpp"

int main(){
    TestValidator::Reader reader(std::cin);

    int x;
    std::cout<<reader.readInt(x)<<std::endl;
    std::cout<<x<<std::endl;


    return 0;
}