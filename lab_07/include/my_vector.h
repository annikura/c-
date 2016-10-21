#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#define TYPE int
#define START_CAPACITY 2


#include <cstddef>

class MyVector {
public: // methods
    MyVector();
    MyVector(std::size_t init_capacity);
    ~MyVector();

    void set(std::size_t index, TYPE value);
    TYPE get(std::size_t index);

    std::size_t size();
    std::size_t capacity();

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(TYPE value);
    void insert(std::size_t index, TYPE value);
    void erase(std::size_t index);
private: // fields
    std::size_t _sz, _cp;
    int *_data;
};

#endif
