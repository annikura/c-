#include "shared_ptr.h"
#include <algorithm>
#include <iostream>

void shared_ptr::swap(shared_ptr & other){
    std::swap(storage_, other.storage_);
}

shared_ptr::shared_ptr(){
    storage_ = new Storage(NULL);
}

shared_ptr::shared_ptr(Matrix* obj){
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr & other){
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr & shared_ptr::operator=(shared_ptr other){
    if (other.ptr() != storage_->getObject())
        this->swap(other);
    return *this;
}

shared_ptr::~shared_ptr(){
    storage_->decr();
}

Matrix *shared_ptr::ptr() const{
    return storage_->getObject();
}

bool shared_ptr::isNull() const{
    return storage_->getObject() == NULL;
}

void shared_ptr::reset(Matrix *obj){
    shared_ptr tmp(obj);
    this->swap(tmp);
}

void shared_ptr::reset(){
    shared_ptr tmp(NULL);
    this->swap(tmp);
}

Matrix *shared_ptr::operator->() const{
    return storage_->getObject();
}

Matrix & shared_ptr::operator*() const{
    return *storage_->getObject();
}

//storage

void shared_ptr::Storage::swap(shared_ptr::Storage & other){
    std::swap(data_, other.data_);
    std::swap(ref_count_, other.ref_count_);
}

shared_ptr::Storage::Storage(){
    data_ = NULL;
    ref_count_ = 1;
}

shared_ptr::Storage::Storage(Matrix *mtx){
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage(){
    if (data_)
        delete data_;
}

void shared_ptr::Storage::incr(){
    ref_count_++;
}

void shared_ptr::Storage::decr(){
    ref_count_--;
    if (!ref_count_)
        delete this;
}

int shared_ptr::Storage:: getCounter() const{
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const{
    return data_;
}
