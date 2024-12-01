#include "proxyserverudp.h"

ProxyServerUdp::ProxyServerUdp(quint16 port, const QString &referenceOnProgram, QObject *parent)
    : QObject(parent), udpSocket(new QUdpSocket(this)), process(new QProcess(this)), referenceOnProgram(referenceOnProgram) {

    // udpSocket->setSocketOption(QAbstractSocket::SocketOption::ReuseAddressHint, 1);

    // Привязка к указанному порту
    if (udpSocket->bind(QHostAddress::Any, port)) {
        connect(udpSocket, &QUdpSocket::readyRead, this, &ProxyServerUdp::handleIncomingData);
        qDebug() << "Listening on port:" << port;
    } else {
        qWarning() << "Failed to bind to port" << port;
    }
}

void ProxyServerUdp::handleIncomingData() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString message = QString::fromUtf8(datagram);

        // qDebug() << "Received message from" << sender.toString() << ":" << senderPort;
        // qDebug() << "Message content:" << message;

        if (message.startsWith("INVITE", Qt::CaseInsensitive)) {
            qDebug() << "Close UDP socket...";
            // После запуска программы отсоединяем сокет от объекта SipServer
            udpSocket->close();
            delete udpSocket;

            qDebug() << "- SIP INVITE detected, launching external program...";
            launchExternalProgram();
            return;
        }
    }
}

void ProxyServerUdp::launchExternalProgram() {
    QStringList arguments; // Аргументы, если нужны
    process->start(referenceOnProgram, arguments);

    if (!process->waitForStarted()) {
        qWarning() << "Failed to start the external program.";
    } else {
        qDebug() << "External program started successfully.";
    }
}
