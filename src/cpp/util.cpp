#include "util.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace expertake {

bool convert(const std::string& str, unsigned int& result) {
	try {
		result = std::stoi(str);
	} catch (std::invalid_argument ex) {
		return false;
	}
	return true;
}

bool isValidDate(const std::string& str) {
	unsigned int tmp = 0;
	std::string cpy = str;
	cpy.erase(7, 1).erase(4,1);
	return str.size() == 10 && str.at(4) == '-' && str.at(7) == '-' && convert(cpy, tmp);
}

void PrintAcumulatedData(const std::map<int, ServiceData>& data, const std::string& startDate, const std::string& endDate) {
	using namespace rapidjson;
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	Value period(kArrayType);
	period.PushBack(Value(startDate.c_str(), startDate.length()), allocator);
	period.PushBack(Value(endDate.c_str(), endDate.length()), allocator);

	document.AddMember("period", period, allocator);

	Value latencies(kArrayType);
	for (const auto& pair : data) {
		Value item(kObjectType);
		item.AddMember("serviceId", pair.first, allocator);
		item.AddMember("numberOfRequests", pair.second.requestNum, allocator);
		item.AddMember("averageResonseTimeMs", pair.second.GetAverageResponseTime(), allocator);
		latencies.PushBack(item, allocator);
	}
	document.AddMember("averageLatencies", latencies, allocator);

	rapidjson::StringBuffer buffer;
	buffer.Clear();
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result(buffer.GetString());
	std::cout << result << std::endl;
}

} // expertake
