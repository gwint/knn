#ifndef KNN_CLASSIFIER_H
#define KNN_CLASSIFIER_H

#include "dataparser.hpp"
#include "distancemetric.hpp"

#include <vector>
#include <unordered_map>

enum DistanceMetricType {
	EUCLIDEAN = 0
};

/// Class representing a K-nearest neighbors classifier.  Currently,
/// only data containing integer datapoints is allowed.
class KnnClassifier {
	private:
		DistanceMetric* _distanceMetric;
		Data _dataset;
		int _k;
		double _getDistance();
		void _initializeTypeToDistanceMap();
		std::unordered_map<DistanceMetricType, DistanceMetric*> TYPE_TO_DISTANCE_FUNCTION;

	public:
		KnnClassifier(int k, const Data& dataset, const DistanceMetricType& distanceMetricType);
		int classify(const std::vector<int>& sample);
};

#endif
