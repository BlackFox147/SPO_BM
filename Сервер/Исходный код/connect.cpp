#include "connect.h"

Connect::Connect(){

}


Connect::Connect(QString tempStr, SOCKET tempSok,int tempInt,bool tempBool){
    this->name = tempStr;
    this->ConnectCli=tempSok;
    this->num = tempInt;
    this->con = tempBool;

}

void Connect::setName(QString tempStr){
     this->name = tempStr;
}

QString Connect::getName(){
    return  this->name;
}

void Connect::setConnectCli(SOCKET tempSok){
    this->ConnectCli=tempSok;
}

SOCKET Connect::getConnectCli(){
    return this->ConnectCli;
}

void Connect::setNum(int tempInt){
    this->num = tempInt;
}

int Connect::getNum(){
    return this->num;
}

void Connect::setCon(bool tempBool){
    this->con = tempBool;
}

bool Connect::getCon(){
    return this->con;
}
