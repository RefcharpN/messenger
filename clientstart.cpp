#include "clientstart.h"
#include "ui_clientstart.h"

ClientStart::ClientStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientStart)
{
    ui->setupUi(this);
}

ClientStart::~ClientStart()
{
    delete ui;
}

void ClientStart::on_pushButton_clicked()
{
    if(this->ui->lineEdit->text().toInt() > 0)
    {
        emit on_client_add(this->ui->lineEdit->text().toInt());
        this->close();
    }
}

