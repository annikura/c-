#include <stdexcept>
#include <cstring>
#pragma once

// common array functions

class my_array_ancestor {
protected:
  	void range_exceptor(std::size_t index, std::size_t size) const;
};

void my_array_ancestor::range_exceptor(std::size_t index, std::size_t size) const{
	if (index >= size)
		throw std::out_of_range("While getting an element from 'my_array' instance an error occured: \
								 Index is out of range");
}


// a common template for the array of any type

template<typename T, std::size_t N>
class my_array : private my_array_ancestor{
public:
	bool empty() const { return false; };
	std::size_t size() const { return N; };

	T & at(std::size_t index);
	const T & at(std::size_t index) const;
  	T & operator[](std::size_t index);
  	const T & operator[](std::size_t index) const;
  	void fill(T val);
private:
	T array_[N];
};
 
template<typename T, std::size_t N>
T & my_array<T, N>::at(std::size_t index){
	this->range_exceptor(index, N);
	return this->operator[](index);
}

template<typename T, std::size_t N>
const T & my_array<T, N>::at(std::size_t index) const {
	this->range_exceptor(index, N);
	return this->operator[](index);
}

template<typename T, std::size_t N>
const T & my_array<T, N>::operator[](std::size_t index) const {
	return array_[index];
}

template<typename T, std::size_t N>
T & my_array<T, N>::operator[](std::size_t index) {
	return array_[index];
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(T val){
	for (size_t i = 0; i < N; i++)
		array_[i] = val;
}

 // zero-size case specializaion

template<typename T>
class my_array <T, 0> : private my_array_ancestor{
public:
	bool empty() const { return true; };
	std::size_t size() const { return 0; };
	
	T & at(std::size_t index) { this->range_exceptor(index, 0); };
	const T & at(std::size_t index) const { this->range_exceptor(index, 0); };
  	T & operator[](std::size_t index) { return 0; }; 
  	const T & operator[](std::size_t index) const { return 0; }; 
  	void fill(__attribute__ ((unused)) T val) { };
};

// bool specialization

template<std::size_t N>
class my_array<bool, N> : private my_array_ancestor{
private:
	char array_[(N + 7) / 8];
	class Proxy {
	public:
		Proxy(const char* byte, std::size_t offset) : 
			byte_((char *)byte + offset / 8), 
			offset_(offset % 8) { };
		Proxy & operator=(bool val);
		Proxy & operator=(Proxy & other);
		operator bool() const;
	private:
		char* byte_;
		std::size_t offset_;
	};

public:
	my_array(){ this->fill(0); }
	bool empty() const { return false; };
	std::size_t size() const { return N; };

	bool at(std::size_t index) const;
  	Proxy at(std::size_t index);
  	Proxy operator[](std::size_t index); 
  	bool operator[](std::size_t index) const;
  	void fill(bool val);
};

// Proxy methods

template<std::size_t N>
typename my_array<bool, N>::Proxy & my_array<bool, N>::Proxy::operator=(my_array<bool, N>::Proxy & val){
	*this = bool(val);
	return *this;
}

template<std::size_t N>
typename my_array<bool, N>::Proxy & my_array<bool, N>::Proxy::operator=(bool val){
	*byte_ = (*byte_ & (~(1 << offset_))) | ((1 << offset_) * (int)val);
	return *this;
}

template<std::size_t N>
my_array<bool, N>::Proxy::operator bool() const{
	return ((*byte_) & (1 << offset_)) != 0;
}

// bool array specialization methods

template<std::size_t N>
bool my_array<bool, N>::at(std::size_t index) const{
	this->range_exceptor(index, N);
	return this->operator[](index);
}

template<std::size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::at(std::size_t index){
	this->range_exceptor(index, N);
	return this->operator[](index);
}

template<std::size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::operator[](std::size_t index){
	return Proxy(array_, index);
}

template<std::size_t N>
bool my_array<bool, N>::operator[](std::size_t index) const{
	return Proxy(array_, index);
}

template<std::size_t N>
void my_array<bool, N>::fill(bool val){
	char filler = val;
	if (val)
		filler = -1;
	memset(array_, filler, (N + 7) / 8);
}

template<std::size_t N>
std::ostream & operator<<(std::ostream & out, my_array<bool, N> arr){
	for (std::size_t i = 0; i < N; i++)
		out << arr[i];
	out << std::endl;
	return out; 
}

template<>
class my_array<bool, 0> {
public:
	int size(){
		return 5;
	}
};