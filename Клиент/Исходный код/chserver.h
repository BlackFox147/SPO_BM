#ifndef CHSERVER_H
#define CHSERVER_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QString>

namespace Ui {
class ChServer;
}

class ChServer : public QDialog
{
    Q_OBJECT

public:
    explicit ChServer(QWidget *parent = 0);
    ~ChServer();

private slots:
    void on_okBytton_clicked();

private:
    Ui::ChServer *ui;
};

#endif // CHSERVER_H
