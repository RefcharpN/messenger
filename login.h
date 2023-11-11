#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include <QTcpSocket>
#include <QSerialPort>




namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

public slots:
    void readSocket();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void radioUpdate();

private:
    Ui::login *ui;

    QPointer<QTcpSocket> socket;

    QSerialPort *serial = NULL;
    QString getTokenFromUSB(QString timeSt);

};

#endif // LOGIN_H
