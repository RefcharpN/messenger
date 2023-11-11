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
    void new_message();


private:
    Ui::MainWindow *ui;

    void init_db();
    QSqlDatabase db;

    QPointer<QTcpSocket> socket;

    void on_socket_add();


};
#endif // MAINWINDOW_H
