#include "DailyData.h"

#include "rapidjson/document.h"

namespace expertake {

//static const char* DATE = "date";
static const char* SERVICE_ID = "serviceId";
static const char* REQUEST_ID = "requestId";
static const char* MILLISECONDS_DELAY = "milliSecondsDelay";

static int GetInt(const rapidjson::Value& request, const char* name) {
	assert(request.HasMember(name));
	assert(request[name].IsInt());
	return request[name].GetInt();
}

DailyData::DailyData(std::string& data) {
	ParseJSON(data);
}

const std::vector<Request>& DailyData::GetRequests() const {
	return mRequests;
}

void DailyData::ParseJSON(const std::string& data) {
	using namespace rapidjson;
	Document document;
	document.Parse(data.c_str());
	assert(document.IsArray());
	const Value& _array = document.GetArray();

	for (SizeType i = 0; i < _array.Size(); i++) {
		assert(_array[i].IsObject());
		const Value& object = _array[i].GetObject();

		Request request;
		request.serviceId			= GetInt(object, SERVICE_ID);
		request.requestId			= GetInt(object, REQUEST_ID);
		request.milliSecondsDelay	= GetInt(object, MILLISECONDS_DELAY);

		mRequests.push_back(request);
	}
}

} // expertake
