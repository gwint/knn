#include "dataparser.hpp"

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdarg>

void getNumDimensionDataPoints(const std::vector<int>&, std::vector<int>&); 

int DataParser::parseAsInt(std::string value) {
	std::stringstream ss(value);
	int intValue = 0;
	ss >> intValue;

	return intValue;
}

Data Data::retrieveFromCSVFile(std::string filename) {
	Data data;
	std::ifstream fileStream;
	fileStream.open(filename);

	int numRows = 0;
	int numColumns;

	if(fileStream.is_open()) {
		for(std::string row; getline(fileStream, row);) {
			++numRows;
			std::string colValue;
			numColumns = 0;
			std::stringstream colStream(row);
			while(getline(colStream, colValue, ',')) {
				int colParsedValue = DataParser::parseAsInt(colValue);
				data.getInputVectors().push_back(colParsedValue);
				++numColumns;
			}
		}
	}
	else {
		throw std::runtime_error("Unable to open file to read data.");
	}

	data.getDimensions().push_back(numRows);
	data.getDimensions().push_back(numColumns);

	return data;
}

Data Data::getSample(const int sampleIndex) {
	Data sample;
	std::vector<int>& allDimensions = this->getDimensions();
	for(int i = 1; i < allDimensions.size(); ++i) {
		sample.getDimensions().push_back(allDimensions[i]);
	}

	std::vector<int>& dimensions = this->getDimensions();
	std::vector<int> numDataPointsInEachDimension;
	getNumDimensionDataPoints(dimensions, numDataPointsInEachDimension);

	const int numDataPointsInEachSample = numDataPointsInEachDimension.front();
	int startingIndex = numDataPointsInEachSample * sampleIndex;

	for(int i = 0; i < numDataPointsInEachSample; ++i) {
		sample.getInputVectors().push_back(this->inputVectors[startingIndex+i]);
	}

	return sample;
}

std::vector<int>& Data::getDimensions() {
	return this->dimensions;
}

std::vector<int>& Data::getInputVectors() {
	return this->inputVectors;
}

const std::vector<int>& Data::getInputVectorsImmutable() const {
	return this->inputVectors;
}


void getNumDimensionDataPoints(const std::vector<int>& dimensions, std::vector<int>& numDataPointsInEachDimension) {
	numDataPointsInEachDimension.clear();
	for(int i = 0; i < dimensions.size(); ++i) {
		numDataPointsInEachDimension.push_back(1);
	}

	int currProduct = 1;

	for(int i = dimensions.size() - 2; i > -1 ; --i) {
		currProduct =  currProduct * dimensions[i+1];
		numDataPointsInEachDimension[i] = currProduct;
	}
}

int Data::getValue(std::vector<int> indices) {
	std::vector<int>& dimensions = this->getDimensions();
	std::vector<int> numDataPointsInEachDimension;
	getNumDimensionDataPoints(dimensions, numDataPointsInEachDimension);

	int index = 0;
	
	for(int i = 0; i < indices.size(); ++i) {
		index += (indices[i] * numDataPointsInEachDimension[i]);
	}

	return this->getInputVectors()[index];
}
