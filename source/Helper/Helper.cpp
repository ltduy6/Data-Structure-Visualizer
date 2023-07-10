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
