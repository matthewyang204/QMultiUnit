#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->CheckBox1, &QCheckBox::toggled,
            this, &MainWindow::updateRoundingControls);

    updateRoundingControls();

    setProgressControlsVisible(false);
    setAirFlowControlsVisible(false);
    setCurrencyControlsVisible(false);

    MainWindow::on_UnitCategorySelector_currentIndexChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setProgressControlsVisible(bool visible)
{
    ui->ProgressBar1->setVisible(visible);
}

void MainWindow::updateAuxiliaryControls()
{
    const QString category = ui->UnitCategorySelector->currentText();

    setAirFlowControlsVisible(category == QStringLiteral("Air Flow"));
    setCurrencyControlsVisible(category == QStringLiteral("Currency"));
}

void MainWindow::updateRoundingControls()
{
    ui->CheckBox2->setEnabled(!ui->CheckBox1->isChecked());
    if (ui->CheckBox1->isChecked()) {
        ui->CheckBox2->setChecked(false);
    }
}

void MainWindow::setAirFlowControlsVisible(bool visible)
{
    ui->Label5->setVisible(visible);
    ui->Label6->setVisible(visible);
    ui->Label7->setVisible(visible);
    ui->AreaInputBox->setVisible(visible);
    ui->Area2InputBox->setVisible(visible);
    ui->AreaUnitSelector->setVisible(visible);

    ui->Label5->setEnabled(visible);
    ui->Label6->setEnabled(visible);
    ui->Label7->setEnabled(visible);
    ui->AreaInputBox->setEnabled(visible);
    ui->Area2InputBox->setEnabled(visible);
    ui->AreaUnitSelector->setEnabled(visible);
}

void MainWindow::setCurrencyControlsVisible(bool visible)
{
    ui->RefreshCurrencyDataButton->setVisible(visible);
    ui->RefreshCurrencyDataButton->setEnabled(visible);
}

void MainWindow::on_CheckBox2_stateChanged(int arg1)
{
    updateRoundingControls();
}


void MainWindow::on_CheckBox1_stateChanged(int arg1)
{
    updateRoundingControls();
}

void MainWindow::on_UnitCategorySelector_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    ui->UnitSelectionBox->clear();
    ui->Unit2SelectionBox->clear();

    // Make some components invisible
    // CFM/LFM-specific stuff
    ui->Label5->setVisible(false);
    ui->AreaUnitSelector->setVisible(false);
    ui->AreaInputBox->setVisible(false);
    ui->Area2InputBox->setVisible(false);
    ui->Label6->setVisible(false);
    ui->Label7->setVisible(false);
    ui->RefreshCurrencyDataButton->setVisible(false);

    QString category = ui->UnitCategorySelector->currentText();
    QStringList units;

    if (category == "Temperature") {
        units = {
            "C",
            "F",
            "K"
        };

    } else if (category == "Speed") {
        units = {
            "MPH",
            "km/h",
            "ft/s",
            "m/s",
            "Knots",
            "Mach",
            "cm/s",
            "mm/s"
        };

    } else if (category == "Length") {
        units = {
            "Meters",
            "Yards",
            "Centimeters",
            "Millimeters",
            "Micrometers",
            "Nanometers",
            "Inches",
            "Kilometers",
            "Miles",
            "Feet",
            "Decimeters",
            "Microns",
            "Nautical Miles",
            "Astronomical Units",
            "Light Years",
            "Parsecs"
        };

    } else if (category == "Area") {
        units = {
            "Square Meters",
            "Square Yards",
            "Square Centimeters",
            "Square Millimeters",
            "Square Inches",
            "Square Kilometers",
            "Square Miles",
            "Square Feet",
            "Square Decimeters",
            "Hectares",
            "Acres",
            "Ares",
            "Square Nautical Miles",
            "Barns"
        };

    } else if (category == "Volume") {
        units = {
            "Milliliters",
            "Tablespoons",
            "Teaspoons",
            "Barrels",
            "Imperial Gallons",
            "Gallons",
            "Liters",
            "Quarts",
            "Pints",
            "Cups",
            "Fluid Ounces",
            "US Gill",
            "UK Gill",
            "Cubic Meters",
            "Cubic Yards",
            "Cubic Centimeters",
            "Cubic Millimeters",
            "Cubic Inches",
            "Cubic Kilometers",
            "Cubic Miles",
            "Cubic Feet",
            "Cubic Decimeters"
        };

    } else if (category == "Energy") {
        units = {
            "Joules",
            "Kilojoules",
            "Megajoules",
            "Watt-hours",
            "Kilowatt-hours",
            "Electronvolts",
            "Calories",
            "Kilocalories",
            "BTUs (British Thermal Units)",
            "Foot-Pounds",
            "Ergs",
            "Therms",
            "Ton TNT",
            "Horsepower-hours"
        };

    } else if (category == "Weight") {
        units = {
            "Dyne",
            "Newton",
            "Kilopond",
            "Kilonewton",
            "Pound-force",
            "Gram-force",
            "Ton-force",
            "Earth Grams",
            "Earth Ounces",
            "Earth Kilograms",
            "Earth Pounds",
            "Earth Metric Tonnes",
            "Earth Short Tonnes",
            "Earth Long Tonnes",
            "Earth Stones"
        };

    } else if (category == "Mass") {
        units = {
            "Grams",
            "Milligrams",
            "Micrograms",
            "Carats",
            "Atomic Mass Units",
            "Ounces",
            "Kilograms",
            "Pounds",
            "Metric Tonnes",
            "Short Tonnes",
            "Long Tonnes",
            "Stones"
        };

    } else if (category == "Air Flow") {
        units = {
            "CFM",
            "LFM",
            "MPH",
            "km/h",
            "ft/s",
            "m/s"
        };

        // Make the area input stuff visible
        ui->Label5->setVisible(true);
        ui->AreaUnitSelector->setVisible(true);
        ui->AreaInputBox->setVisible(true);
        ui->Area2InputBox->setVisible(true);
        ui->Label6->setVisible(true);
        ui->Label7->setVisible(true);

    } else if (category == "Angle") {
        units = {
            "Degrees",
            "Radians",
            "Gradians",
            "Arcminutes",
            "Arcseconds"
        };

    } else if (category == "Currency") {
        ui->RefreshCurrencyDataButton->setVisible(true);

        ui->UnitSelectionBox->clear();
        ui->Unit2SelectionBox->clear();

        // Not ready yet
        // UpdateCRatios();

    } else {
        QMessageBox::warning(
            this,
            "Invalid Category",
            "Please select a valid category."
            );
    }

    // Populate both unit selectors
    ui->UnitSelectionBox->addItems(units);
    ui->Unit2SelectionBox->addItems(units);

    // Set default selections
    if (ui->UnitSelectionBox->count() > 0) {
        ui->UnitSelectionBox->setCurrentIndex(0);
    }

    if (ui->Unit2SelectionBox->count() > 1) {
        ui->Unit2SelectionBox->setCurrentIndex(1);
    }
}
