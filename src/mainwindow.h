#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void updateAuxiliaryControls();
    void updateRoundingControls();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
