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
#include "connect.h"
#include "listofcli.h"
#include "listofinfofile.h"
#include "infofile.h"

SOCKET Con;							//принимает подключаемых сокетов
QVector <SOCKET> ConnectionsCli;
SOCKET Listen;
ListOfCli ListOf;
ListOfInfoFIle listOfFiles;

void SendFileToClient(InfoFile temp);

int ClientCount = 0;					//количество подключённых клиентов
int isNew = 0;
void SendMassageToClient(LPVOID tempID)			//отправить сообщение всем клиентам
{
    Connect ID = *(Connect*) tempID;
    char * buffer = new char[1024];					//транзакция
    QString trail = ".//Files//";

    qDebug() << ID.getName() << ID.getNum() << ID.getCon();

    int er;
    char * info = new char[150];
    char *temp = new char[100];
    char *dot = new char[120];
    char *com = new char[10];


    while(1)									//бесконечный цикл с временным интервалом
    {
//        memset(buffer, 0, sizeof(buffer));						//чистим буер
//        memset(com, 0, sizeof(com));

        if (er = recv(ID.getConnectCli(), com, 10, NULL)){

            if(er==SOCKET_ERROR){
                //qDebug() << "SOCKET_ERROR"<< ID.getNum();
                ID.setCon(false);
                 //qDebug() << ID.getName() << ID.getNum() << ID.getCon();
                 ListOf.writeToFile();
                 listOfFiles.writeToFile();
                return;
            }

            int iif;
            iif = atoi(com);
            //qDebug() << iif;
            //qDebug() << "Привет";
            memset(com, 0, sizeof(com));
            switch (iif) {
            case 0:{

                char inf[10] = "00";
                if(send(ID.getConnectCli(), inf, 10, 0)== SOCKET_ERROR)
                    return;
                QString ew;
                ew = QString::number(ListOf.size());

                if(send(ID.getConnectCli(),ew.toStdString().data() , 10, 0)== SOCKET_ERROR)
                    return;

                //qDebug() << ListOf.size();

                for (int i = 0; i < ListOf.size(); i++)							//отпраляем всем остальным клиентам
                {
                    if(ListOf.size()==0){

                        break;
                    }

                       if(send(ID.getConnectCli(),ListOf.getList(i).getName().toStdString().data() , 150, NULL)==SOCKET_ERROR)
                           qDebug () << "Error!";

                }

                if(isNew == 0){
                    break;
                }

                char inf1[10] = "09";

                if(send(ID.getConnectCli(), inf1, 10, 0)== SOCKET_ERROR)
                    qDebug () << "Error!";

                for (int i = 0; i < ListOf.size(); i++)							//отпраляем всем остальным клиентам
                {
                    if(ListOf.size()==0){

                        break;
                    }
                    if(ListOf.getList(i).getCon()){
                        if(send(ListOf.getList(i).getConnectCli(), inf1, 10, 0)== SOCKET_ERROR)
                          qDebug () << "Error!";

                       if(send(ListOf.getList(i).getConnectCli(),ID.getName().toStdString().data() , 150, NULL)==SOCKET_ERROR)
                           qDebug () << "Error!";

                    }
                }


            }
                break;
            case 1:{

                int a = recv(ID.getConnectCli(), buffer, 1024, NULL);

                 //qDebug() << buffer<<a;

                char inf[10] = "01";

                for (int i = 0; i < ListOf.size(); i++)							//отпраляем всем остальным клиентам
                {
                    if(ListOf.getList(i).getCon()){
                       if(send(ListOf.getList(i).getConnectCli(), inf, 10, 0)== SOCKET_ERROR)
                         return;
                       QString qqq = ID.getName()+" >> "+buffer;

                       if(send(ListOf.getList(i).getConnectCli(), qqq.toStdString().data(), 1024, NULL)==SOCKET_ERROR)
                           return;

                           //qDebug() << "[send_to_client]";
                           //qDebug() << i;
                    }
                }

            }
               break;

            case 3:{
                //qDebug() << "[file_start]";

              er = recv(ID.getConnectCli(), info, 150, NULL);
              if(er==SOCKET_ERROR){
                  //qDebug() << "error_info";
                  return;
              }
            //qDebug() << "[file_get]"<< er;

            //qDebug() << info;

            memset(temp, 0, sizeof(temp));
            memset(dot, 0, sizeof(dot));

                int i = 0;
                int k = 0;
                int size;
                int numberPac;

                for (i; info[i] != '/'; i++){
                    temp[i] = info[i];
                }

                temp[i] = '\0';
                size = atoi(temp);
                i++;
                memset(temp, 0, sizeof(temp));

                k = i;
                for (i; info[i] != '/'; i++){
                    temp[i - k] = info[i];
                }

                temp[i - k] = '\0';
                numberPac = atoi(temp);
                i++;

                k = i;

                memset(temp, 0, sizeof(temp));


                for (i; info[i] != '/'; i++){
                    dot[i - k] = info[i];
                }
                dot[i - k] = '\0';



                //qDebug() << "[file_dot111]";

                memset(info, 0, sizeof(info));
                QString str_temp = dot;
                int fileId=-1;

                //qDebug() << listOfFiles.size();
                for(i=0;i<listOfFiles.size();i++){
                    //qDebug() << i;
                    if(str_temp == listOfFiles.getList(i).getDotFile()){
                        fileId=i;
                        break;
                    }
                }



                    QFile file2(trail+dot);

                    file2.open(QIODevice::WriteOnly);

                    int ii=numberPac;
                    while(ii>0){

                        int nBloc = recv(ID.getConnectCli(), buffer, 1024, NULL);
                        file2.write(buffer,nBloc);
                        ii--;
                    }
                    file2.close();
                    //qDebug() << "End";
                if(fileId==-1){
                    InfoFile tempInf(listOfFiles.size(),size,numberPac,dot);
                     listOfFiles.add(tempInf);
                     SendFileToClient(tempInf);
                     qDebug() <<"[file saved]"<<listOfFiles.size()-1<< size<<numberPac<<dot;
                }
                else{
                    listOfFiles.getList(fileId).setNumberPacFile(numberPac);
                    listOfFiles.getList(fileId).setSizeFile(size);
                    SendFileToClient(listOfFiles.getList(fileId));
                    qDebug() <<"[file changed]"<<fileId<< size<<numberPac<<dot;
                }
                 //qDebug() << "continue";
            }
                break;
            case 4:{

                er = recv(ID.getConnectCli(), info, 150, NULL);
                if(er==SOCKET_ERROR){
                    //qDebug() << "error_info";
                    return;
                }
              //qDebug() << "[file_get]"<< er;
              int i=0;

              for (i; i<er; i++){
                  dot[i] = info[i];
              }

              dot[i] = '\0';
              QString str_temp = dot;
              //qDebug() << str_temp;

              int fileId=-1;

              //qDebug() << listOfFiles.size();
              for(i=0;i<listOfFiles.size();i++){
                  //qDebug() << i;
                  if(str_temp == listOfFiles.getList(i).getDotFile()){
                      fileId=i;
                      break;
                  }
              }


              if(fileId==-1){
                  qDebug () << "Файла нет!";
                  continue;
              }

              //qDebug()<<fileId;//**
                  QString inform;

                  char inf[10] = "03";

                  if(send(ID.getConnectCli(), inf, 10, 0)== SOCKET_ERROR)
                      return;

                  //qDebug() << listOfFiles.getList(fileId).getSizeFile() << listOfFiles.getList(fileId).getNumberPacFile() << listOfFiles.getList(fileId).getDotFile();

                  inform+=QString::number(listOfFiles.getList(fileId).getSizeFile())+'/'+QString::number(listOfFiles.getList(fileId).getNumberPacFile())+'/'+listOfFiles.getList(fileId).getDotFile()+'/';
                  //qDebug() << inform;


                  QByteArray strBa(inform.toUtf8());

                  char *am = new char[150];
                  am = strBa.data();
                  //qDebug() << am;

                  send(ID.getConnectCli(), am, 150, 0);


                  QFile file2(trail+listOfFiles.getList(fileId).getDotFile());

                  file2.open(QIODevice::ReadOnly);

                  char tempC[1024];
                   //qDebug() << "[1]";
                  while(!file2.atEnd()){
                       int nBloc = file2.read(tempC,sizeof(tempC));
                       send(ID.getConnectCli(),tempC, nBloc, 0);            //**

                  }
                  //qDebug() << "[2]";

                  file2.close();
                  qDebug() <<"[file sent]"<<fileId<< listOfFiles.getList(fileId).getSizeFile()<<listOfFiles.getList(fileId).getNumberPacFile()
                          <<listOfFiles.getList(fileId).getDotFile();

                  //qDebug() << "[end_send_file]";
  //                delete am;
            }

            break;
            case 5 :
            {
                //qDebug() << "[takeAt_close]"<< ID.getNum();
                ID.setCon(false);
                 //qDebug() << ID.getName() << ID.getNum() << ID.getCon();

                 ListOf.writeToFile();
                 listOfFiles.writeToFile();
                 qDebug() << ID.getName()<<"[went out of network]";
               return;
              }
                break;

            case 6:{


                recv(ID.getConnectCli(), buffer, 10, NULL);
                QString num = QString::number(ID.getNum());
                int number = atoi(buffer);
                memset(buffer, 0, sizeof(buffer));

                int a = recv(ID.getConnectCli(), buffer, 1024, NULL);

//                buffer[a] = 0;
                 //qDebug() << buffer<<a;
                //qDebug() << number<<num<<"[number]";
                char inf[10] = "06";

                if(ListOf.getList(number).getCon()){
                   if(send(ListOf.getList(number).getConnectCli(), inf, 10, 0)== SOCKET_ERROR)
                     qDebug () << "Error!";

                   if(send(ListOf.getList(number).getConnectCli(), num.toStdString().data(), 10, 0)== SOCKET_ERROR)
                     qDebug () << "Error!";

                   QString qqq = ID.getName()+" >> "+buffer;
//                      char bb[1024] = qqq.toStdString().data();

                   if(send(ListOf.getList(number).getConnectCli(), qqq.toStdString().data(), 1024, NULL)==SOCKET_ERROR)
                       qDebug () << "Error!";

                       //qDebug() << "[send_to_client]";
                       //qDebug() << number;
                }

            }
                break;

            case 7:{

                //qDebug() << "[file_start]";

                recv(ID.getConnectCli(), buffer, 10, NULL);
//                QString num = QString::number(ID.getNum());
                int number = atoi(buffer);
                memset(buffer, 0, sizeof(buffer));

              er = recv(ID.getConnectCli(), info, 150, NULL);
              if(er==SOCKET_ERROR){
                  //qDebug() << "error_info";
              }
            //qDebug() << "[file_get]"<< er;

            //qDebug() << info;

            memset(temp, 0, sizeof(temp));
            memset(dot, 0, sizeof(dot));

                int i = 0;
                int k = 0;
                int size;
                int numberPac;

                for (i; info[i] != '/'; i++){
                    temp[i] = info[i];
                }

                temp[i] = '\0';
                size = atoi(temp);
                printf("%d\n", size);
                i++;
                memset(temp, 0, sizeof(temp));

                k = i;
                for (i; info[i] != '/'; i++){
                    temp[i - k] = info[i];
                }

                temp[i - k] = '\0';
                numberPac = atoi(temp);
                i++;

                printf("%d\n", numberPac);
                k = i;

                memset(temp, 0, sizeof(temp));


                for (i; info[i] != '/'; i++){
                    dot[i - k] = info[i];
                }
                dot[i - k] = '\0';


                //qDebug() << size<<numberPac<<dot;
                //qDebug() << "[file_dot]";

                memset(info, 0, sizeof(info));

                QByteArray strBa;

                QFile file2(trail+dot);
                file2.open(QIODevice::WriteOnly);

                int ii=numberPac;
                while(ii>0){

                    int nBloc = recv(ID.getConnectCli(), buffer, 1024, NULL);
                    file2.write(buffer,nBloc);
                    ii--;
                }
                file2.close();
                //qDebug() << "End";
                QString str_temp = dot;
                //qDebug() << str_temp;

                int fileId=-1;

                //qDebug() << listOfFiles.size();
                for(i=0;i<listOfFiles.size();i++){
                    //qDebug() << i;
                    if(str_temp == listOfFiles.getList(i).getDotFile()){
                        fileId=i;
                        break;
                    }
                }

                if(fileId==-1){
                    InfoFile tempInf(listOfFiles.size(),size,numberPac,dot);
                    listOfFiles.add(tempInf);
                    if(!ListOf.getList(number).getCon()){
                        continue;
                    }
                    send(ListOf.getList(number).getConnectCli(), "02", 10, 0);
                    QByteArray strBa1(tempInf.getDotFile().toUtf8());
                    char *am = new char[150];
                    am = strBa1.data();
                    if(send(ListOf.getList(number).getConnectCli(), am, 150, 0)== SOCKET_ERROR)
                        return;
                     qDebug() <<"[file saved]"<<listOfFiles.size()-1<< size<<numberPac<<dot;

                }
                else{
                    listOfFiles.getList(fileId).setNumberPacFile(numberPac);
                    listOfFiles.getList(fileId).setSizeFile(size);
                    if(!ListOf.getList(number).getCon()){
                        continue;
                    }
                    send(ListOf.getList(number).getConnectCli(), "02", 10, 0);
                    QByteArray strBa1(listOfFiles.getList(fileId).getDotFile().toUtf8());
                    char *am = new char[150];
                    am = strBa1.data();
                    if(send(ListOf.getList(number).getConnectCli(), am, 150, 0)== SOCKET_ERROR)
                        return;
                    qDebug() <<"[file changed]"<<fileId<< size<<numberPac<<dot;
                }

            }
                break;
           default:
                 //qDebug() << "[лишнее]";
                break;
            }
        }
    }
    //qDebug() << "[end]";
}


