#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#pragma comment( lib, "ws2_32.lib" )
#include <WinSock2.h>

#include <iostream>
#include <WS2tcpip.h>
#include "story.h"
#include "listofstory.h"
#include <QFileDialog>
#include <Qlabel>
#include <QTextCodec>
#include <QCloseEvent>
#include<QFile>
#include <QString>
#include <QChar>
#include<QDebug>
#include <stdlib.h> //Для очистки экрана
#include <QLayout>
#include "inchat.h"
#include "chserver.h"

#include <QTcpSocket>

#define PORT 7770
//#define SERVERADDR "127.0.0.1"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SOCKET my_sock;
    char nameP[150];
    ListOfStory listOfStory;
    int workWindow;
    QString trail;
    char SERVERADDR[15];
    int numberOfGtntralStory;


    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:

    void on_pushSend_clicked();
    void on_pushButton_clicked();
    void on_lisfFiles_doubleClicked(const QModelIndex &index);

    void on_lustOfPeople_doubleClicked(const QModelIndex &index);

    void on_connect_clicked();

    void on_actionIP_triggered();

public:
    void WriteMassageToServer(char *);
    void WriteName(char *);
    void AddNameFile(char *);
    void closeEvent(QCloseEvent *event);

    void beforeWork();

    void WriteMassageToServerWithoutStory(char *);
    void StoryMassageToServer(char *);
    void setBackgroundNamePeople();
    void readListOfFiles();
    void writeListOfFiles();
    void setColor(int row);

    int isNeed(QString);

    SOCKET startConnect();
};

#endif // MAINWINDOW_H
