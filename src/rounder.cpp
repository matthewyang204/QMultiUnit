#include "rounder.h"

#include <cmath>
#include <string>
#include <QString>

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
    return std::round(number * factor) / factor;
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

int Rounder::GetLowestDecimalPlaces(std::vector<double> numbers)
{
    if (numbers.empty()) {
        return 0;
    }

    int minDecimalPlaces = GetDecimalPlaces(numbers[0]);

    for (size_t i = 1; i < numbers.size(); ++i) {
        int decimalPlaces = GetDecimalPlaces(numbers[i]);

        if (decimalPlaces < minDecimalPlaces) {
            minDecimalPlaces = decimalPlaces;
        }
    }

    return minDecimalPlaces;
}

double SigFigs::RoundToSigFigs(double value, int sigFigs)
{
    if (value == 0) {
        return 0;
    }

    double scale = std::pow(
        10.0,
        std::floor(std::log10(std::abs(value))) + 1 - sigFigs
        );

    return std::round(value / scale) * scale;
}

int SigFigs::GetSigFigs(double value)
{
    if (value == 0) {
        return 1;
    }

    QString strValue = QString::number(value, 'g', 17);

    int sigFigs = 0;

    for (const QChar& c : strValue) {
        if (c.isDigit()) {
            ++sigFigs;
        }
    }

    return sigFigs;
}

int SigFigs::GetSigFigsFromList(const std::vector<double>& values)
{
    int maxSigFigs = 0;

    for (double value : values) {
        int sigFigs = GetSigFigs(value);

        if (sigFigs > maxSigFigs) {
            maxSigFigs = sigFigs;
        }
    }

    return maxSigFigs;
}
