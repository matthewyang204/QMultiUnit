#include <QSslSocket>
#include <QDebug>

void printSSLInfo(){
    qDebug() << "supportsSsl:" << QSslSocket::supportsSsl();
    qDebug() << "sslLibraryVersion:"
            << QSslSocket::sslLibraryVersionString();
    qDebug() << "sslLibraryBuildVersion:"
            << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "availableBackends:"
            << QSslSocket::availableBackends();
    qDebug() << "activeBackend:"
            << QSslSocket::activeBackend();
}