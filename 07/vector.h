#pragma once
#include <iostream>
#include "allocator.h"
#include "iterator.h"

template <class T, class Alloc = Allocator<T> >
class Vector{
public:

    Vector(size_t count=0) :
                    data_size(count), 
                    data_capacity(count+3){
        data = allocator.alloc(data_capacity);
        for(size_t i=0; i<data_size;i++) 
            allocator.construct(&(data[i]));
    }

    ~Vector(){
        for (size_t i=0; i<data_size;i++){
            allocator.destroy(data + i);
        }
    }

    void push_back(const T &val){
        if (data_size>=data_capacity)
            this->reserve(data_size*2+1);
        data[data_size] = val;
        data_size++;
        return;
    }
    //push_back(T&& value) ... 

    void pop_back(){
        if (!empty()){
            data_size--;
            allocator.destroy(&data[data_size]);
        }
        else{
            std::cout << "warning: trying to delete from empty object";
        }
        return;
    }
    
    bool empty() const noexcept{
        return (data_size==0);
    }
    size_t size() const noexcept{
        return data_size;
    }
    size_t capacity() const noexcept{
        return data_capacity;
    }

    void clear(){
        this->resize(0);
        return;
    }

    Iterator<T> begin() const noexcept{
        return Iterator<T>(data);
    }
    Iterator<T> end() const noexcept{
        return Iterator<T>(&data[data_size]);
    }
    std::reverse_iterator<Iterator<T>> rbegin() const noexcept{
        return std::reverse_iterator<Iterator<T> >(Iterator<T>(&data[data_size]));
    }
    std::reverse_iterator<Iterator<T>> rend() const noexcept{
        return std::reverse_iterator<Iterator<T> >(Iterator<T>(data));
    }

    void reserve(size_t new_capacity){
        if(new_capacity<=data_capacity) return;
        T *tmp = allocator.alloc(new_capacity);
        for (size_t i=0; i<data_size;i++){
            tmp[i] = data[i];
            allocator.destroy(&data[i]);
        }
        allocator.dealloc(data, data_capacity);
        data = tmp;
        data_capacity = new_capacity;
        return;
    }
    void resize(size_t newSize){
        if(newSize>=data_capacity){
            reserve(newSize*2);
            for (size_t i=data_size; i<newSize; i++){
                allocator.construct(data+i);
            }
        }
        else if(newSize>=data_size){
            for (size_t i=data_size; i<newSize; i++){
                allocator.construct(data+i);
            }
        }
        else{
            for (size_t i=newSize; i<data_size;i++){
                allocator.destroy(data+i);
            }
        }
        data_size = newSize;
        return;
    }

    T& operator[](std::ptrdiff_t x) const{
        if(x>data_size)
            throw std::runtime_error("list index out of range");
        return data[x];
    }

private:
    Alloc allocator;
    T* data;
    size_t data_size;
    size_t data_capacity;
};
