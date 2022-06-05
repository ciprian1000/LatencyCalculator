#pragma once

#include "DailyData.h"

namespace expertake {

class DataLoader {
public:
	DataLoader();
	~DataLoader() = default;

	DailyData LoadData(const std::string& date);
};

} // expertake
