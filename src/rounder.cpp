#include "rounder.h"
#include "sigfig/SigFig.h"

#include <algorithm>
#include <cmath>
#include <QString>
#include <QRegularExpression>

Rounder::Rounder() {}

int Rounder::GetDecimalPlaces(double number)
{
    if (!std::isfinite(number)) {
        return 0;
    }

    const QString numberString = QString::number(number, 'g', 15);
    const int lowerExponentMarker = numberString.indexOf('e');
    const int upperExponentMarker = numberString.indexOf('E');
    const int exponentMarker = lowerExponentMarker != -1
                                    ? lowerExponentMarker
                                    : upperExponentMarker;
    const QString mantissa = exponentMarker == -1
                                 ? numberString
                                 : numberString.left(exponentMarker);
    const int decimalPoint = mantissa.indexOf('.');
    const int exponent = exponentMarker == -1
                             ? 0
                             : numberString.mid(exponentMarker + 1).toInt();
    const int mantissaDecimals = decimalPoint == -1
                                     ? 0
                                     : mantissa.length() - decimalPoint - 1;

    return std::max(0, mantissaDecimals - exponent);
}

int Rounder::GetDecimalPlacesQStr(QString number){
    const QString numberString = number;
    const int lowerExponentMarker = numberString.indexOf('e');
    const int upperExponentMarker = numberString.indexOf('E');
    const int exponentMarker = lowerExponentMarker != -1
                                    ? lowerExponentMarker
                                    : upperExponentMarker;
    const QString mantissa = exponentMarker == -1
                                 ? numberString
                                 : numberString.left(exponentMarker);
    const int decimalPoint = mantissa.indexOf('.');
    const int exponent = exponentMarker == -1
                             ? 0
                             : numberString.mid(exponentMarker + 1).toInt();
    const int mantissaDecimals = decimalPoint == -1
                                     ? 0
                                     : mantissa.length() - decimalPoint - 1;

    return std::max(0, mantissaDecimals - exponent);
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

int Rounder::GetLowestDecimalPlacesQStr(std::vector<QString> numbers)
{
    if (numbers.empty()) {
        return 0;
    }

    int minDecimalPlaces = GetDecimalPlacesQStr(numbers[0]);

    for (size_t i = 1; i < numbers.size(); ++i) {
        int decimalPlaces = GetDecimalPlacesQStr(numbers[i]);

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
        if (c == 'e' || c == 'E'){
            break;
        }
        if (c.isDigit()) {
            ++sigFigs;
        }
    }

    return sigFigs;
}

int SigFigs::GetSigFigsQStr(QString value)
{
    QString strValue = value;

    if (strValue.startsWith('+') || strValue.startsWith('-')) {
        strValue.remove(0, 1);
    }

    const int exponentMarker = strValue.indexOf(QRegularExpression("[eE]"));
    if (exponentMarker != -1) {
        strValue = strValue.left(exponentMarker);
    }

    int firstSignificant = 0;

    while (firstSignificant < strValue.length() &&
           strValue[firstSignificant] == '0') {
        ++firstSignificant;
    }

    int sigFigs = 0;

    for (int i = firstSignificant; i < strValue.length(); ++i) {
        if (strValue[i].isDigit()) {
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

int SigFigs::GetSigFigsFromListQStr(const std::vector<QString>& values)
{
    int maxSigFigs = 0;

    for (QString value : values) {
        int sigFigs = GetSigFigsQStr(value);

        if (sigFigs > maxSigFigs) {
            maxSigFigs = sigFigs;
        }
    }

    return maxSigFigs;
}
