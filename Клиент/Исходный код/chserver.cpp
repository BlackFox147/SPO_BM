#include "chserver.h"
#include "ui_chserver.h"

ChServer::ChServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChServer)
{
    ui->setupUi(this);
}

ChServer::~ChServer()
{
    delete ui;
}

void ChServer::on_okBytton_clicked()
{
    QString ipServer = ui->newData->text();

    QFile file("info.txt");

    QByteArray strBa(ipServer.toUtf8());
    char *am = strBa.data();

    file.open(QIODevice::WriteOnly);

    file.write(am);
    file.close();

    close();
}
