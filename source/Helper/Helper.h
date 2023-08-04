#pragma once
#include <cassert>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

typedef std::vector<std::pair<std::pair<int, int>, int>> listEdge;

namespace Helper {
	int rand(int minValue, int maxValue);
	Color randColor();
	bool checkExist(std::vector<int>& nums, int value);
	bool checkValidNumber(std::string& num, int minValue, int maxValue);
	bool checkValidString(std::string& input);
	float EaseCircInOut(float t, float b, float c, float d);  
	std::vector<std::string> extractStringInput(const std::string& input);
	listEdge getEdgeList(std::string filePath);
	std::vector<std::vector<int>> getMatrix(std::map<std::string, std::string>& inputs, int size);
};

Vector2 operator + (const Vector2& a, const Vector2& b);
Vector2 operator - (const Vector2& a, const Vector2& b);
Vector2 operator * (const Vector2& a, float b);
Vector2 operator / (const Vector2& a, float b);
bool operator != (const Vector2& a, const Vector2& b);
bool operator == (const Color& a, const Color& b);

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

template <typename T>
std::vector<T> extractString(std::string stringInput)
{
	std::regex pattern("(?:-?\\d+)?(?:\\s+-?\\d+)*\\s*");

	bool isMatch = std::regex_match(stringInput, pattern);

	std::vector<T> mInput; 
	if (isMatch)
	{
		T input; 
		std::stringstream ss(stringInput);
		while (ss >> input)
		{
			mInput.push_back(input);
		}
	}
	return mInput;
}

template <typename T>
std::vector<T> readFromFileRange(std::string filePath, int range)
{
	std::ifstream fin;
	fin.open(filePath);
	assert(fin.is_open() == true);
	std::vector<T> res;
	T input;
	int index = 0; 
	while (fin >> input && index < range)
	{
		res.push_back(input);
		index++;
	}
	fin.close();
	return res;
}