#include "serverstart.h"
#include "ui_serverstart.h"

ServerStart::ServerStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerStart)
{
    ui->setupUi(this);
}

ServerStart::~ServerStart()
{
    delete ui;
}

void ServerStart::on_pushButton_clicked()
{
    if(this->ui->lineEdit->text().toInt() > 0)
    {
        emit on_server_start(this->ui->lineEdit->text().toInt());
        this->close();
    }
}

