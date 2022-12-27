#include "dataparser.hpp"

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

Data Data::retrieveFromFile(std::string filename) {
	Data data;
	std::ifstream fileStream;
	fileStream.open(filename);

	if(fileStream.is_open()) {
		for(std::string row; getline(fileStream, row);) {
			std::cout << row << '\n';
		}
	}
	else {
		throw std::runtime_error("Unable to open file to read data.");
	}

	return data;
}