void SendFileToClient(InfoFile info){

    char inf[10] = "02";
    //qDebug() << ClientCount;
    for (int i = 0; i < ClientCount; i++){
        if(ListOf.getList(i).getCon()){

        send(ListOf.getList(i).getConnectCli(), inf, 10, 0);

        QByteArray strBa(info.getDotFile().toUtf8());
        char *am = new char[150];
        am = strBa.data();

        //qDebug() << am;

        send(ListOf.getList(i).getConnectCli(), am, 150, 0);


        }
    }
    //qDebug() << info.getNumberPacFile()<<info.getSizeFile();

    //qDebug() << "temp_end";
}





int main()
{

    setlocale(LC_CTYPE, "Russian");

    WSAData data;
    WORD version = MAKEWORD(2, 2);            //версия сокетов 2.2
    int res = WSAStartup(version, &data);		//инициализация сокетв

    if (res != 0)								//проверка сокетов
    {
        return 0;
    }

    struct addrinfo hints;							//для инициализации сокетов
    struct addrinfo * result;

//    Connections = (SOCKET*)calloc(64, sizeof(SOCKET));		//инициализация масива клиентов

    ZeroMemory(&hints, sizeof(hints));						//обнуляем структуру

    hints.ai_family = AF_INET;						//задаём семейство сокетов
    hints.ai_flags = AI_PASSIVE;					//флаг
    hints.ai_socktype = SOCK_STREAM;				//потоковый сокет
    hints.ai_protocol = IPPROTO_TCP;				//протокол TCP

    getaddrinfo(NULL, "7770", &hints, &result);			//информация о хосте

    Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    bind(Listen, result->ai_addr, result->ai_addrlen);			//объявляем сервер
    listen(Listen, SOMAXCONN);								//ждём подключения

    freeaddrinfo(result);									//всё настроено, удаляем лишнее

    printf("Start server...\n");
    ClientCount = ListOf.readFromFile();
    listOfFiles.readFromFile();
    //qDebug() << "Привет";



    char m_connect[] = "Connected...";		//сообщение для клиента
    for (;; Sleep(75))					//бесконечный цикл с небольшой задержкой
    {
        if (Con = accept(Listen, NULL, NULL))		//ждём подключения
        {
            printf("Client connect... \n");
//            Connections[ClientCount] = Connect;					//сохраняем его сокет
//            send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);		//отправляем ему сооющь, что подключился
            char temp1[150];

            recv(Con, temp1, 150, NULL);
            //qDebug() << temp1<< "[temp1]";
            int a;
            a = ListOf.isNeed(temp1);
            if(a>=0){
                ListOf.getList(a).setConnectCli(Con);
                ListOf.getList(a).setCon(true);
                //qDebug() <<"[old]";
                isNew = 0;
            }
            else{

                Connect ter(temp1,Con,ClientCount,true);
                ListOf.add(ter);
                //qDebug() <<"[new]";
                a=ClientCount;
                ClientCount++;
                isNew = 1;
            }



            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMassageToClient, (LPVOID)&(ListOf.getList(a)), NULL, NULL);
            //создаём поток для вывода сообщения.
        }
    }
    ListOf.writeToFile();

    //qDebug() << "[Хрень]";
    return 0;
}





