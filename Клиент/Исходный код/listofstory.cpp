#include "listofstory.h"

ListOfStory::ListOfStory()
{

}

void ListOfStory::add(Story temp){
    this->listOfStory.append(temp);
}

Story& ListOfStory::getStory(int tempNumber){
    return this->listOfStory[tempNumber];
}

int ListOfStory::find(QString nameFile){
    int i;
    for(i=0; i<this->listOfStory.size();i++){
        if(nameFile==this->listOfStory[i].getName()){
            break;
        }
    }
    return i;
}

void ListOfStory::close(){
    for (int i=0;i<this->listOfStory.size();i++){
        this->listOfStory[i].writeToFile();
        qDebug() << listOfStory[i].getName();
    }
}

