#pragma once
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <raylib.h>
#include <fstream>

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

template <typename T>
std::vector<T> readListFromFile(std::string filePath)
{
	std::ifstream fin;
	fin.open(filePath); 
	assert(fin.is_open() == true);
	std::vector<T> res; 
	T input; 
	while (fin >> input)
		res.push_back(input); 
	fin.close(); 
	return res; 
	
}