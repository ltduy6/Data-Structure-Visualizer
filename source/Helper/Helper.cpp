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

float Helper::EaseCircInOut(float t, float b, float c, float d)
{
    if ((t /= d / 2.0f) < 1.0f) return (-c / 2.0f * (sqrtf(1.0f - t * t) - 1.0f) + b);
    t -= 2.0f; return (c / 2.0f * (sqrtf(1.0f - t * t) + 1.0f) + b);
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
