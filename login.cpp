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

#include <QSerialPortInfo>



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
    if(error.offset)
    {
        qWarning() << "Error: " << error.errorString() << error.offset << error.error;
        return;
    }

    if (doc.isObject())
    {
        QJsonObject obj = doc.object();
        QString exist = obj["EXIST"].toString();
        if(exist == "1")
        {
            int socketDescriptor = this->socket->socketDescriptor();
            QObject::disconnect(socket, &QTcpSocket::readyRead, this, &login::readSocket);
            MainWindow *w = new MainWindow(socket);
            w->show();
            this->close();
        }
    }
}

void login::on_pushButton_clicked()
{

    if(!socket)
    {
        socket = new QTcpSocket();
        //socket->connectToHost("25.8.8.1", 4013);
        socket->connectToHost("localhost", 4013);
        QObject::connect(socket, &QTcpSocket::readyRead, this, &login::readSocket);

    }

    qWarning() << "сокет открыт " << socket->isOpen();

    QString token;
    if(this->ui->radioButton_2->isChecked())
    {
        token = this->ui->lineEdit_3->text();
    }
    else
    {
        token = this->getTokenFromUSB(QString::number(QDateTime::currentSecsSinceEpoch()));
        if(token.length() != 6)
        {
            return;
        }
    }

    qWarning() << "токен получен";


    if(socket->waitForConnected(1000))
    {
        qWarning() << "ожидание завершено";
        QTextStream stream(socket);
            QJsonObject item_data;

            item_data.insert("OPERATION", QJsonValue("1"));
            item_data.insert("LOGIN", QJsonValue(this->ui->lineEdit->text()));
            item_data.insert("PASSWORD", QJsonValue(this->ui->lineEdit_2->text()));
            item_data.insert("TOKEN", QJsonValue(token));
            qWarning() << "создан json для сервера";
        QJsonDocument doc(item_data);
        QString jsonString = doc.toJson(QJsonDocument::Compact);

        stream << jsonString + "\n";
        qWarning() << "отправлено на сервер";
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
    qWarning() << "запрос к usb";
    if(serial != NULL)
    {
        serial->close();
        delete serial;
    }

    serial = new QSerialPort();


    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qWarning() << "\n"
                   << "Port:" << portInfo.portName() << "\n"
                   << "Location:" << portInfo.systemLocation() << "\n"
                   << "Description:" << portInfo.description() << "\n"
                   << "Manufacturer:" << portInfo.manufacturer() << "\n"
                   << "Serial number:" << portInfo.serialNumber() << "\n"
                   << "Vendor Identifier:"
                   << (portInfo.hasVendorIdentifier()? QByteArray::number(portInfo.vendorIdentifier(), 16): QByteArray()) << "\n"
                   << "Product Identifier:"
                   << (portInfo.hasProductIdentifier()? QByteArray::number(portInfo.productIdentifier(), 16): QByteArray());

        if(((portInfo.hasVendorIdentifier()? QByteArray::number(portInfo.vendorIdentifier(), 16): QByteArray()) == "2341")
           && ((portInfo.hasProductIdentifier()? QByteArray::number(portInfo.productIdentifier(), 16): QByteArray()) == "8036"))
        {
            //по двум id ищем токен на ардуино
            serial->setPortName(portInfo.portName());
        }
    }

    qWarning() << "установлен порт" << serial->portName();
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    //serial->setStopBits(QSerialPort::UnknownStopBits);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    serial->setDataTerminalReady(false);
    serial->setRequestToSend(false);

    serial->open(QIODevice::ReadWrite);
    serial->waitForReadyRead(1000);//требует доп. проверку

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
        qWarning() << "токен с arduino" <<arduinoResponseString;  // Вывод полученного ответа
    }
    else
    {
        qWarning() << "Ошибка открытия последовательного порта:" << serial->errorString();
    }
    return arduinoResponseString;
}


