#include <array>
#include <iostream>
#include <fstream>

#include "matrix.h"


int main() {
	std::array<Matrix, 10> mtrx_array;
	std::string command; 
	while (1) {
		std::cin >> command;
		try {
			if (command == "exit") {
				return 0;
			}
			if (command == "load") {
				char trash;
				std::string filename;
				int reg;
				std::cin >> trash >> reg >> filename;
				
				std::ifstream in(filename);

				in >> mtrx_array[reg];
				in.close(); 
				
				continue;
			}
			if (command == "print") {
				char trash;
				int reg;
				
				std::cin >> trash >> reg;
				std::cout << mtrx_array[reg];
				
				continue;
			}
			if (command == "add") {
				int reg1, reg2;
				char trash;

				std:: cin >> trash >> reg1 >> trash >> reg2;
				mtrx_array[reg1] += mtrx_array[reg2];

				continue;
			}
			if (command == "mul") {
				int reg1, reg2;
				char trash;

				std:: cin >> trash >> reg1 >> trash >> reg2;
				mtrx_array[reg1] *= mtrx_array[reg2];

				continue;
			}

			if (command == "elem") {
				char trash;
				int reg, i, j;

				std::cin >> trash >> reg >> i >> j;
				std::cout << mtrx_array[reg].at(i, j) << std::endl;

				continue;
			}

		}
		catch(MatrixException & exception) {
			std::cout << exception.log() << std::endl;
		}
	}
}