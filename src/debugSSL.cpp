#include <QSslSocket>
#include <QDebug>

void printSSLInfo(){
    qDebug() << "D: supportsSsl:" << QSslSocket::supportsSsl();
    qDebug() << "D: sslLibraryVersion:"
            << QSslSocket::sslLibraryVersionString();
    qDebug() << "D: sslLibraryBuildVersion:"
            << QSslSocket::sslLibraryBuildVersionString();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    qDebug() << "D: availableBackends:"
            << QSslSocket::availableBackends();
    qDebug() << "D: activeBackend:"
            << QSslSocket::activeBackend();
#endif
}