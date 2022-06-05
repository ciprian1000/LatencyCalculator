#pragma once

#include "InterfaceController.h"
#include "DailyData.h"
#include "DataLoader.h"

#include <memory>
#include <future>
#include <map>

namespace expertake {

class LatencyCalculator {
public:
	LatencyCalculator(bool autoStart);
	~LatencyCalculator() = default;

	void Start();
	bool IsRunning() const;

private:
	void Stop();
	void Run();
	void ReadStartDate();
	void ReadEndDate();
	bool AreDatesInOrder(const std::string& startDate, const std::string& endDate);
	std::string ReadDate();
	void Calculate();
	void LoadAvailableDataList();
	void PrintAvailableDataList();
	const std::vector<std::string>& GetDataList() const;

	bool mIsRunning;
	std::future<void> mRun;
	std::string mStartDate;
	std::string mEndDate;
	std::unique_ptr<InterfaceController> mInterfaceController;
	std::vector<std::string> mDataList;
	std::map<std::string, DailyData> mDailyData;
	std::unique_ptr<DataLoader> mDataLoader;
};

} // expertake
