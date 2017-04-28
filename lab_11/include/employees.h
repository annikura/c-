#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

enum employee_t {DEVELOPER = 1, SMANAGER = 2};

class Employee  {
public:
    Employee(){};
    virtual ~Employee(){delete [] _name;};
    virtual std::ostream & output(std::ostream & out) = 0;
    virtual std::ofstream & output(std::ofstream & out) = 0;
    virtual int salary() const = 0;

    friend std::ostream &operator<<(std::ostream & out, Employee & e){
        return e.output(out);
    }

    friend std::ofstream &operator<<(std::ofstream & out, Employee & e){
        return e.output(out);
    }

private:
    Employee(__attribute__((unused)) Employee & other){};
    Employee & operator=(Employee & other){return other;};
protected:
    char *_name;
    int32_t _base_salary;

};

class Developer : public Employee {
public:
    Developer(){};
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
            return salary;
    }

    std::ostream & output(std::ostream & out){
        out << *this;
        return out;
    }

    std::ofstream & output(std::ofstream & out){
        out << *this;
        return out;
    }

    friend std::istream &operator >> (std::istream & in, Developer & d);
    friend std::ostream &operator << (std::ostream & out, Developer & d);
    friend std::ifstream &operator >> (std::ifstream & in, Developer & d);
    friend std::ofstream &operator << (std::ofstream & out, Developer & d);


private:
    Developer(__attribute__((unused)) Developer & other) : Employee(){};
    Developer &operator=(Developer & other){return other;};

    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager(){};
    int salary() const {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    std::ostream & output(std::ostream & out){
        out << *this;
        return out;
    }

    std::ofstream & output(std::ofstream & out){
        out << *this;
        return out;
    }

    friend std::istream &operator >> (std::istream & in, SalesManager & sm);
    friend std::ostream &operator << (std::ostream & out, SalesManager & sm);
    friend std::ifstream &operator >> (std::ifstream & in, SalesManager & sm);
    friend std::ofstream &operator << (std::ofstream & out, SalesManager & sm);

private:
    SalesManager(__attribute__((unused)) SalesManager & other) : Employee(){};
    SalesManager & operator=(SalesManager & other){return other;};

    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray() : _count(0), _employees(NULL){};
    ~EmployeesArray();
    void add(const Employee *e);
    int total_salary() const;

    friend std::ostream &operator << (std::ostream & out, EmployeesArray & ea);
    friend std::ofstream &operator << (std::ofstream & out, EmployeesArray & ea);
    friend std::ifstream &operator >> (std::ifstream & in, EmployeesArray & ea);


private:
    EmployeesArray(__attribute__((unused)) Employee & other){};
    EmployeesArray & operator=(EmployeesArray & other){return other;};

    int32_t _count;
    int _total_salary;
    Employee **_employees;
};

#endif
