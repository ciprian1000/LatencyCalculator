#include "LatencyCalculator.h"

#include <thread>
#include <chrono>

int main() {
	expertake::LatencyCalculator calculator(true);

	while (calculator.IsRunning()) {
		std::this_thread::sleep_for(std::chrono::microseconds(50));
	}

	return 0;
}
