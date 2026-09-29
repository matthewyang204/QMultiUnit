#include "mainwindow.h"
#include "darkmode.h"

#include <QApplication>
#include <QStyleFactory>
#include <QIcon>
#include <QDebug>
#include <QTranslator>

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

    QString systemLang = QLocale::system().name();
    qDebug() << "I: Locale:" << systemLang;
    QString lang = qEnvironmentVariable("LANG");
    lang = lang.left(lang.lastIndexOf('.'));
    qDebug() << "I: Terminal Locale:" << lang;
    QString lang2use;
    if (systemLang.isEmpty()) {lang2use = lang;}
    else if (lang.isEmpty()) {lang2use = systemLang;}
    else if (systemLang != lang) {lang2use = lang;}
    else {lang2use = systemLang;}
    QTranslator translator;
    if (translator.load(QLocale(lang2use), "QMultiUnit", "_", ":/translations")) {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
