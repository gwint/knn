#ifndef STATS_UTILS_H
#define STATS_UTILS_H

#include "dataparser.hpp"

#include <vector>

class StatsUtils {
	public:
		static std::vector<Data> getSplitData(const Data& data, const Data& classifications, double testProportions);
		static std::vector<std::vector<int>> getConfusionMatrix(const Data&, const Data&);
};
#endif
