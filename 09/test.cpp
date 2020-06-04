#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "sort.h"

int main(){
    
    {
        std::ofstream file;
        file.open("input.dat", std::ios::binary);
        assert(file);
    
        for (uint64_t i = 9999999; i>0; i--)
            file.write((char*)&i, sizeof(uint64_t));
        file.close();
    }    

    try{
        std::cout <<"test started"<< std::endl;

        std::string fname("input.dat");
        sort(fname);
        std::cout<< "sorted completed\n";

        std::string fout("output.dat");
        std::ifstream out(fout);
        assert(out);

        //проверка 
        uint64_t prev, next;
        out.read((char*)&prev, sizeof(uint64_t));
        while(!out.eof()){
            out.read((char*)&next, sizeof(uint64_t));
            assert(prev<=next);
            prev=next;
        }
        out.close();
        std::cout << "test completed well"<< std::endl;
    }
    catch (...){
        std::cout << "Exception, error occured!"<< std::endl;
    }

    return 0;
}
