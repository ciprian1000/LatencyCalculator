#include "LatencyCalculator.h"

#include "ServiceData.h"

#include "util.h"

#include <iostream>
#include <algorithm>
#include <filesystem>

namespace expertake {

static const char* SET_START_DATE = "Please set the start date.";
static const char* SET_END_DATE = "Please set the end date.";
static const char* INSERT_START_DATE = "Insert start date:";
static const char* INSERT_END_DATE = "Insert end date:";
static const char* VALID_DATE_INEXISTENT = " is a valid date but we don't have that data point.";
static const char* EMPTY_DATA_LIST = "No data points available.";
static const char* AVAILABLE_DATA_POINTS = "Data points available.";
static const char* INVALID_DATES = " [start date] is after the [end date] ";
static const char* RESET_DATES = "Start date and end date have been reset.";

LatencyCalculator::LatencyCalculator(bool autoStart)
	: mIsRunning(false)
{
	LoadAvailableDataList();

	if (autoStart) {
		Start();
	}
}

void LatencyCalculator::Stop() {
	std::system("cls");
	mIsRunning = false;
}

void LatencyCalculator::Run() {
	while (mIsRunning) {
		mInterfaceController->Reset();
	}
}

void LatencyCalculator::ReadStartDate() {
	std::system("cls");
	std::cout << INSERT_START_DATE << std::endl;
	
	std::string date = ReadDate();
	if (date.empty()) {
		return;
	}

	if (mEndDate.empty() || AreDatesInOrder(date, mEndDate)) {
		mStartDate = date;
	} else {
		std::cout << date << INVALID_DATES << mEndDate << std::endl;
	}
}

std::string LatencyCalculator::ReadDate() {
	std::string date;
	std::cin >> date;

	if (isValidDate(date)) {
		auto found = std::find(mDataList.begin(), mDataList.end(), date);
		if (found == mDataList.end()) {
			std::cout << date << VALID_DATE_INEXISTENT << std::endl;
			PrintAvailableDataList();
		}
		else {
			return date;
		}
	}
	else {
		std::cout << date << " is not a valid date." << std::endl;
	}

	return "";
}

bool LatencyCalculator::AreDatesInOrder(const std::string& startDate, const std::string& endDate) {
	auto foundStart = std::find(mDataList.begin(), mDataList.end(), startDate);
	auto foundEnd = std::find(foundStart, mDataList.end(), endDate);
	return foundEnd != mDataList.end();
}

void LatencyCalculator::ReadEndDate() {
	std::system("cls");
	std::cout << INSERT_END_DATE << std::endl;

	std::string date = ReadDate();
	if (date.empty()) {
		return;
	}

	if (mStartDate.empty() || AreDatesInOrder(mStartDate, date)) {
		mEndDate = date;
	}
	else {
		std::cout << mStartDate << INVALID_DATES << date << std::endl;
	}
}

void LatencyCalculator::Calculate() {
	std::system("cls");
	if (mStartDate.empty()) {
		std::cout << SET_START_DATE << std::endl;
		return;
	}
	if (mEndDate.empty()) {
		std::cout << SET_END_DATE << std::endl;
		return;
	}

	auto foundStart = std::find(mDataList.begin(), mDataList.end(), mStartDate);
	auto foundEnd = std::find(foundStart, mDataList.end(), mEndDate);
	std::vector<std::reference_wrapper<DailyData>> dataPoints;

	std::for_each(
		foundStart,
		foundEnd + 1,
		[this, &dataPoints](const std::string& item) {
			if (!mDailyData.count(item)) {
				mDailyData.insert( { item, mDataLoader->LoadData(item) } );
			}

			dataPoints.push_back(mDailyData.at(item));
		});

	std::map<int, ServiceData> cumulatedData;
	for (const auto& item : dataPoints) {
		for (const auto& request : item.get().GetRequests()) {
			if (!cumulatedData.count(request.serviceId)) {
				cumulatedData.insert( { request.serviceId, ServiceData() } );
			}

			cumulatedData.at(request.serviceId).requestNum++;
			cumulatedData.at(request.serviceId).responseTimes.push_back(request.milliSecondsDelay);
		}
	}
	PrintAcumulatedData(cumulatedData, mStartDate, mEndDate);

	mStartDate.clear();
	mEndDate.clear();

	std::cout << RESET_DATES << std::endl;
}

void LatencyCalculator::Start() {
	if (mIsRunning) {
		return;
	}

	mInterfaceController = std::make_unique<InterfaceController>();
	mInterfaceController->AddMenuItem(MenuItem(
		"Print available data points", [this]() { PrintAvailableDataList(); }
	));
	mInterfaceController->AddMenuItem(MenuItem(
		"Set start date: format yyyy-mm-dd", [this]() { ReadStartDate(); }
	));
	mInterfaceController->AddMenuItem(MenuItem(
		"Set end date: format yyyy-mm-dd", [this]() { ReadEndDate(); }
	));
	mInterfaceController->AddMenuItem(MenuItem(
		"Calculate", [this]() { Calculate(); }
	));
	mInterfaceController->AddMenuItem(MenuItem(
		"Exit", [this]() { Stop(); }
	));

	mDataLoader = std::make_unique<DataLoader>();

	mIsRunning = true;
	mRun = std::async([this]() { Run(); });
}

bool LatencyCalculator::IsRunning() const {
	return  mIsRunning;
}

void LatencyCalculator::LoadAvailableDataList() {
	using namespace std::filesystem;
	std::string path = "data/";
	auto x = directory_iterator(path);
	for (const auto& entry : x) {
		auto& path = entry.path().string();
		std::size_t foundStart = path.find('/') + 1;
		std::size_t foundEnd = path.find('.');
		std::string fileName = path.substr(foundStart, foundEnd - foundStart);
		mDataList.push_back(fileName);
	}
}

void LatencyCalculator::PrintAvailableDataList() {
	std::system("cls");
	if (mDataList.empty()) {
		std::cout << EMPTY_DATA_LIST << std::endl;
	} else {
		std::cout << AVAILABLE_DATA_POINTS << std::endl;
		for (auto& point : mDataList) {
			std::cout << point << std::endl;
		}
	}
}

const std::vector<std::string>& LatencyCalculator::GetDataList() const {
	return mDataList;
}

} // expertake
