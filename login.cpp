#include "login.h"
#include "ui_login.h"


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

void login::on_pushButton_clicked()
{

    MainWindow *w = new MainWindow();
    w->show();

    this->close();
}


void login::on_pushButton_3_clicked()
{
    this->close();
}


void login::on_pushButton_2_clicked()
{

}

