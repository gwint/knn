#include "distancemetric.hpp"
#include "dataparser.hpp"

#include <vector>
#include <assert.h>
#include <math.h>

double EuclideanDistanceMetric::distance(const std::vector<int>& sample1, const std::vector<int>& sample2) {
	double sumOfSquaredDifferences = 0;
	assert(sample1.size() == sample2.size());

	const int sampleSize = sample1.size();

	for(int i = 0; i < sampleSize; ++i) {
		sumOfSquaredDifferences += pow(sample1[i] - sample2[i], 2);
	}

	return sqrt(sumOfSquaredDifferences);
}

double EuclideanDistanceMetric::distance(const Data& sample1, const Data& sample2) const {
	double sumOfSquaredDifferences = 0;
	const std::vector<int>& sample1VectorValues1D = sample1.getInputVectorsImmutable();
	const std::vector<int>& sample2VectorValues1D = sample2.getInputVectorsImmutable();
	assert(sample1VectorValues1D.size() == sample2VectorValues1D.size());

	for(int i = 0; i < sample1VectorValues1D.size(); ++i) {
		sumOfSquaredDifferences += pow(sample1VectorValues1D[i] - sample2VectorValues1D[i], 2);
	}

	return sqrt(sumOfSquaredDifferences);
}
