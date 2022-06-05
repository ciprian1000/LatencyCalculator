#pragma once

#include <vector>

namespace expertake {

struct ServiceData {
	unsigned int requestNum = 0;
	std::vector<int> responseTimes;
		
	unsigned int GetAverageResponseTime() const;
};

} // expertake
