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
