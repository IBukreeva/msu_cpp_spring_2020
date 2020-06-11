#include <iostream>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "summator.h"
#include <vector>

void read(std::ifstream& in, std::mutex& mtx_numbers, std::vector<int>& numbers, 
                std::condition_variable& num_cond, bool& read_complete){

    int tmp;
    while(!in.eof()){
        std::unique_lock<std::mutex> lock(mtx_numbers);
        in >> tmp;
        numbers.push_back(tmp);
        lock.unlock();
        num_cond.notify_one();
    }
    read_complete=true;
    num_cond.notify_all();
}

void count_sum(std::mutex& mtx_numbers, std::vector<int>& numbers, 
                        std::mutex& ans_mtx, int& answer, std::condition_variable& num_cond, bool& read_complete){

    int summ=0;
    int tmp=0;
    while(true){
        std::unique_lock<std::mutex> lock(mtx_numbers);
        while(numbers.empty() && !read_complete){
            num_cond.wait(lock);
        }
        if(read_complete && numbers.empty()) break;

        tmp = numbers.back();
        numbers.pop_back();
        lock.unlock();
        summ+=tmp;
    }

    {
        std::unique_lock<std::mutex> lock(ans_mtx);
        answer+=summ;
    }

}

int summator(std::string& fname){

    std::ifstream in(fname);
    std::cout << fname<< std::endl;
    assert(in);

    int answer=0;
    std::mutex ans_mtx;
    std::condition_variable num_cond; //чтобы когда добавляются новые числа оповещать какой-нибудь поток
    std::vector<int> numbers;
    std::mutex mtx_numbers;
    bool read_complete=false;

    auto reading = std::bind(read, std::ref(in), std::ref(mtx_numbers), std::ref(numbers), std::ref(num_cond), std::ref(read_complete));
    auto summaring = std::bind(count_sum, std::ref(mtx_numbers), std::ref(numbers), std::ref(ans_mtx), std::ref(answer), std::ref(num_cond), std::ref(read_complete));

    std::thread readThread(reading);
    std::thread sumThread1(summaring);
    std::thread sumThread2(summaring);

    readThread.join();
    sumThread1.join();
    sumThread2.join();

    return answer;
}