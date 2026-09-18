#include "mainwindow.h"
#include "darkmode.h"

#include <QApplication>
#include <QStyleFactory>
#include <QIcon>
#include <QDebug>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qDebug() << "I: Setting Retina-grade DPI on Qt 5";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    QIcon icon = QIcon(":/images/qmultiunit-1024.png");
    a.setWindowIcon(icon);
    qDebug() << "I: Icon is null:" << icon.isNull();

    setTheme(isSystemDarkMode());
    setThemeListener();

    MainWindow w;
    w.show();
    return a.exec();
}
