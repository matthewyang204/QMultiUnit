#include "mainwindow.h"
#include "darkmode.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    setTheme(isSystemDarkMode());
    setThemeListener();

    MainWindow w;
    w.show();
    return a.exec();
}
