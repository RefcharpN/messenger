#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QPointer>
#include<QString>
#include<QTime>
#include<QMessageBox>

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>

#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>

#include "clientstart.h"
#include "serverstart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void dialog_server_click();
    void dialog_client_click();

    void on_server_add(int port);
    void on_socket_add(int port);
    void new_connect();
    void new_message();

private:
    Ui::MainWindow *ui;

    void init_db();
    QSqlDatabase db;

    QPointer<QTcpServer> server;
    QPointer<QTcpSocket> socket;

    QPointer<ClientStart> client_start_window;
    QPointer<ServerStart> server_start_window;


};
#endif // MAINWINDOW_H
