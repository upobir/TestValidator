#include "test.hpp"
#include "..\\src\\TestValidator.hpp"

#include <sstream>
#include <string.h>

bool matchExceptionMessage(const char* msg){
    return strcmp(msg, "Validation Error") == 0;
}

bool spaceTest(){
    std::stringstream input, output;
    std::string testString(" \t  xt230\a2\n  \t");
    input << testString;
    
    TestValidator::Validator validator(input, output);
    for(char c : testString){
        bool is_space = (c == ' ');
        try{
            bool success = validator.readSpaceChar();
            if(!is_space || !success){
                return false;
            }
        }
        catch(const char* msg){
            if(matchExceptionMessage(msg) == is_space){
                return false;
            }
        }
    }
    
    return true;
}

int main(){
    test::addTest("Space reading test", spaceTest);
    return test::runTests();
}