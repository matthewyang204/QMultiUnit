#include "mainconv.h"

#include <stdexcept>

MainConverter::MainConverter() {}

double MainConverter::Convert(QString category, QString fromUnit, QString toUnit, double userInput) {
    QMap<QString, double> selectedDict;
    
    if (category == "Length") {
        selectedDict = ConversionDicts().LengthRatios;
    } else if (category == "Area") {
        selectedDict = ConversionDicts().AreaRatios;
    } else if (category == "Volume") {
        selectedDict = ConversionDicts().VolumeRatios;
    } else if (category == "Energy") {
        selectedDict = ConversionDicts().EnergyRatios;
    } else if (category == "Speed") {
        selectedDict = ConversionDicts().SpeedRatios;
    } else if (category == "Mass") {
        selectedDict = ConversionDicts().MassRatios;
    } else if (category == "Weight") {
        selectedDict = ConversionDicts().WeightRatios;
    } else if (category == "Angle") {
        selectedDict = ConversionDicts().AngleRatios;
    } else if (category == "Currency") {
        selectedDict = ConversionDicts().CurrencyRatios;
    } else if (category == "Air Flow") {
        // selectedDict = ConversionDicts().AirFlowRatios;
        return 0.0;
    } else if (category == "Temperature") {
        // return TempConvert(fromUnit, toUnit, userInput);
        return 0.0;
    } else {
        throw std::invalid_argument("Invalid category");
    }

    if (!selectedDict.contains(fromUnit) || !selectedDict.contains(toUnit)) {
        throw std::invalid_argument("Invalid unit for the selected category");
    }

    return 0.0;
}
