#include <cstddef>
#include <iostream>

static const int START_VECTOR_SIZE = 64;

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector & other);
    my_vector & operator=(my_vector other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);

    T & operator[](size_t index);
    const T & operator[](size_t index) const;

    void push_back(T& t);
    void pop_back();
    void clear();
    void swap(my_vector & other);

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};


static size_t lowest_ge_two_degree(size_t n){
    size_t two = 1;
    while (two < n) { two <<= 1; }
    return two;
}

template <class T>
my_vector<T>::my_vector() : capacity_(0), size_(0), array_(NULL) {
    this->reserve(START_VECTOR_SIZE);
}

template <class T>
my_vector<T>::my_vector(size_t n) : capacity_(0), size_(0), array_(NULL){
    this->resize(n);
}
    
template <class T>
my_vector<T>::my_vector(const my_vector & other) : my_vector(other.size()){
    for (size_t i = 0; i < size_; i++){
        array_[i].~T();
        new (array_ + i) T(other[i]);
    }
}

template <class T>
my_vector<T> & my_vector<T>::operator=(my_vector<T> other){
    //swap-copy idiom. If we don't make a copy here^ we will have to do it in function body. But for what? 
    this->swap(other);
    return *this;
}

template <class T>
my_vector<T>::~my_vector(){
    for (size_t i = 0; i < size_; i++)
        this->array_[i].~T();
    delete [] array_;
}

template <class T>
size_t my_vector<T>::size() const{
    return size_;
}

template <class T>
size_t my_vector<T>::capacity() const{
    return capacity_;
}


template <class T>
bool my_vector<T>::empty() const{
    return size_ == 0;
}

template <class T>
void my_vector<T>::resize(size_t n){
    this->reserve(n);
    if (n < size_){
        for (size_t i = n; i < size_; i++)
            this->array_[i].~T();            
    }
    if (n > size_){
        for (size_t i = size_; i < n; i++)
            new (this->array_ + i) T(); 
    }
    size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n){
    if (capacity_ >= n)
        return;
    n = lowest_ge_two_degree(n);
    T *tmp = (T *)(new char[n * sizeof(T)]);
    for (size_t i = 0; i < size_; i++)
        new (tmp + i) T(this->array_[i]);
    std::swap(tmp, this->array_);
    delete [] tmp;
    capacity_ = n;
}

template <class T>
T & my_vector<T>::operator[](size_t index){
    return this->array_[index];
}


template <class T>
const T &my_vector<T>::operator[](size_t index) const{
    return this->array_[index];
}

template <class T>
void my_vector<T>::push_back(T& t){
    this->reserve(size_ + 1);
    new (this->array_ + size_++) T(t);
}

template <class T>
void my_vector<T>::pop_back(){
    if (size_)
        this->array_[--size_].~T();
}

template <class T>
void my_vector<T>::clear(){
    this->resize(0);
}

template <class T>
std::ostream & operator<<(std::ostream & out, my_vector<T> & v){
    for (size_t i = 0; i < v.size(); i++){
        if (i)
            out << " ";
        out << v[i];
    }
    return out;
}

template <class T>
void my_vector<T>::swap(my_vector & other){
    std::swap(other.array_, this->array_);
    std::swap(other.size_, this->size_);
    std::swap(other.capacity_, this->capacity_);
}