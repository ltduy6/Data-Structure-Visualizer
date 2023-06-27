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
