#ifndef SERVERSTART_H
#define SERVERSTART_H

#include <QDialog>

namespace Ui {
class ServerStart;
}

class ServerStart : public QDialog
{
    Q_OBJECT

public:
    explicit ServerStart(QWidget *parent = nullptr);
    ~ServerStart();

private:
    Ui::ServerStart *ui;
signals:
    void on_server_start(int port);
private slots:
    void on_pushButton_clicked();
};

#endif // SERVERSTART_H
