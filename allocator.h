template <class T>
class Allocator{
public:
    T* alloc(size_t count){   
        T* new_data = static_cast<T*>(malloc(sizeof(T)*count));
        if (!new_data)
            throw std::bad_alloc();
        return new_data;
    }

    void dealloc(T *ptr, size_t count){
        free(ptr);
    }

    template <class... Args>
    void construct(T *ptr, Args&&... args){
        new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T *ptr) noexcept{
        ptr->~T();
    }
};