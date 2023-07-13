#pragma once
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <raylib.h>

namespace Helper {
	int rand(int minValue, int maxValue);
	bool checkExist(std::vector<int>& nums, int value);
	bool checkValidNumber(std::string& num, int minValue, int maxValue);
	float EaseCircInOut(float t, float b, float c, float d); 
};

Vector2 operator + (const Vector2& a, const Vector2& b);
Vector2 operator - (const Vector2& a, const Vector2& b);
Vector2 operator * (const Vector2& a, float b);
Vector2 operator / (const Vector2& a, float b);