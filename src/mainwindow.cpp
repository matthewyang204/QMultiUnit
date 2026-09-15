#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainconv.h"
#include "rounder.h"
#include "additionalconv.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainconversiondicts()
    , PrimaryConverter(mainconversiondicts)
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
    setAirFlowControlsVisible(false);
    setCurrencyControlsVisible(false);

    QString category = ui->UnitCategorySelector->currentText();
    QStringList units;

    if (category == "Temperature") {
        units = {
            "C",
            "F",
            "K"
        };

    } else if (category == "Speed") {
        for (auto it = mainconversiondicts.SpeedRatios.begin(); it != mainconversiondicts.SpeedRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Length") {
        for (auto it = mainconversiondicts.LengthRatios.begin(); it != mainconversiondicts.LengthRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Area") {
        for (auto it = mainconversiondicts.AreaRatios.begin(); it != mainconversiondicts.AreaRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Volume") {
        for (auto it = mainconversiondicts.VolumeRatios.begin(); it != mainconversiondicts.VolumeRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Energy") {
        for (auto it = mainconversiondicts.EnergyRatios.begin(); it != mainconversiondicts.EnergyRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Weight") {
        for (auto it = mainconversiondicts.WeightRatios.begin(); it != mainconversiondicts.WeightRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Mass") {
        for (auto it = mainconversiondicts.MassRatios.begin(); it != mainconversiondicts.MassRatios.end(); ++it){
            units.append(it.key());
        }

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
        setAirFlowControlsVisible(true);

    } else if (category == "Angle") {
        for (auto it = mainconversiondicts.AngleRatios.begin(); it != mainconversiondicts.AngleRatios.end(); ++it){
            units.append(it.key());
        }

    } else if (category == "Currency") {
        setCurrencyControlsVisible(true);

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

void MainWindow::ConvertWrapper() {
    bool ok;
    QString userInputStr = ui->Input->text();
    double userInput = userInputStr.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
        qWarning() << "E: User attempted to convert bad number: " << userInputStr;
        return;
    }
    QString category = ui->UnitCategorySelector->currentText();
    QString fromUnit = ui->UnitSelectionBox->currentText();
    QString toUnit = ui->Unit2SelectionBox->currentText();
    bool shouldRound;
    bool shouldSF = false;
    if (ui->CheckBox1->isChecked()){
        shouldRound = false;
    } else if (ui->CheckBox2->isChecked()){
        shouldRound = false;
        shouldSF = true;
    } else {
        shouldRound = true;
    }
    double result;
    QString areaUnit;
    double areaHeight;
    double areaWidth;
    if (category == "Temperature") {
        AdditionalConv additionalconverter(mainconversiondicts);
        result = additionalconverter.TempConvert(fromUnit, toUnit, userInput, shouldRound, shouldSF);
    } else if (category == "Air Flow") {
        areaUnit = ui->AreaUnitSelector->currentText();
        areaHeight = ui->AreaInputBox->text().toDouble();
        areaWidth = ui->Area2InputBox->text().toDouble();
        AdditionalConv additionalconverter(mainconversiondicts);
        result = additionalconverter.AFConvert(fromUnit, toUnit, userInput, areaUnit, areaWidth, areaHeight);
    } else {
        result = PrimaryConverter.Convert(category, fromUnit, toUnit, userInput, shouldRound);
    }
    if (shouldRound && category == "Air Flow"){
        double fromValue = mainconversiondicts.LengthRatios.value(areaUnit);
        double toValue = mainconversiondicts.LengthRatios.value(areaUnit);
        std::vector<double> numbers = {
            fromValue,
            toValue,
            userInput
        };
        int deccount = Rounder().GetLowestDecimalPlaces(numbers);
        result = Rounder().roundtoDecimalPlaces(result, deccount);
    } else if (shouldSF && category == "Air Flow"){
        double fromValue = mainconversiondicts.LengthRatios.value(areaUnit);
        double toValue = mainconversiondicts.LengthRatios.value(areaUnit);
        std::vector<double> numbers = {
            fromValue,
            toValue,
            userInput
        };
        int sigfigcount = SigFigs().GetSigFigsFromList(numbers);
        result = SigFigs().RoundToSigFigs(result, sigfigcount);
    } else if (shouldSF && category != "Temperature"){
        double fromValue = PrimaryConverter.GetRatioDictValue(category, fromUnit);
        double toValue = PrimaryConverter.GetRatioDictValue(category, toUnit);
        std::vector<double> numbers = {
            fromValue,
            toValue,
            userInput
        };
        int sigfigcount = SigFigs().GetSigFigsFromList(numbers);
        result = SigFigs().RoundToSigFigs(result, sigfigcount);
    }
    QString resultString = QString::number(result, 'g', 6);
    ui->ResultBox->setText(resultString);
}

void MainWindow::on_ConvertButton_clicked()
{
    ConvertWrapper();
}


void MainWindow::on_Input_returnPressed()
{
    ConvertWrapper();
}

