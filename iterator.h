#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>{
public:
    explicit Iterator(T* ptr_) : ptr(ptr_) 
    {
    }

    Iterator<T>& operator++(){
        ptr++;
        return *this;
    }
    Iterator<T>& operator--(){
        ptr--;
        return *this;
    }

    Iterator<T>& operator+=(size_t n){
        ptr += n;
        return *this;
    }
    Iterator<T>& operator-=(size_t n){
        ptr -= n;
        return *this;
    }    
    
    Iterator<T> operator+(size_t n) const{
        return Iterator(ptr + n);
    }
    Iterator<T> operator-(size_t n) const{
        return Iterator(ptr - n);
    }

    T& operator*() const{
        return *ptr;
    }
    T& operator[](int n) const{
        return ptr[n];
    }

    bool operator==(const Iterator<T> &iter) const{
        return ptr==iter.ptr;
    }
    bool operator!=(const Iterator<T> &iter) const{
        return ptr!=iter.ptr;
    }

private:
    T *ptr;
};