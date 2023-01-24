#ifndef STATS_UTILS_H
#define STATS_UTILS_H

#include "dataparser.hpp"

#include <vector>

class StatsUitls {
	static std::vector<Data> getSplitData(const Data& data, const Data& classifications);
};
#endif
