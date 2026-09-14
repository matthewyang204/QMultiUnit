#ifndef DARKMODE_H
#define DARKMODE_H

#include <QPalette>

QPalette createDarkPalette();
void setTheme(bool isDark);
bool isSystemDarkMode();
void setThemeListener();

#endif // DARKMODE_H
