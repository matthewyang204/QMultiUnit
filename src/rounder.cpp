#include "rounder.h"

#include <cmath>
#include <string>

Rounder::Rounder() {}

int Rounder::GetDecimalPlaces(double number)
{
    std::string numberStr = std::to_string(number);
    size_t decimalPos = numberStr.find('.');
    if (decimalPos == std::string::npos) {
        return 0; // No decimal point found
    }
    return numberStr.length() - decimalPos - 1;
}

double Rounder::roundtoDecimalPlaces(double number, int decimalPlaces)
{
    double factor = std::pow(10.0, decimalPlaces);
    return static_cast<int>(std::round(number * factor) / factor);
}

int Rounder::RoundToNearestInteger(double number)
{
    return static_cast<int>(std::round(number));
}

int Rounder::GetHighestDecimalPlaces(std::vector<double> numbers)
{
    int maxDecimalPlaces = 0;
    for (double number : numbers) {
        int decimalPlaces = GetDecimalPlaces(number);
        if (decimalPlaces > maxDecimalPlaces) {
            maxDecimalPlaces = decimalPlaces;
        }
    }
    return maxDecimalPlaces;
}
