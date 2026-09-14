#ifndef MAINCONV_H
#define MAINCONV_H

#include <QString>
#include <QMap>
#include <QtMath>

class ConversionDicts {
public:
    QMap<QString, double> LengthRatios = {
        {"Meters", 1.0}, // Base unit
        {"Yards", 0.9144},
        {"Centimeters", 0.01},
        {"Millimeters", 0.001},
        {"Inches", 0.0254},
        {"Kilometers", 1000.0},
        {"Miles", 1609.344},
        {"Feet", 0.3048},
        {"Decimeters", 0.1},
        {"Micrometers", 0.000001},
        {"Nanometers", 0.000000001},
        {"Microns", 0.000001},
        {"Nautical Miles", 1852.0},
        {"Astronomical Units", 149597870700.0},
        {"Light Years", 9.4607e15},
        {"Parsecs", 3.0857e16}
    };

    QMap<QString, double> AreaRatios = {
        {"Square Meters", 1.0}, // Base unit
        {"Square Yards", std::pow(LengthRatios["Yards"], 2)},
        {"Square Centimeters", std::pow(LengthRatios["Centimeters"], 2)},
        {"Square Millimeters", std::pow(LengthRatios["Millimeters"], 2)},
        {"Square Inches", std::pow(LengthRatios["Inches"], 2)},
        {"Square Kilometers", std::pow(LengthRatios["Kilometers"], 2)},
        {"Square Miles", std::pow(LengthRatios["Miles"], 2)},
        {"Square Feet", std::pow(LengthRatios["Feet"], 2)},
        {"Square Decimeters", std::pow(LengthRatios["Decimeters"], 2)},
        {"Hectares", 10000.0},
        {"Acres", 4046.8564224},
        {"Ares", 100.0},
        {"Square Nautical Miles", std::pow(LengthRatios["Nautical Miles"], 2)},
        {"Barns", 1.0e-28}
    };

    QMap<QString, double> VolumeRatios = {
        {"Milliliters", 0.000001},
        {"Tablespoons", 0.0000147868},
        {"Teaspoons", 0.00000492892},
        {"Barrels", 0.158987294928},
        {"Imperial Gallons", 0.00454609},
        {"Gallons", 0.003785411784},
        {"Liters", 0.001},
        {"Quarts", 0.000946352946},
        {"Pints", 0.000473176473},
        {"Cups", 0.0002365882365},
        {"Fluid Ounces", 0.0000295735295625},
        {"US Gill", 0.00011829411825},
        {"UK Gill", 0.0001420653125},
        {"Cubic Meters", 1.0}, // Base unit
        {"Cubic Yards", std::pow(LengthRatios["Yards"], 3)},
        {"Cubic Centimeters", std::pow(LengthRatios["Centimeters"], 3)},
        {"Cubic Millimeters", std::pow(LengthRatios["Millimeters"], 3)},
        {"Cubic Inches", std::pow(LengthRatios["Inches"], 3)},
        {"Cubic Kilometers", std::pow(LengthRatios["Kilometers"], 3)},
        {"Cubic Miles", std::pow(LengthRatios["Miles"], 3)},
        {"Cubic Feet", std::pow(LengthRatios["Feet"], 3)},
        {"Cubic Decimeters", std::pow(LengthRatios["Decimeters"], 3)}
    };

    QMap<QString, double> EnergyRatios = {
        {"Joules", 1.0}, // Base unit
        {"Kilojoules", 1000.0},
        {"Megajoules", 1000000.0},
        {"Watt-hours", 3600.0},
        {"Kilowatt-hours", 3600000.0},
        {"Electronvolts", 1.602176634e-19},
        {"Calories", 4.184},
        {"Kilocalories", 4184.0},
        {"BTUs (British Thermal Units)", 1055.05585},
        {"Foot-Pounds", 1.355817948},
        {"Ergs", 0.0000001},
        {"Therms", 105505585.257},
        {"Ton TNT", 4184000000.0},
        {"Horsepower-hours", 2684519.54}
    };

    QMap<QString, double> SpeedRatios = {
        {"MPH", 0.44704},
        {"km/h", 0.277777778},
        {"ft/s", 0.3048},
        {"m/s", 1.0}, // Base unit
        {"LFM", 0.00508},
        {"Knots", 0.514444},
        {"Mach", 343.0}, // Approximately at sea level
        {"cm/s", 0.01},
        {"mm/s", 0.001}
    };

    QMap<QString, double> MassRatios = {
        {"Grams", 0.001},
        {"Milligrams", 0.000001},
        {"Micrograms", 0.000000001},
        {"Carats", 0.0002},
        {"Atomic Mass Units", 1.6605390666e-27},
        {"Ounces", 0.0283495},
        {"Kilograms", 1.0}, // Base unit
        {"Pounds", 0.45359237},
        {"Metric Tonnes", 1000.0},
        {"Short Tonnes", 907.18474},
        {"Long Tonnes", 1016.0469088},
        {"Stones", 6.35029318}
    };

    QMap<QString, double> WeightRatios = {
        {"Dyne", 0.00001},
        {"Newton", 1.0}, // Base unit
        {"Kilopond", 9.80665},
        {"Kilonewton", 1000.0},
        {"Pound-force", 4.44822},
        {"Gram-force", 0.00980665},
        {"Ton-force", 8896.443}
    };

    QMap<QString, double> AngleRatios = {
        {"Degrees", 1.0}, // Base unit
        {"Radians", 180.0 / M_PI},
        {"Gradians", 0.9},
        {"Arcminutes", 1.0 / 60.0},
        {"Arcseconds", 1.0 / 3600.0}
    };

    QMap<QString, double> CurrencyRatios;
};

class MainConverter
{
public:
    MainConverter();
};

#endif // MAINCONV_H
