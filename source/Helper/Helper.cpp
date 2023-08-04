#include "Helper.h"

int Helper::rand(int minValue, int maxValue)
{
    std::mt19937 mt{
        static_cast<std::mt19937::result_type>(
            std::chrono::steady_clock::now().time_since_epoch().count())};
    if (minValue > maxValue)
    {
        std::swap(minValue, maxValue);
    }
    return mt() % (maxValue - minValue + 1) + minValue;
}

Color Helper::randColor()
{
    std::mt19937 mt{
        static_cast<std::mt19937::result_type>(
            std::chrono::steady_clock::now().time_since_epoch().count()) };
    Color res; 
    res.r = mt() % 255 + 1; 
    res.g = mt() % 255 + 1; 
    res.b = mt() % 255 + 1;
    res.a = 255;

    return res;
}

bool Helper::checkExist(std::vector<int>& nums, int value)
{
    for (auto num : nums)
        if (num == value)
            return true; 
    return false; 
}

bool Helper::checkValidNumber(std::string& num, int minValue, int maxValue)
{
    if (num.size() == 0)
        return false; 
    for (int i = 0; i < num.size(); ++i)
    {
        if (i == 0 && num[i] == '-')
            continue; 
        if (isdigit(num[i]) == false)
            return false; 
    }
    int sum = std::stoi(num);
    if (sum >= minValue && sum <= maxValue)
        return true; 
    return false;
}

bool Helper::checkValidString(std::string& input)
{
    int length = input.length();
    if (length == 0)
        return false; 
    for (int i = 0; i < length; ++i)
    {
        if (input[i] < 'A' || (input[i] > 'Z' && input[i] < 'a') || (input[i] > 'z'))
            return false; 
    }
    return true; 
}

float Helper::EaseCircInOut(float t, float b, float c, float d)
{
    if ((t /= d / 2.0f) < 1.0f) return (-c / 2.0f * (sqrtf(1.0f - t * t) - 1.0f) + b);
    t -= 2.0f; return (c / 2.0f * (sqrtf(1.0f - t * t) + 1.0f) + b);
}

std::vector<std::string> Helper::extractStringInput(const std::string& input)
{
    std::vector<std::string> res; 
    std::istringstream iss(input); 
    std::string word; 

    while (iss >> word)
    {
        if (checkValidString(word))
            res.push_back(word); 
    }
    return res;
}

listEdge Helper::getEdgeList(std::string filePath)
{
    std::ifstream fin; 
    fin.open(filePath);
    assert(fin.is_open());

    listEdge res; 
    int u{ 0 }, v{ 0 }, w{ 0 };
    while (fin >> u >> v >> w)
    {
        res.push_back(std::make_pair(std::make_pair(u, v), w));
    }

    fin.close();
    return res;
}

std::vector<std::vector<int>> Helper::getMatrix(std::map<std::string, std::string>& inputs, int size)
{
    std::vector<std::vector<int>> res;
    for (int i = 0; i < size; ++i)
    {
        std::vector<int> row; 
        for (int j = 0; j < size; ++j)
        {
            if (checkValidNumber(inputs[std::to_string(i) + std::to_string(j)], 1, 200))
            {
                row.push_back(std::stoi(inputs[std::to_string(i) + std::to_string(j)]));
            }
            else if (checkValidNumber(inputs[std::to_string(j) + std::to_string(i)], 1, 200))
            {
                row.push_back(std::stoi(inputs[std::to_string(j) + std::to_string(i)]));
            }
            else
                row.push_back(-1);
        }
        res.push_back(row);
    }
    return res;
}

Vector2 operator+(const Vector2& a, const Vector2& b)
{
    return Vector2{ a.x + b.x, a.y + b.y};
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
    return Vector2{a.x - b.x, a.y - b.y};
}

Vector2 operator*(const Vector2& a, float b)
{
    return Vector2{ a.x * b, a.y * b };
}

Vector2 operator/(const Vector2& a, float b)
{
    return Vector2{ a.x / b, a.y / b };
}

bool operator!=(const Vector2& a, const Vector2& b)
{
    return (a.x != b.x || a.y != b.y);
}

bool operator==(const Color& a, const Color& b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b);
}
