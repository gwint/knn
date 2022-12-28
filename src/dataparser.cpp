#include "dataparser.hpp"

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>

int DataParser::parseAsInt(std::string value) {
	std::stringstream ss(value);
	int intValue = 0;
	ss >> intValue;

	return intValue;
}

Data Data::retrieveFromFile(std::string filename) {
	Data data;
	std::ifstream fileStream;
	fileStream.open(filename);

	if(fileStream.is_open()) {
		for(std::string row; getline(fileStream, row);) {
			std::string colValue;
			for(std::stringstream colStream(row); getline(colStream, colValue, ',');) {
				int colParsedValue = DataParser::parseAsInt(colStream.str());
				std::cout << colParsedValue << '\n';
			}
		}
	}
	else {
		throw std::runtime_error("Unable to open file to read data.");
	}

	return data;
}

std::vector<int> Data::getDimensions() {
	std::vector<int> dimensions;
	return dimensions;
}

int Data::getValue(int indices...) {
	return 0;
}
