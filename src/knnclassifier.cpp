#include "knnclassifier.hpp"
#include "dataparser.hpp"

#include <vector>
#include <algorithm>
#include <assert.h>

void KnnClassifier::_initializeTypeToDistanceMap() {
	TYPE_TO_DISTANCE_FUNCTION[EUCLIDEAN] = new EuclideanDistanceMetric();
}

KnnClassifier::KnnClassifier(int k, const Data& dataset, const Data& classifications, const DistanceMetricType& distanceMetricType): _k(k), _dataset(dataset), _classifications(classifications)
{
	_initializeTypeToDistanceMap();
	_distanceMetric = TYPE_TO_DISTANCE_FUNCTION[distanceMetricType];
}

std::vector<int> KnnClassifier::classify(const Data& testSamples) {
	std::vector<int> classifications;

	for(int testSampleIndex; testSampleIndex < testSamples.getNumSamples(); ++testSampleIndex)	{
		std::vector<int> heap;
		std::unordered_map<int, double> sampleIndexToDistance;
		Data currSample = testSamples.getSample(testSampleIndex); //_dataset.getSample(sampleIndex);
		for(int datasetSampleIndex = 0; datasetSampleIndex < _dataset.getNumSamples(); ++datasetSampleIndex) {
			const Data trainingSample = _dataset.getSample(datasetSampleIndex);
			const double distance = _distanceMetric->distance(trainingSample, currSample);
			assert(distance >= 0);
			sampleIndexToDistance[datasetSampleIndex] = distance;

			if(heap.size() < _k) {
				heap.push_back(datasetSampleIndex);
				std::push_heap(heap.begin(), heap.end());
			}
			else if(heap.front() > sampleIndexToDistance[datasetSampleIndex]) {
				std::pop_heap(heap.begin(), heap.end());
				heap.pop_back();
				heap.push_back(datasetSampleIndex);
				std::push_heap(heap.begin(), heap.end());
			}
		}

		classifications.push_back(_getClassLabelFromNearestNeighbors(heap));
	}	

	return classifications;
}

// Uses majority rule to figure out which class labe to use based on
// output labels attached to nearest neighbors.  Can expand in the
// future.
int KnnClassifier::_getClassLabelFromNearestNeighbors(const std::vector<int>& closestSamples) {
	std::unordered_map<int, int> classAppearanceCounts;
	for(int sampleIndex = 0; sampleIndex < closestSamples.size(); ++sampleIndex) {
		const int label = _classifications.getValue(std::vector<int>{sampleIndex});
		if(classAppearanceCounts.find(label) == classAppearanceCounts.end()) {
			classAppearanceCounts[label] = 0;
		}
		++classAppearanceCounts[label];	
	}	

	int mostPopularClass = -1;
	int maxCountSeen = -1;
	for(auto iter = classAppearanceCounts.begin(); iter != classAppearanceCounts.end(); ++iter) {
		int label = iter->first;
		int count = iter->second;
		if(maxCountSeen < count) {
			maxCountSeen = count;
			mostPopularClass = label;
		}
	}

	return mostPopularClass;
}
