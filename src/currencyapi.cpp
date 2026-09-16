#include "currencyapi.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QEventLoop>
#include <stdexcept>

CurrencyAPI::CurrencyAPI() {}

QString CurrencyAPI::DownloadCurrencyData(){
    QUrl url("https://api.frankfurter.dev/v2/rates?base=CNY");

    QNetworkRequest request(url);
    QNetworkReply* reply = networkManager.get(request);

    QEventLoop loop;

    QObject::connect(
        reply,
        &QNetworkReply::finished,
        &loop,
        &QEventLoop::quit
        );

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        QString error = reply->errorString();
        reply->deleteLater();

        throw std::runtime_error(
            ("Currency API request failed: " + error).toStdString()
            );
    }

    QByteArray data = reply->readAll();

    reply->deleteLater();

    QString json = QString::fromUtf8(data);

    qInfo() << "I: Downloaded new currency data:" << json;

    return json;
}

QMap<QString, double> CurrencyAPI::ParseRates(const QString& json){
    QMap<QString, double> dict;

    QJsonParseError parseError;
    QJsonDocument document =
        QJsonDocument::fromJson(json.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        throw std::invalid_argument(
            ("Invalid currency JSON: " +
             parseError.errorString()).toStdString()
            );
    }

    if (!document.isArray()) {
        throw std::invalid_argument(
            "Currency API returned an unexpected JSON format."
            );
    }

    QJsonArray items = document.array();

    // Base currency
    dict["CNY"] = 1.0;

    for (const QJsonValue& value : items) {
        if (!value.isObject()) {
            continue;
        }

        QJsonObject item = value.toObject();

        QString quote = item["quote"].toString();
        double rate = item["rate"].toDouble();

        if (quote.isEmpty() || rate == 0.0) {
            continue;
        }

        dict[quote] = 1.0 / rate;
    }

    return dict;
}

QMap<QString, double> CurrencyAPI::RefreshRates(){
    QString json = DownloadCurrencyData();
    return ParseRates(json);
}
