#ifndef ADDITIONALCONV_H
#define ADDITIONALCONV_H

#include "mainconv.h"

#include <QString>

class AdditionalConv
{
public:
    AdditionalConv(ConversionDicts& mainconversiondicts);
    double TempConvert(QString fromUnit, QString toUnit, double userInput, bool shouldRound, bool shouldSF);
    double AFConvert(QString fromUnit, QString toUnit, double userInput, QString areaUnit, double areaWidth, double areaHeight);
private:
    ConversionDicts& primaryconversiondicts;
};

#endif // ADDITIONALCONV_H
