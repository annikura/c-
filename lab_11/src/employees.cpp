#include "../include/employees.h"


static std::ifstream & operator>>(std::ifstream & in, std::string & s){
    char byte;
    s = "";
    while (1){
        in.read((char *)&byte, sizeof(char));
        if (byte == 0)
            break;
        else
            s += byte;
    }
    return in;
}


std::istream & operator >> (std::istream & in, Developer & d){
    std::string name;
    in >> name >> d._base_salary >> d._has_bonus;
    d._name = new char[name.size() + 1];
    std::strcpy(d._name, name.c_str());
    return in;
}

std::ostream & operator << (std::ostream & out, Developer & d){
    std::string name(d._name);
    out << "Developer\n"
        << "Name: " << name << "\n"
        << "Base Salary: " << d._base_salary << "\n"
        << "Has bonus: " << (d._has_bonus ? "+\n" : "-\n");
    return out;
}


std::ifstream &operator >> (std::ifstream & in, Developer & d){
    std::string name;
    in >> name;
    d._name = new char[name.size() + 1];
    std::strcpy(d._name, name.c_str());
    in.read((char *)&d._base_salary, sizeof(d._base_salary));
    in.read((char *)&d._has_bonus, sizeof(d._has_bonus));
    return in;
}

std::ofstream &operator << (std::ofstream & out, Developer & d){
    int32_t type = DEVELOPER;
    char zero = 0;
    out.write((char *)&type, sizeof(type));
    out << (std::string)d._name;
    out.write((char *)&zero, sizeof(char));
    out.write((char *)&d._base_salary, sizeof(d._base_salary));
    out.write((char *)&d._has_bonus, sizeof(d._has_bonus));
    return out;
}

std::istream & operator >> (std::istream & in, SalesManager & sm){
    std::string name;
    in >> name >> sm._base_salary >> sm._sold_nm >> sm._price;
    sm._name = new char[name.size() + 1];
    std::strcpy(sm._name, name.c_str());
    return in;
}

std::ostream & operator << (std::ostream & out, SalesManager & sm){
    std::string name(sm._name);
    out << "Sales Manager\n"
        << "Name: " << name << "\n"
        << "Base Salary: " << sm._base_salary << "\n"
        << "Sold items: " << sm._sold_nm << "\n"
        << "Item price: " << sm._price << "\n";
    return out;
}

std::ifstream &operator >> (std::ifstream & in, SalesManager & sm){
    std::string name;
    in >> name;
    sm._name = new char[name.size() + 1];
    std::strcpy(sm._name, name.c_str());
    in.read((char *)&sm._base_salary, sizeof(sm._base_salary));
    in.read((char *)&sm._sold_nm, sizeof(sm._sold_nm));
    in.read((char *)&sm._price, sizeof(sm._price));
    return in;
}

std::ofstream &operator << (std::ofstream & out, SalesManager & sm){
    int32_t type = SMANAGER;
    char zero = 0;
    out.write((char *)&type, sizeof(type));
    out << (std::string)sm._name;
    out.write((char *)&zero, sizeof(char));
    out.write((char *)&sm._base_salary, sizeof(sm._base_salary));
    out.write((char *)&sm._sold_nm, sizeof(sm._sold_nm));
    out.write((char *)&sm._price, sizeof(sm._price));
    return out;
}

EmployeesArray::~EmployeesArray(){
    for (int i = 0; i < _count; i++)
        delete _employees[i];
    delete [] _employees;
}

void EmployeesArray::add(const Employee *e){
    Employee ** tmp = new Employee*[_count + 1];
    for (int i = 0; i < _count; i++)
        tmp[i] = _employees[i];
    tmp[_count] = (Employee *)e;
    if (_employees)
        delete [] _employees;
    _employees = tmp;
    _count++;
}

int EmployeesArray::total_salary() const{
    int sum = 0;
    for (int i = 0; i < _count; i++)
        sum += _employees[i]->salary();
    return sum;
}

std::ostream & operator<<(std::ostream & out, EmployeesArray & ea){
    for (int i = 0; i < ea._count; i++)
        out << i + 1 << ". " << *(ea._employees[i]);
    out << "== Total salary: " << ea.total_salary() << "\n";
    return out;
}


std::ofstream &operator<<(std::ofstream & out, EmployeesArray & ea){
    out.write((char *)&ea._count, sizeof(ea._count));
    for (int i = 0; i < ea._count; i++){
        out << *ea._employees[i];
    }
    return out;
}

std::ifstream &operator>>(std::ifstream & in, EmployeesArray & ea){
    int32_t type, to_add;
    in.read((char *)&to_add, sizeof(to_add));
    for (int i = 0; i < to_add; i++){
        in.read((char *)&type, sizeof(type));
        if (type == DEVELOPER){
            Developer * employee = new Developer();
            in >> *employee;
            ea.add(employee);
        }
        else if (type == SMANAGER){
            SalesManager * employee = new SalesManager();
            in >> *employee;
            ea.add(employee);
        }
    }
    return in;
}
