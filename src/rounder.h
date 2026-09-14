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

#endif // ROUNDER_H
