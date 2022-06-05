#pragma once

#include <string>
#include <map>
#include <vector>

namespace expertake {

struct Request {
	//std::string date; //The date can be added later, but at this point it serves no purpose
	int serviceId;
	int requestId;
	int milliSecondsDelay;
};

class DailyData {
public:
	DailyData(std::string& data);

	const std::vector<Request>& GetRequests() const;
private:
	void ParseJSON(const std::string& data);

	std::vector<Request> mRequests;
};

} // expertake
