#ifndef ROUNDER_H
#define ROUNDER_H

#include <vector>

class Rounder
{
public:
    Rounder();
    int GetDecimalPlaces(double number);
    double roundtoDecimalPlaces(double number, int decimalPlaces);
    int RoundToNearestInteger(double number);
    int GetHighestDecimalPlaces(std::vector<double> numbers);
};

class SigFigs
{
public:
    static double RoundToSigFigs(double value, int sigFigs);
    static int GetSigFigs(double value);
    static int GetSigFigsFromList(const std::vector<double>& values);
};

#endif // ROUNDER_H
