#ifndef LISTOFINFOFILE_H
#define LISTOFINFOFILE_H

#include <QObject>
#include "infofile.h"
#include <QVector>
#include <QFile>
#include <qDebug>
#include <QDir>

class ListOfInfoFIle
{

public:
    ListOfInfoFIle();
    void add(InfoFile);
 //   int isNeed(QString);
    InfoFile& getList(int);

    int readFromFile();
    void writeToFile();
    int size();

private:
    QVector<InfoFile> ListFiles;

};

#endif // LISTOFINFOFILE_H
