#pragma once
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <string>

namespace Helper {
	int rand(int minValue, int maxValue);
	bool checkExist(std::vector<int>& nums, int value);
	bool checkValidNumber(std::string& num, int minValue, int maxValue);
};

