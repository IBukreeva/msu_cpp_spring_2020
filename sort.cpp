#include <iostream>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <mutex>
#include <thread>
#include "sort.h"

#define BUFSIZE 8388608

void thread_sort(std::mutex& mtx, std::ifstream& in, std::ofstream& tmp){

    std::unique_ptr<uint64_t[]> sorting_arr(new uint64_t[BUFSIZE/sizeof(uint64_t)]);
    while(true){
        {
            std::unique_lock<std::mutex> lock(mtx);
            in.read((char*)sorting_arr.get(), BUFSIZE);
        }
        size_t read = in.gcount();
        if (read==0) break;
        std::sort(sorting_arr.get(), sorting_arr.get()+read/sizeof(uint64_t));
        {
            std::unique_lock<std::mutex> lock(mtx);
            tmp.write((char*)sorting_arr.get(), read);
        }
    }
}

void merge2blocks(std::ifstream& in, std::ofstream& out, uint64_t lpos, uint64_t rpos, uint64_t block_size){
    in.seekg(lpos, std::ios::beg);

    uint64_t leftPiecePos=lpos+sizeof(uint64_t), rightPiecePos=lpos+block_size;
    in.seekg(lpos, std::ios::beg);
    uint64_t num_left;
    in.read((char*)&num_left, sizeof(uint64_t));
    uint64_t num_righ = 0; //считать из правого куска
    bool flag=false; //показывает, откуда будем читать в следующий раз: true - левый кусок
                    //                                                  false - правый кусок
    while((leftPiecePos<lpos+block_size)&&(rightPiecePos<rpos)){
        if(flag){
            in.seekg(leftPiecePos, std::ios::beg);
            in.read((char*)&num_left, sizeof(uint64_t));
            leftPiecePos+=sizeof(uint64_t);
        }
        else{
            in.seekg(rightPiecePos, std::ios::beg);
            in.read((char*)&num_righ, sizeof(uint64_t));
            rightPiecePos+=sizeof(uint64_t);
        }
        if(num_left<num_righ){
            out.write((char*)&(num_left), sizeof(uint64_t));
            flag=true;
        }
        else{
            out.write((char*)&(num_righ), sizeof(uint64_t));
            flag=false;
        }
    }

    uint64_t buf;
    in.seekg(leftPiecePos, std::ios::beg);
    while(leftPiecePos<lpos+block_size){
        in.read((char*)&buf, sizeof(uint64_t));
        out.write((char*)&(buf), sizeof(uint64_t));
        leftPiecePos+=sizeof(uint64_t);
    }

    in.seekg(rightPiecePos, std::ios::beg);
    while(rightPiecePos<rpos){ 
        in.read((char*)&buf, sizeof(uint64_t));
        out.write((char*)&(buf), sizeof(uint64_t));
        rightPiecePos+=sizeof(uint64_t);
    }
}

void merge_blocks(){
    std::ifstream in;
    std::ofstream f1;
    uint64_t cursize_block=BUFSIZE;
    
    in.open("help_file.bin", std::ios::binary);
    in.seekg(0, std::ios::end);
    uint64_t filesize = in.tellg();  //размер файла
    in.seekg(0, std::ios::beg);
    in.close();

    while(cursize_block<filesize){
        in.open("help_file.bin", std::ios::binary);
        assert(in);
        f1.open("f1.bin", std::ios::binary);
        assert(f1);
        uint64_t lpos=0;

        uint64_t rpos;
        while(lpos<filesize-cursize_block){
            if(lpos+2*cursize_block<filesize) rpos=lpos+2*cursize_block;
            else rpos=filesize;
            merge2blocks(in, f1, lpos, rpos, cursize_block);
            lpos+=cursize_block*2;
        }
        in.close(); f1.close();

        in.open("f1.bin", std::ios::binary);
        f1.open("help_file.bin", std::ios::binary);
        const size_t capacity = 1024;
        char buffer[capacity];
        while(!in.eof()){
            in.read(buffer, capacity);
            f1.write(buffer, in.gcount());
        }  
        in.close(); f1.close();

        cursize_block*=2;
    }
}

void sort(std::string& inFname){

    std::ifstream in(inFname, std::ios::binary);
    assert(in);
    std::ofstream help_file("help_file.bin", std::ios::binary);
    assert(help_file);

    std::mutex mtx;
    auto sorting = std::bind(thread_sort, std::ref(mtx), std::ref(in), std::ref(help_file));
    std::thread sort_thread1 (sorting);
    std::thread sort_thread2 (sorting);
    sort_thread1.join();
    sort_thread2.join();
    help_file.close();
    std::cout << "complete sorting pieces"<< std::endl;
    //теперь у нас есть отсортированные кусочки фиксированного размера
    merge_blocks();
    
    //переписать в выходной файл
    std::ofstream out("output.dat", std::ios::binary);
    in.close(); in.open("help_file.bin", std::ios::binary);
    assert(in); assert(out);
    const size_t capacity = 1024;
     char buffer[capacity];
    while(!in.eof()){
        in.read(buffer, capacity);
        out.write(buffer, in.gcount());
    }  
    in.close(); out.close();

}

