#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainconv.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setProgressControlsVisible(bool visible);
    void setAirFlowControlsVisible(bool visible);
    void setCurrencyControlsVisible(bool visible);
    void setCurrencyControlsEnabled(bool enabled);
    ConversionDicts mainconversiondicts;

private slots:
    void updateAuxiliaryControls();
    void updateRoundingControls();

    void on_CheckBox2_stateChanged(int arg1);

    void on_CheckBox1_stateChanged(int arg1);

    void on_UnitCategorySelector_currentIndexChanged(int index);

    void on_ConvertButton_clicked();

    void on_Input_returnPressed();

    void on_RefreshCurrencyDataButton_clicked();

private:
    Ui::MainWindow *ui;
    MainConverter PrimaryConverter;

    void ConvertWrapper();
};
#endif // MAINWINDOW_H
