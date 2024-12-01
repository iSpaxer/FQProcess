#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

#include <proxyserverudp.h>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    ProxyServerUdp proxyserverupd(5060, "/home/alex/CProject/CallPjsip/build/Desktop_Qt_6_7_2-Debug/CallPjsip");

    return app.exec();
}
