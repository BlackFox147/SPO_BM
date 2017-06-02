#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"
#include <QMainWindow>



#pragma comment( lib, "ws2_32.lib" )
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>


#include<QFile>
#include <QString>
#include <QChar>
#include<QDebug>
#include <stdlib.h> //Для очистки экрана

#include "story.h"

SOCKET my_sock1;
MainWindow *wnd;


void SendMassageToServer()
{
    qDebug() << "001";
    wnd->readListOfFiles();
    qDebug() << "002";
    int nsize;
    char buffer[1024];
    char infor[10];

    char start0[10] = "00";
    qDebug() << "001";
    send(wnd->my_sock, start0, 10, 0);
    my_sock1 = wnd->my_sock;

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(infor, 0, sizeof(infor));

        if((nsize = recv(my_sock1, infor, 10, 0))){
                if(nsize==SOCKET_ERROR){                   
                     return;
                }
                int iif;
                iif = atoi(infor);

                 switch (iif) {
                 case 0:{
                     qDebug() << "00";
                    recv(my_sock1, infor, 10, 0);
                    int size;
                    size = atoi(infor);

                    qDebug() << size;

                    for(int i=0;i<size;i++){
                        if(size==0){
                            break;
                        }
                        nsize = recv(my_sock1, buffer, 150, 0);

                        wnd->WriteName(buffer);

                        Story tempStory(buffer);
                        tempStory.readFromFile();
                        wnd->listOfStory.add(tempStory);

                        memset(buffer, 0, sizeof(buffer));

                    }
                    wnd->workWindow = wnd->listOfStory.find(wnd->nameP);
                    wnd->numberOfGtntralStory = wnd->workWindow;
                     qDebug() <<  wnd->workWindow;
                    for(int i=0;i<wnd->listOfStory.getStory(wnd->workWindow).size();i++){

                        QByteArray tempData(wnd->listOfStory.getStory(wnd->workWindow).gerStr(i).toUtf8());
                        char *am = tempData.data();
                        wnd->WriteMassageToServerWithoutStory(am);
                    }


                    wnd->setBackgroundNamePeople();


                 }
                     break;
                 case 2:{
                     char * info = new char[150];
                     int n = recv(my_sock1, info, 150, NULL);
                     info[n] = '\0';
                     if(wnd->isNeed(info)==0){
                         wnd->AddNameFile(info);
                         memset(info, 0, sizeof(info));
                     }

                 }
                     break;

                 case 3:{

                     char * info = new char[150];
                     recv(my_sock1, info, 150, NULL);
                     char *temp = new char[100];

                     int i = 0;
                     int k = 0;
                     int size;
                     int numberPac;
                     char dot[120];

                     for (i; info[i] != '/'; i++){
                         temp[i] = info[i];
                     }

                     temp[i] = '\0';
                     size = atoi(temp);
                     i++;

                     k = i;
                     for (i; info[i] != '/'; i++){
                         temp[i - k] = info[i];
                     }

                     temp[i - k] = '\0';
                     numberPac = atoi(temp);
                     i++;
                     k = i;
                     for (i; info[i] != '/'; i++){
                         dot[i - k] = info[i];
                     }
                     dot[i - k] = '\0';


                     memset(info, 0, sizeof(info));
                     QFile file2(wnd->trail+dot);
                     file2.open(QIODevice::WriteOnly);

                     int ii=numberPac;
                     while(ii>0){
                         int nBloc = recv(my_sock1, buffer, 1024, NULL);
                         file2.write(buffer,nBloc);
                         ii--;
                     }
                     file2.close();
                 }
                     break;
                 case 1:{                                         
                     nsize = recv(my_sock1, buffer, 1024, 0);

                     if(wnd->numberOfGtntralStory==wnd->workWindow){
                         wnd->WriteMassageToServer(buffer);
                     }
                     else{
                         int a = wnd->workWindow;
                         wnd->workWindow = wnd->numberOfGtntralStory;
                         wnd->StoryMassageToServer(buffer);
                         wnd->setColor(wnd->workWindow);

                         wnd->workWindow = a;
                     }
                     memset(buffer, 0, sizeof(buffer));                    
                 }
                    break;

                 case 6:{                   
                      recv(my_sock1, buffer, 10, 0);
                      int number = atoi(buffer);
                      memset(buffer, 0, sizeof(buffer));
                     nsize = recv(my_sock1, buffer, 1024, 0);

                     if(number==wnd->workWindow){
                         wnd->WriteMassageToServer(buffer);
                     }
                     else{
                         int a = wnd->workWindow;
                         wnd->workWindow = number;
                         wnd->StoryMassageToServer(buffer);
                         wnd->setColor(wnd->workWindow);

                         wnd->workWindow = a;
                     }


                     memset(buffer, 0, sizeof(buffer));
                 }
                    break;
                 case 9:{
                     nsize = recv(my_sock1, buffer, 1024, 0);
                     buffer[nsize] = '\0';

                     wnd->WriteName(buffer);
                     Story tempStory(buffer);
                     tempStory.readFromFile();
                     wnd->listOfStory.add(tempStory);
                     memset(buffer, 0, sizeof(buffer));
                 }
                 default:
                     break;
                 }
        }
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    wnd = new MainWindow();

    wnd->show();

    qDebug() << "Connected...";

    return a.exec();
}








