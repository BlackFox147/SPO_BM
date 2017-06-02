#ifndef LISTOFSTORY_H
#define LISTOFSTORY_H

#include <QObject>
#include <QVector>
#include"story.h"
#include <QDebug>

class ListOfStory
{
private:
    QVector <Story> listOfStory;



public:
    ListOfStory();
    void add(Story);
    Story& getStory(int);
    int find(QString );
    void close();

};

#endif // LISTOFSTORY_H
