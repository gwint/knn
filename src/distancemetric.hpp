#ifndef DISTANCE_METRIC_H
#define DISTANCE_METRIC_H

#include <vector>

#include "dataparser.hpp"

class DistanceMetric {
	virtual int distance(Data, const std::vector<int>&, const std::vector<int>&);
}

#endif
