#include <iostream>
#include <cstdio>

#include "summator.h"

int main(){

    {
        std::string fname("input1.txt");

        int result = summator(fname);
        std::cout << result<< std::endl;
    }


    {
        std::string fname("input2.txt");

        int result = summator(fname);
        std::cout << result<< std::endl;

    }
    return 0;   
}