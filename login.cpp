#include "login.h"
#include "ui_login.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>


login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::readSocket()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QTextStream stream(client);

    QString response = stream.readLine();

    qWarning() << response;



    QJsonParseError error;

    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8(), &error);

    if (doc.isObject())
    {
        QJsonObject obj = doc.object();
        QString exist = obj["EXIST"].toString();
        if(exist == "1")
        {
            MainWindow *w = new MainWindow();
            w->show();

            //    this->close();
        }
    }
}

void login::on_pushButton_clicked()
{

    if(!socket)
    {
        socket = new QTcpSocket();
    }
    //socket->connectToHost("10.66.66.1", 4013);
    socket->connectToHost("localhost", 4013);


    QObject::connect(socket, &QTcpSocket::readyRead, this, &login::readSocket);

    if(socket->waitForConnected(1000))
    {
        QTextStream stream(socket);


            QJsonObject item_data;

            item_data.insert("OPERATION", QJsonValue("1"));
            item_data.insert("LOGIN", QJsonValue(this->ui->lineEdit->text()));
            item_data.insert("PASSWORD", QJsonValue(this->ui->lineEdit_2->text()));
            item_data.insert("TOKEN", QJsonValue(this->ui->lineEdit_3->text()));

        QJsonDocument doc(item_data);
        QString jsonString = doc.toJson(QJsonDocument::Compact);

        stream << jsonString + "\n";
        stream.flush();//важно для приёма отправления
    }
}


void login::on_pushButton_3_clicked()
{
}


void login::on_pushButton_2_clicked()
{

}

