#ifndef ROUNDER_H
#define ROUNDER_H

#include <vector>
#include <QString>

class Rounder
{
public:
    Rounder();
    int GetDecimalPlaces(double number);
    int GetDecimalPlacesQStr(QString number);
    double roundtoDecimalPlaces(double number, int decimalPlaces);
    int RoundToNearestInteger(double number);
    int GetHighestDecimalPlaces(std::vector<double> numbers);
    int GetLowestDecimalPlaces(std::vector<double> numbers);
    int GetLowestDecimalPlacesQStr(std::vector<QString> numbers);
};

class SigFigs
{
public:
    static double RoundToSigFigs(double value, int sigFigs);
    static int GetSigFigs(double value);
    static int GetSigFigsQStr(QString value);
    static int GetSigFigsFromList(const std::vector<double>& values);
    static int GetSigFigsFromListQStr(const std::vector<QString>& values);
};

#endif // ROUNDER_H
