#ifndef PROXYSERVERUDP_H
#define PROXYSERVERUDP_H

#include <QObject>

#include <QCoreApplication>
#include <QUdpSocket>
#include <QProcess>
#include <QDebug>

class ProxyServerUdp : public QObject
{
    Q_OBJECT

public:
    explicit ProxyServerUdp(quint16 port, const QString &referenceOnProgram, QObject *parent = nullptr);

private slots:
    void handleIncomingData();

    void launchExternalProgram();

private:
    QUdpSocket *udpSocket;
    QProcess *process;

    const QString referenceOnProgram;
};

#endif // PROXYSERVERUDP_H
