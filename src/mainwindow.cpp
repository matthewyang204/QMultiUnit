#include "mainwindow.h"
#include "ui_mainwindow.h"

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

