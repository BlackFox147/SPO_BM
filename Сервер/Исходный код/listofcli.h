#ifndef LISTOFCLI_H
#define LISTOFCLI_H

#include <QObject>
#include "connect.h"
#include <QVector>
#include <QString>
#include <QFile>

class ListOfCli
{
public:
    ListOfCli();
    void add(Connect);
    int isNeed(QString);
    Connect& getList(int);

    int readFromFile();
    void writeToFile();
    int size();

private:
    QVector<Connect> List;

};

#endif // LISTOFCLI_H
