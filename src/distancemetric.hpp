#ifndef DISTANCE_METRIC_H
#define DISTANCE_METRIC_H

#include <vector>

#include "dataparser.hpp"

class DistanceMetric {
	public:
	virtual	double distance(const std::vector<int>& sample1, const std::vector<int>& sample2) {return -1;}
};

class EuclideanDistanceMetric: public DistanceMetric {
	public:
		double distance(const std::vector<int>& sample1, const std::vector<int>& sample2);
};
#endif
