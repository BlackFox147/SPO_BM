#include "story.h"
#include <QFile>
#include <qDebug>


Story::Story()
{}

Story::Story(QString nameFile){

    QFile file(".//Story//"+nameFile+".txt");
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    this->name = nameFile;
}

void Story::add(QString tempStr){
   listOfMes.append(tempStr);
}

QString Story::gerStr(int number){
    return listOfMes[number];
}

int Story::readFromFile(){
    QFile inform (".//Story//"+this->name+".txt");
    inform.open(QIODevice::ReadOnly);
    char tempC[1024];
    memset(tempC, 0, sizeof(tempC));
    int n;
    inform.read(tempC,sizeof(int));
    n = atoi(tempC);
    int i=n;

    while(n>0){
        memset(tempC, 0, sizeof(tempC));
        QString temp;
        inform.read(tempC,sizeof(int));
        int a = atoi(tempC);
        inform.read(tempC,a);
        temp = tempC;

        listOfMes.append(temp);
        n--;
    }

    qDebug() << listOfMes.size();
    inform.close();
    n=i;
    for(n=0;n<i;n++){
        qDebug() << listOfMes[n];
    }
    return i;
}

void Story::writeToFile(){
    QFile inform (".//Story//"+this->name+".txt");
    inform.remove();
    inform.open(QIODevice::WriteOnly);

    int i=0;
    qDebug() << listOfMes.size();
    inform.write(QString::number(listOfMes.size()).toStdString().data(),sizeof(int));

    while(i<listOfMes.size()){
        qDebug()<< QString::number(strlen(listOfMes[i].toStdString().data())).toStdString().data()<<listOfMes[i].toStdString().data();

        inform.write(QString::number(strlen(listOfMes[i].toStdString().data())).toStdString().data(),sizeof(int));
        inform.write(listOfMes[i].toStdString().data(),strlen(listOfMes[i].toStdString().data()));

        i++;
    }

    inform.close();
}

int Story::size(){
    return listOfMes.size();
}

void Story::setNameFile(QString tempStr){
    this->name = tempStr;
}

QString Story::getName(){
    return this->name;
}


