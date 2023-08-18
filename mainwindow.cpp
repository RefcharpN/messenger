#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_db();

    QObject::connect(this->ui->action,SIGNAL(triggered()),SLOT(dialog_server_click()));
    QObject::connect(this->ui->action_2,SIGNAL(triggered()),SLOT(dialog_client_click()));
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
    stream << text;



    QSqlQuery query(db);
    query.exec("INSERT INTO message_log (info) "
                   "VALUES ('"+QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text)+"')");

    this->ui->lineEdit->clear();

}

void MainWindow::dialog_server_click()//окно для запуска сервера(получение)
{
    if(server_start_window)
    {
        delete server_start_window;
    }
    server_start_window = new ServerStart();

    server_start_window->setModal(true);
    server_start_window->setWindowTitle("окно для запуска сервера(получение)");

    QObject::connect(server_start_window, &ServerStart::on_server_start, this, &MainWindow::on_server_add);

    server_start_window->show();
}

void MainWindow::dialog_client_click()//окно для запуска клиента-сокета (отправление)
{
    if(client_start_window)
    {
        delete client_start_window;
    }
    client_start_window = new ClientStart();

    client_start_window->setModal(true);
    client_start_window->setWindowTitle("окно для запуска клиента(отправление)");

    QObject::connect(client_start_window, &ClientStart::on_client_add, this, &MainWindow::on_socket_add);

    client_start_window->show();
}

void MainWindow::on_server_add(int port)//когда создали сервер
{
    if(!server)
    {
        server = new QTcpServer();
    }
    server->listen(QHostAddress::LocalHost, port);

    QObject::connect(server, &QTcpServer::newConnection,this,&MainWindow::new_connect);

    this->ui->label_2->setText(QString("порт для получения: %1").arg(port));

}

void MainWindow::on_socket_add(int port)//когда объявили клиент
{
    if(!socket)
    {
        socket = new QTcpSocket();
    }
    socket->connectToHost(QHostAddress::LocalHost, port);
    this->ui->label->setText(QString("порт клиента: %1").arg(port));
}

void MainWindow::new_connect()
{
    while(server->hasPendingConnections())
    {
        QTcpSocket *client = server->nextPendingConnection();
        QObject::connect(client, &QTcpSocket::readyRead, this, &MainWindow::new_message);
    }
}

void MainWindow::new_message()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    QTextStream stream(client);

    QString text = stream.readLine();

    this->ui->listWidget->addItem(QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text));

    QSqlQuery query(db);
    query.exec("insert into message_log(info) values ('"+QString("%1:%2:%3-%4").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(text)+"')");

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

