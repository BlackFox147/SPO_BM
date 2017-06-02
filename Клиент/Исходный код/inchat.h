#ifndef INCHAT_H
#define INCHAT_H

#include <QDialog>

namespace Ui {
class InChat;
}

class InChat : public QDialog
{
    Q_OBJECT

public:
    explicit InChat(QWidget *parent = 0);
    ~InChat();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InChat *ui;
};

#endif // INCHAT_H
