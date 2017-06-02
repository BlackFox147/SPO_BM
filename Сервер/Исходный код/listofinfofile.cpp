#include "listofinfofile.h"


ListOfInfoFIle::ListOfInfoFIle()
{
    QDir dir("Files");
    if(!dir.exists()){
         QDir dir1(".");
        dir1.mkdir("Files");
    }
}

void ListOfInfoFIle::add(InfoFile temp){
    this->ListFiles.append(temp);
}
/*
int ListOfInfoFIle::isNeed(QString){
    return 0;
}
*/
InfoFile& ListOfInfoFIle::getList(int num){
    return this->ListFiles[num];
}

/*
 * int number;
    int sizeFile;
    int numberPacFile;
    QString dotFile;
    int who;
 */

int ListOfInfoFIle::readFromFile(){
    QFile inform ("files.txt");
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
        InfoFile temp;
        inform.read(tempC,sizeof(int));
        int a = atoi(tempC);
        inform.read(tempC,a);
        temp.setDotFile(tempC);
        memset(tempC, 0, sizeof(tempC));

        inform.read(tempC,sizeof(int));
        a = atoi(tempC);
        temp.setNumber(a);
        memset(tempC, 0, sizeof(tempC));

        inform.read(tempC,sizeof(int));
        a = atoi(tempC);
        temp.setNumberPacFile(a);
        memset(tempC, 0, sizeof(tempC));

        inform.read(tempC,sizeof(int));
        a = atoi(tempC);
        temp.setSizeFile(a);
        memset(tempC, 0, sizeof(tempC));
/*
        inform.read(tempC,sizeof(int));
        a = atoi(tempC);
        temp.setWho(a);
*/
        this->ListFiles.append(temp);
        qDebug() << temp.getDotFile()<<"[read]";
        n--;
    }

    qDebug() << this->ListFiles.size();
    inform.close();

    return i;
}

void ListOfInfoFIle::writeToFile(){
    QFile inform ("files.txt");
    inform.open(QIODevice::WriteOnly);
    int i=0;
//    qDebug() << this->ListFiles.size()<< "[write]";
    inform.write(QString::number(this->ListFiles.size()).toStdString().data(),sizeof(int));

    while(i<this->ListFiles.size()){
//        qDebug()<< QString::number(this->ListFiles[i].getDotFile().size()).toStdString().data()<<List[i].getName().toStdString().data()<<QString::number(List[i].getNum()).toStdString().data();
        inform.write(QString::number(strlen(this->ListFiles[i].getDotFile().toStdString().data())).toStdString().data(),sizeof(int));
        inform.write(this->ListFiles[i].getDotFile().toStdString().data(),strlen(this->ListFiles[i].getDotFile().toStdString().data()));
        inform.write(QString::number(this->ListFiles[i].getNumber()).toStdString().data(),sizeof(int));
        inform.write(QString::number(this->ListFiles[i].getNumberPacFile()).toStdString().data(),sizeof(int));
        inform.write(QString::number(this->ListFiles[i].getSizeFile()).toStdString().data(),sizeof(int));
//        inform.write(QString::number(this->ListFiles[i].getWho()).toStdString().data(),sizeof(int));
        i++;
    }

    inform.close();
}

int ListOfInfoFIle::size(){
    return this->ListFiles.size();
}
