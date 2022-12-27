#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <vector>
#include <unordered_map>
#include <string>

/* Represents the data used by the Knn algorithm (training set, testing set).
   Meant to be created via the retrieveFromFile static method. */
class Data {
	private: 
		std::vector<int> trainingData;
		std::vector<int> trainingResults;
		std::vector<int> testingData;

	public:
		static Data retrieveFromFile(std::string filename);
};

/* Utility class for handling all data parsing for input data.  Will handle any alterations
   that must be made to input data to allow it to be represented internally.
 */
class DataParser {
};

#endif
