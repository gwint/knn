#include "dataparser.hpp"

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <assert.h>

void getNumDimensionDataPoints(const std::vector<int>&, std::vector<int>&); 

int DataParser::parseAsInt(std::string value) {
	std::stringstream ss(value);
	int intValue = 0;
	ss >> intValue;

	return intValue;
}

Data Data::retrieveClassificationsFromCSVFile(std::string filename) {
	Data classifications;
	std::ifstream classificationsFileStream;
	classificationsFileStream.open(filename);
	int numRows = 0;

	if(classificationsFileStream.is_open()) {
		for(std::string row; getline(classificationsFileStream, row);) {
			++numRows;
			classifications.getInputVectors().push_back(DataParser::parseAsInt(row));
		}
	}
	else {
		throw std::runtime_error("Unable to open file to read classifications.");
	}

	classifications.getDimensions().push_back(numRows);
	return classifications;
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

Data Data::getSample(const int sampleIndex) const {
	Data sample;
	const std::vector<int>& allDimensions = this->getDimensionsImmutable();
	for(int i = 1; i < allDimensions.size(); ++i) {
		sample.getDimensions().push_back(allDimensions[i]);
	}

	const std::vector<int>& dimensions = this->getDimensionsImmutable();
	std::vector<int> numDataPointsInEachDimension;
	getNumDimensionDataPoints(dimensions, numDataPointsInEachDimension);

	const int numDataPointsInEachSample = numDataPointsInEachDimension.front();
	int startingIndex = numDataPointsInEachSample * sampleIndex;

	for(int i = 0; i < numDataPointsInEachSample; ++i) {
		sample.getInputVectors().push_back(this->inputVectors[startingIndex+i]);
	}

	return sample;
}

const std::vector<int>& Data::getDimensionsImmutable() const {
	return this->dimensions;
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

int Data::getNumSamples() const {
	return this->dimensions[0];
}

void Data::addSample(const Data& sample) {
	const std::vector<int>& sampleDimensions = sample.getDimensionsImmutable();
	for(int dimensionIndex = 1; dimensionIndex < this->dimensions.size(); ++dimensionIndex) {
		assert(this->dimensions[dimensionIndex] == sampleDimensions[dimensionIndex-1]);
	}
	assert(sampleDimensions[0] == 1);

	for(int i = 0; i < sample.getInputVectorsImmutable().size(); ++i) {
		this->getInputVectors().push_back(sample.getInputVectorsImmutable()[i]);
	}
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
