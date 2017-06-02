#include "inchat.h"
#include "ui_inchat.h"
#include <QFile>


InChat::InChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InChat)
{
    ui->setupUi(this);
}


InChat::~InChat()
{
    delete ui;
}

void InChat::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QFile file("name.txt");

    QByteArray strBa(name.toUtf8());
    char *am = strBa.data();

    file.open(QIODevice::WriteOnly);

    file.write(am);
    file.close();

    close();
}
