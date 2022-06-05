#pragma once

#include "ServiceData.h"

#include "rapidjson/document.h"

#include <string>
#include <map>

namespace expertake {

bool convert(const std::string& str, unsigned int& result);
bool isValidDate(const std::string& str);

void PrintAcumulatedData(
	const std::map<int, ServiceData>& data,
	const std::string& startDate,
	const std::string& endDate);

} // expertake
