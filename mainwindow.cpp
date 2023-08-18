#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_socket_add();

    //init_db();
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


    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::new_message);



//    QSqlQuery query(db);
//    query.exec("INSERT INTO message_log (info) "
//                   "VALUES ('"+QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text)+"')");

//    this->ui->lineEdit->clear();

}

void MainWindow::on_socket_add()//подключение к серверу
{
    if(!socket)
    {
        socket = new QTcpSocket();
    }
    socket->connectToHost(QHostAddress::LocalHost, 2517);
    this->ui->label->setText(QString("порт клиента: %1").arg(2517));
}


void MainWindow::new_message()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QTextStream stream(client);

    QString text = stream.readLine();

    this->ui->listWidget->addItem(QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text));

//    QSqlQuery query(db);
//    query.exec("insert into message_log(info) values ('"+QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text)+"')");

}

void MainWindow::init_db()
{

    db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "hw3" );


    if(!db.open())
    {
        qWarning() << db.lastError().text();
    }
    else
    {
        QSqlQuery query(db);
        if( !query.exec("CREATE TABLE message_log(info nvarchar(255) not null)") )
        {
            query.exec("SELECT info FROM message_log");
            while (query.next())
            {
              this->ui->listWidget->addItem(query.value(0).toString());
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("создана бд");
            msgBox.setText("была создана база для хранения сообщений");
            msgBox.exec();
        }
    }
}

