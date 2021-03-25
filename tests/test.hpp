#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>

namespace test{
    std::vector<std::pair<std::string, bool (*)()>> tests;

    void addTest(std::string testName, bool(*testFunction)()){
        tests.emplace_back(testName, testFunction);
    }

    int runTests(){
        int failCount = 0;
        for(auto test : tests){
            auto testName = test.first;
            auto testFunction = test.second;

            bool success = testFunction();
            if(success){
                std::cout<<"Passed \""<<testName<<"\""<<std::endl;
            }
            else{
                std::cout<<"FAILED \""<<testName<<"\""<<std::endl;
                failCount++;
            }
        }

        std::cout<<std::endl;
        if(failCount == 0){
            std::cout<<"All of "<<tests.size()<<" test(s) passed"<<std::endl;
        }
        else{
            std::cout<<failCount<<" out of "<<tests.size()<<" test(s) failed"<<std::endl; 
        }
        return failCount;
    }
}