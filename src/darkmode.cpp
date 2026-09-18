#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QColor>
#include <QStyle>
#include <QStyleHints>
#include <QGuiApplication>

QPalette createDarkPalette() {
    QPalette darkPalette;

    // Base surface colors
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    // Highlight / Selection colors
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    // Disabled state colors
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));

    return darkPalette;
}

void setTheme(bool isDark){
    qApp->setStyle(QStyleFactory::create("Fusion"));

    if (isDark) {
        qApp->setPalette(createDarkPalette());
    } else {
        qApp->setPalette(qApp->style()->standardPalette());
    }
}

bool isSystemDarkMode() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
#else
    QPalette palette = QGuiApplication::palette();
    return palette.color(QPalette::Window).lightness() < 128;
#endif
}

void setThemeListener() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    QObject::connect(QGuiApplication::styleHints(),
                     &QStyleHints::colorSchemeChanged,
                     [](Qt::ColorScheme colorScheme) {
                         bool isDark = (colorScheme == Qt::ColorScheme::Dark);
                         setTheme(isDark);
                     });
#else
    // Qt 5 is incompatible
#endif
}
