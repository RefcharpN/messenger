#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QPointer<QTcpSocket> socket, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->socket = socket;

    on_socket_add();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//кнопка "отправить сообщение"
{
    QString text = this->ui->lineEdit->text();

    QTextStream stream(socket);
    this->ui->listWidget->addItem(QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text));
    stream << text + "\n";
    stream.flush();//важно для приёма отправления

}

void MainWindow::on_socket_add()//подключение к серверу
{
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::new_message);

    // Проверка, если уже есть данные для чтения
    if (socket->bytesAvailable() > 0) {
        new_message(); // Вызываем new_message вручную
    }
}


void MainWindow::new_message()
{
    qWarning() << "новое сообщение";

    QTcpSocket *client = (QTcpSocket*)sender();

    QTextStream stream(client);

    QString response = stream.readLine();

    qWarning() << "сообщение" << response;

    this->ui->listWidget->addItem(QString("%1:%2:%3 - %4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(response));

}



