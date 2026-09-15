#ifndef CURRENCYAPI_H
#define CURRENCYAPI_H

#include <QMap>
#include <QString>
#include <QNetworkAccessManager>

class CurrencyAPI
{
public:
    CurrencyAPI();
    QString DownloadCurrencyData();
    QMap<QString, double> ParseRates(const QString& json);
    QMap<QString, double> RefreshRates();

private:
    QNetworkAccessManager networkManager;
};

#endif // CURRENCYAPI_H
