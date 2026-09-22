#include "additionalconv.h"
#include "mainconv.h"

#include <stdexcept>

AdditionalConv::AdditionalConv(ConversionDicts& mainconversiondicts)
    : primaryconversiondicts(mainconversiondicts)
{}

double AdditionalConv::TempConvert(QString fromUnit, QString toUnit, double userInput) {
    double calcTemp;

    if (fromUnit == "C" && toUnit == "F"){
        calcTemp = (userInput * (9.0/5.0)) + 32.0;
    } else if (fromUnit == "C" && toUnit == "K"){
        calcTemp = userInput + 273.15;
    } else if (fromUnit == "F" && toUnit == "C"){
        calcTemp = (userInput - 32.0) * 5.0 / 9.0;
    } else if (fromUnit == "F" && toUnit == "K"){
        calcTemp = (userInput - 32.0) * 5.0 / 9.0 + 273.15;
    } else if (fromUnit == "K" && toUnit == "C"){
        calcTemp = userInput - 273.15;
    } else if (fromUnit == "K" && toUnit == "F"){
        calcTemp = (userInput - 273.15) * 9.0 / 5.0 + 32.0;
    } else if (fromUnit == toUnit){
        return userInput;
    } else {
        throw std::invalid_argument("Invalid Temperature conversion.");
    }

    return calcTemp;
}

double AdditionalConv::AFConvert(QString fromUnit, QString toUnit, double userInput, QString areaUnit, double areaWidth, double areaHeight){
    double calcTemp;
    double area;

    if (fromUnit == "CFM" || toUnit == "CFM") {
        double width = areaWidth *
                       primaryconversiondicts.LengthRatios.value(areaUnit) /
                       primaryconversiondicts.LengthRatios.value("Feet");

        double height = areaHeight *
                        primaryconversiondicts.LengthRatios.value(areaUnit) /
                        primaryconversiondicts.LengthRatios.value("Feet");

        area = width * height;

        if (area <= 0) {
            throw std::invalid_argument(
                "Your area is 0 or negative. This will give you meaningless results."
                );
        }
    }

    if (fromUnit == "CFM" && toUnit == "LFM") {
        calcTemp = userInput / area;
        return calcTemp;

    } else if (fromUnit == "LFM" && toUnit == "CFM") {
        calcTemp = userInput * area;
        return calcTemp;

    } else if (fromUnit == toUnit) {
        return userInput;

    } else if (primaryconversiondicts.SpeedRatios.contains(fromUnit) ||
               primaryconversiondicts.SpeedRatios.contains(toUnit)) {

        if (fromUnit == "CFM") {
            userInput = userInput / area;
            fromUnit = "LFM";

        } else if (toUnit == "CFM") {
            calcTemp =
                userInput *
                primaryconversiondicts.SpeedRatios.value(fromUnit) /
                primaryconversiondicts.SpeedRatios.value("LFM");

            return calcTemp * area;
        }

        calcTemp =
            userInput *
            primaryconversiondicts.SpeedRatios.value(fromUnit) /
            primaryconversiondicts.SpeedRatios.value(toUnit);

        return calcTemp;
    }

    throw std::invalid_argument("Invalid Airflow conversion.");
}
