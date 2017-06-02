#include "infofile.h"

InfoFile::InfoFile()
{}

InfoFile::InfoFile(int startNum,int startSize,int startPac,QString startDot){
    this->number = startNum;
    this->sizeFile = startSize;
    this->numberPacFile = startPac;
//    this->who = startWho;
    this->dotFile = startDot;
}

int InfoFile::getNumber(){
    return this->number;
}

int InfoFile::getSizeFile(){
    return this->sizeFile;
}

int InfoFile::getNumberPacFile(){
    return this->numberPacFile;
}

QString InfoFile::getDotFile(){
    return this->dotFile;
}

void InfoFile::setNumber(int temp){
    this->number = temp;
}

void InfoFile::setSizeFile(int temp){
    this->sizeFile = temp;
}

void InfoFile::setNumberPacFile(int temp){
    this->numberPacFile = temp;
}

void InfoFile::setDotFile(QString temp){
    this->dotFile = temp;
}
/*
void infoFile::setWho(int temp){
    this->who = temp;
}

int infoFile::getWho(){
    return this->who;
}
*/
