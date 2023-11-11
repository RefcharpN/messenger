#include "login.h"
#include "ui_login.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QObject>
#include <QDateTime>
#include <QSerialPort>


login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    QObject::connect(this->ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(radioUpdate()));

}

login::~login()
{
    serial->close();
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

    QString token;
    if(this->ui->radioButton_2->isChecked())
    {
        token = this->ui->lineEdit_3->text();
    }
    else
    {
        token = this->getTokenFromUSB(QString::number(QDateTime::currentSecsSinceEpoch()));
    }


    if(socket->waitForConnected(1000))
    {
        QTextStream stream(socket);


            QJsonObject item_data;

            item_data.insert("OPERATION", QJsonValue("1"));
            item_data.insert("LOGIN", QJsonValue(this->ui->lineEdit->text()));
            item_data.insert("PASSWORD", QJsonValue(this->ui->lineEdit_2->text()));
            item_data.insert("TOKEN", QJsonValue(token));

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

void login::radioUpdate()
{
    if(this->ui->radioButton->isChecked())
    {
        this->ui->lineEdit_3->setVisible(false);
    }
    else
    {
        this->ui->lineEdit_3->setVisible(true);
    }
}


//работа с serial портом arduino переделать на динамический поиск
QString login::getTokenFromUSB(QString timeSt)
{
    if(serial != NULL)
    {
        serial->close();
        delete serial;
    }

    serial = new QSerialPort();
    serial->setPortName("/dev/ttyUSB0");  // Измените '/dev/ttyUSB0' на ваш серийный порт
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::UnknownStopBits);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    serial->setDataTerminalReady(false);
    serial->setRequestToSend(false);

    serial->open(QIODevice::ReadWrite);
    serial->waitForReadyRead(3000);

    QString arduinoResponseString;
    if (serial->isOpen() && serial->isWritable())
    {
        QByteArray data = timeSt.toUtf8();
        serial->write(data);
        serial->write("\n");

        serial->flush();

        serial->waitForBytesWritten(1000);//посмотреть на интервал
        serial->waitForReadyRead(1000);

        // Ожидание и чтение ответа от Arduino
        QByteArray arduinoResponse = serial->readLine();
        arduinoResponseString = QString::fromLatin1(arduinoResponse).trimmed();
        qWarning() << arduinoResponseString;  // Вывод полученного ответа
    }
    else
    {
        qWarning() << "Ошибка открытия последовательного порта:" << serial->errorString();
    }
    return arduinoResponseString;
}


