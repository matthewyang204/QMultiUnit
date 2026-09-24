#include <QSslSocket>
#include <QDebug>

void printSSLInfo(){
    qDebug() << "D: supportsSsl:" << QSslSocket::supportsSsl();
    qDebug() << "D: sslLibraryVersion:"
            << QSslSocket::sslLibraryVersionString();
    qDebug() << "D: sslLibraryBuildVersion:"
            << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "D: availableBackends:"
            << QSslSocket::availableBackends();
    qDebug() << "D: activeBackend:"
            << QSslSocket::activeBackend();
}