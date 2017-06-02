#ifndef INFOFILE_H
#define INFOFILE_H

#include <QObject>
#include <QString>
class InfoFile
{
private:
    int number;
    int sizeFile;
    int numberPacFile;
    QString dotFile;
//    int who;

public:
    InfoFile();
    InfoFile(int,int,int,QString);
    int getNumber();
    int getSizeFile();
    int getNumberPacFile();
    QString getDotFile();
    void setNumber(int);
    void setSizeFile(int);
    void setNumberPacFile(int);
    void setDotFile(QString);
//    void setWho(int);
//    int getWho();
};

#endif // INFOFILE_H
