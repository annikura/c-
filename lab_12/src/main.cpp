#include <iostream>
#include <cstring>
#include <cassert>

#include "../include/my_vector.h"

static char * copystr(const char *from){
	size_t len = strlen(from);
	char * str = new char[len + 1];
	std::strcpy(str, from);
	return str;
}

class Product {
public:
	Product() : name_((char *)"NULL"), quantity_(0), price_(0){};

    Product(const char *name, int quantity, double price) : name_(copystr(name)),
    														quantity_(quantity), 
    														price_(price) {};

	Product(const Product & other) : name_(copystr(other.name_)),
							   quantity_(other.quantity_),
							   price_(other.price_){};

	Product(Product && other) : name_(other.name_),
							   quantity_(other.quantity_),
							   price_(other.price_){
		other.name_ = (char *)"NULL";
		other.quantity_ = 0, other.price_ = 0;
	};


	Product & operator=(Product other){
		this->~Product();
		new (this) Product(other);
	    return *this;
	}

    friend std::ostream & operator<<(std::ostream & out, Product & p);
private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream & operator<<(std::ostream & out, Product & p){
	std::cout << (std::string)p.name_ << " " << p.quantity_ << " " << p.price_;
	return out;
}

template <class T>
void test_my_vector(T a, T b){
	my_vector <T> v(5);
	assert(v.size() == 5);
	std::cout << v << std::endl;
	std::cout << "Should have printed: 5x zero values" << std::endl;
	assert(v.empty() == false);
	assert(v.capacity() == 8);
	v.push_back(a);
	std::cout << v << std::endl;
	std::cout << "Should have printed: 5x zero values, " << a << std::endl;
	v.push_back(b);
	std::cout << v << std::endl;
	std::cout << "Should have printed: 5x zero values, " << a << " " << b << std::endl;
	v.pop_back();
	std::cout << v << std::endl;
	std::cout << "Should have printed: 5x zero values, " << a << std::endl;
	v.push_back(a);
	std::cout << v << std::endl;
	std::cout << "Should have printed: 5x zero values, " << a << " " << a << std::endl;
	v.clear();
	assert(v.empty() == true);
	v.push_back(a);
	v.resize(8);
	std::cout << v << std::endl;
	std::cout << "Should have printed: " << a << ", 7x zero values" << std::endl;
	v.reserve(9);
	assert(v.capacity() == 16);

	my_vector <T> x;
	my_vector <T> y(v);

	x.push_back(b);
	std::cout << x << std::endl;
	std::cout << "Should have printed: " << b << std::endl;
	y.push_back(b);
	std::cout << y << std::endl;
	std::cout << "Should have printed: " << a << ", 7x zero values " << b << std::endl;
	std::cout << v << std::endl;
	std::cout << "Should have printed: " << a << ", 7x zero values" << std::endl;
	y = v;
	std::cout << y << std::endl;
	std::cout << "Should have printed: " << a << ", 7x zero values" << std::endl;
	
}

int main() {
   //test_my_vector<int>(5, 10);
    //test_my_vector(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}

