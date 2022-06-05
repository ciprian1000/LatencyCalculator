#include "ServiceData.h"

#include <numeric>

namespace expertake {

unsigned int ServiceData::GetAverageResponseTime() const {
	return std::accumulate(responseTimes.begin(), responseTimes.end(), 0) / responseTimes.size();
}

} // expertake
