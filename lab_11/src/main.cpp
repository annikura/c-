#include <cstdio>
#include "employees.h"


using namespace std;

int main(){
    string filename;
    string input;
    EmployeesArray emp_array;
    while (1){
        cin >> input;
        if (input == "exit")
            break;
        if (input == "list"){
            cout << emp_array;
            continue;
        }
        if (input == "add"){
            int32_t type;
            cin >> type;
            if (type == DEVELOPER){
                Developer * employee = new Developer;
                cin >> *employee;
                emp_array.add(employee);
            }
            else if (type == SMANAGER){
                SalesManager * employee = new SalesManager;
                cin >> *employee;
                emp_array.add(employee);
            }
            continue;
        }
        if (input == "save"){
            std::cin >> filename;
            ofstream out;
            out.open(filename.c_str(), ios_base::binary);
            out << emp_array;
            out.close();
            continue;
        }
        if (input == "load"){
            std::cin >> filename;
            ifstream in;
            in.open(filename.c_str(), ios_base::binary);
            in >> emp_array;
            in.close();
            continue;
        }
    }
    return 0;
}
