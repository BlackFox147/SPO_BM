#include "listofcli.h"


ListOfCli::ListOfCli()
{

}

void ListOfCli::add(Connect tempCon){
    this->List.append(tempCon);
}

int ListOfCli::isNeed(QString tempStr){

    for(int i=0;i<this->List.size();i++){
        if(tempStr == this->List[i].getName()){
//            return true;
            return i;
        }
    }
    return -1;
//    return false;
}

Connect& ListOfCli::getList(int tempInt){
    return this->List[tempInt];
}

int ListOfCli::readFromFile(){
    QFile inform ("people.txt");
    if (!inform.exists()){
        inform.open(QIODevice::WriteOnly);
        int i=0;
        inform.write(QString::number(i).toStdString().data(),sizeof(int));
        inform.close();
        return i;
    }
    inform.open(QIODevice::ReadOnly);
    char tempC[1024];
    memset(tempC, 0, sizeof(tempC));
    int n;
    inform.read(tempC,sizeof(int));
    n = atoi(tempC);
    int i=n;

    while(n>0){
        memset(tempC, 0, sizeof(tempC));
        Connect temp;
        inform.read(tempC,sizeof(int));
        int a = atoi(tempC);
        inform.read(tempC,a);
        temp.setName(tempC);
        memset(tempC, 0, sizeof(tempC));
        inform.read(tempC,sizeof(int));
        a = atoi(tempC);
        temp.setNum(a);
        temp.setCon(false);

        List.append(temp);
        n--;
    }

//    qDebug() << List.size();
    inform.close();
    return i;
}

void ListOfCli::writeToFile(){
    QFile inform ("people.txt");
    inform.open(QIODevice::WriteOnly);
    int i=0;
    qDebug() << List.size()<<"[count clients]";
    inform.write(QString::number(List.size()).toStdString().data(),sizeof(int));

    while(i<List.size()){
        qDebug()<< QString::number(List[i].getName().size()).toStdString().data()<<List[i].getName().toStdString().data()<<QString::number(List[i].getNum()).toStdString().data();
        inform.write(QString::number(List[i].getName().size()).toStdString().data(),sizeof(int));
        inform.write(List[i].getName().toStdString().data(),List[i].getName().size());
        inform.write(QString::number(List[i].getNum()).toStdString().data(),sizeof(int));
        i++;
    }

    inform.close();
}


int ListOfCli::size(){
    return List.size();
}

/*
 *  QFile file2(trail+listOfFiles[fileId].dotFile);

          //        QString data;
                  file2.open(QIODevice::ReadOnly);

                  char tempC[1024];
                   qDebug() << "[1]";
                  while(!file2.atEnd()){
                       int nBloc = file2.read(tempC,sizeof(tempC));
              //            file2.write(tempC,nBloc);
 * */
