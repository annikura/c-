#include <cassert>
#include <cstring>
#include <iostream>
#include "my_vector.h"


MyVector::MyVector(){
    _data = new TYPE[START_CAPACITY];
    _cp = START_CAPACITY;
    _sz = 0;
}

MyVector::MyVector(std::size_t init_capacity){
    _data = new TYPE[init_capacity];
    _cp = init_capacity;
    _sz = 0;
}

MyVector::~MyVector(){
    delete []_data;
}

void MyVector::set(std::size_t index, TYPE value){
    assert(index >= 0 && index < _sz);
    _data[index] = value;
}

TYPE MyVector::get(std::size_t index){
    assert(index >= 0 && index < _sz);
    return _data[index];
}

std::size_t MyVector::size(){
    return _sz;
}
std::size_t MyVector::capacity(){
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity){
    if (_cp >= new_capacity)
        return;
    _cp = new_capacity * 2;
    TYPE * new_data = new TYPE[_cp];
    memcpy(new_data, _data, _sz * sizeof(TYPE));
    delete []_data;
    _data = new_data;
}

void MyVector::resize(std::size_t new_size){
    this->reserve(new_size);
    memset(_data + _sz, 0, (new_size - _sz) * sizeof(TYPE));
    _sz = new_size;
}

void MyVector::push_back(TYPE value){
    if (_sz == _cp)
        this->reserve(_cp + 1);
    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, TYPE value){
    assert(index >= 0 && index <= _sz);
    if (_sz == _cp)
        this->reserve(_cp + 1);
    for (std::size_t i = _sz; i > index; i--)
        _data[i] = _data[i - 1];
    _data[index] = value;

    _sz++;
}

void MyVector::erase(std::size_t index){
    assert(index >= 0 && index < _sz);
    for (std::size_t i = index; i < _sz; i++)
        _data[i] = _data[i + 1];

    _sz--;
}
