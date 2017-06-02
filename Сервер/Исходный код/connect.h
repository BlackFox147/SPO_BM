#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <QVector>


#include<QFile>
#include <QString>
#include <QChar>
#include<QDebug>
#include <QTextCodec>
#include <QNetworkInterface>

class Connect
{

protected:
    QString name;
    SOCKET ConnectCli;
    int num;
    bool con;
public:
//    explicit Conect(QObject *parent = 0);

    explicit Connect(QString, SOCKET,int,bool);
    Connect();

    void setName(QString);
    QString getName();

    void setConnectCli(SOCKET);
    SOCKET getConnectCli();

    void setNum(int);
    int getNum();

    void setCon(bool);
    bool getCon();


signals:

public slots:

};

#endif // CONECT_H
