#pragma once
#include <chrono>
#include <iostream>

class Timing
{
private:
	const char* blockName;
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	bool stopped;
public:
	Timing(const char* name) :stopped(false), blockName(name) {
		startTime = std::chrono::high_resolution_clock().now();
	}
	~Timing() {
		if (!stopped) {
			stop();
		}
	}

	void stop() {
		auto endTime = std::chrono::high_resolution_clock().now();
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();
		printf("%s: %d \n", blockName, (end - start));
	}
};

