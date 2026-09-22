#include "mainconv.h"

#include <stdexcept>

ConversionDicts::ConversionDicts() {
    for (auto it = MassRatios.begin(); it != MassRatios.end(); ++it){
        WeightRatios["Earth " + it.key()] = it.value();
    }
}

MainConverter::MainConverter(ConversionDicts& mainconversiondicts)
    : primaryconversiondicts(mainconversiondicts)
{}

double MainConverter::Convert(QString category, QString fromUnit, QString toUnit, double userInput) {
    QMap<QString, double> selectedDict;
    
    if (category == "Length") {
        selectedDict = primaryconversiondicts.LengthRatios;
    } else if (category == "Area") {
        selectedDict = primaryconversiondicts.AreaRatios;
    } else if (category == "Volume") {
        selectedDict = primaryconversiondicts.VolumeRatios;
    } else if (category == "Energy") {
        selectedDict = primaryconversiondicts.EnergyRatios;
    } else if (category == "Speed") {
        selectedDict = primaryconversiondicts.SpeedRatios;
    } else if (category == "Mass") {
        selectedDict = primaryconversiondicts.MassRatios;
    } else if (category == "Weight") {
        selectedDict = primaryconversiondicts.WeightRatios;
    } else if (category == "Angle") {
        selectedDict = primaryconversiondicts.AngleRatios;
    } else if (category == "Currency") {
        selectedDict = primaryconversiondicts.CurrencyRatios;
    } else if (category == "Air Flow") {
        throw std::invalid_argument("Unable to convert unit type `Air Flow`. Use helper function located in additionalconv.cpp instead.");
    } else if (category == "Temperature") {
        throw std::invalid_argument("Unable to convert unit type `Temperature`. Use helper function located in additionalconv.cpp instead.");
    } else {
        throw std::invalid_argument("Invalid category");
    }

    if (!selectedDict.contains(fromUnit) || !selectedDict.contains(toUnit)) {
        throw std::invalid_argument("Invalid unit for the selected category");
    }

    return userInput * (selectedDict[fromUnit] / selectedDict[toUnit]);
}

double MainConverter::GetRatioDictValue(QString category, QString unit){
    QMap<QString, double> selectedDict;

    if (category == "Length") {
        selectedDict = primaryconversiondicts.LengthRatios;
    } else if (category == "Area") {
        selectedDict = primaryconversiondicts.AreaRatios;
    } else if (category == "Volume") {
        selectedDict = primaryconversiondicts.VolumeRatios;
    } else if (category == "Energy") {
        selectedDict = primaryconversiondicts.EnergyRatios;
    } else if (category == "Speed") {
        selectedDict = primaryconversiondicts.SpeedRatios;
    } else if (category == "Mass") {
        selectedDict = primaryconversiondicts.MassRatios;
    } else if (category == "Weight") {
        selectedDict = primaryconversiondicts.WeightRatios;
    } else if (category == "Angle") {
        selectedDict = primaryconversiondicts.AngleRatios;
    } else if (category == "Currency") {
        selectedDict = primaryconversiondicts.CurrencyRatios;
    } else if (category == "Air Flow") {
        throw std::invalid_argument("Unable to convert unit type `Air Flow`. Use helper function located in additionalconv.cpp instead.");
    } else if (category == "Temperature") {
        throw std::invalid_argument("Unable to convert unit type `Temperature`. Use helper function located in additionalconv.cpp instead.");
    } else {
        throw std::invalid_argument("Invalid category");
    }

    return selectedDict[unit];
}
