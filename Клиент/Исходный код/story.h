#ifndef STORY_H
#define STORY_H

#include <QObject>

#include <QVector>
class Story
{
private:
    QVector <QString> listOfMes;
    QString name;


public:
    Story();
    Story(QString);
    void add(QString);
    QString gerStr(int number);
    void setNameFile(QString);

    int readFromFile();
    void writeToFile();
    int size();

    QString getName();

};

#endif // STORY_H
