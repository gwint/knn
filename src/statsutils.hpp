#ifndef STATS_UTILS_H
#define STATS_UTILS_H

#include "dataparser.hpp"

#include <vector>

class StatsUtils {
	public:
		static std::vector<Data> getSplitData(const Data& data, const Data& classifications, double testProportions);
		static std::vector<std::vector<double>> getConfusionMatrix(const Data&, const Data&, const std::vector<int>& labels);

	private:
		static double _getTrueNegativeProportion(const Data& actual, const Data& test, const std::vector<int>&);
		static double _getTruePositiveProportion(const Data& actual, const Data& test, const std::vector<int>&);
		static double _getFalseNegativeProportion(const Data& actual, const Data& test, const std::vector<int>&);
		static double _getFalsePositiveProportion(const Data& actual, const Data& test, const std::vector<int>&);

};
#endif
