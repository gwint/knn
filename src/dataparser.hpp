#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <vector>
#include <unordered_map>
#include <string>

/* Represents the data used by the Knn algorithm (training set, testing set).
   Meant to be created via the retrieveFromFile static method. */
class Data {
	private: 
		std::vector<int> dimensions;
		std::vector<int> inputVectors;
		std::vector<int> classifications;

	public:
		static Data retrieveFromCSVFile(std::string filename);
		static Data retrieveClassificationsFromCSVFile(std::string filename);
		// Collection of number of elements along each axis for each
		// dimension in data cube.  e.g [2, 3, 4] for a dataset whose
		// input data consists of 2 sets of 3 rows and 4 columns.  A typical
		// set of table data with rows and columns would look like [2, 3] 
		// (2 samples, and 3 values per sample)
		std::vector<int>& getDimensions();
		std::vector<int>& getInputVectors();
		const std::vector<int>& getInputVectorsImmutable() const;
		int getValue(std::vector<int> indices);
		Data getSample(const int index) const;
		int getNumSamples() const;
		void addSample(const Data&);
		const std::vector<int>& getDimensionsImmutable() const;
		bool operator==(const Data&) const;
};

/* Utility class for handling all data parsing for input data.  Will handle any alterations
   that must be made to input data to allow it to be represented internally.
 */
class DataParser {
	public:
		static int parseAsInt(std::string value);

	private:
		DataParser();
};

#endif
