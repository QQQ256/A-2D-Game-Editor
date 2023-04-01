#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>

class Debug
{
public:
    template<typename T>
    // && means rvalue reference, which is used for move semantics
    static void PrintMessage(T&& t){
        std::cout << t << std::endl;
    }
};

#endif