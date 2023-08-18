#ifndef CLIENTSTART_H
#define CLIENTSTART_H

#include <QDialog>

namespace Ui {
class ClientStart;
}

class ClientStart : public QDialog
{
    Q_OBJECT

public:
    explicit ClientStart(QWidget *parent = nullptr);
    ~ClientStart();

private:
    Ui::ClientStart *ui;

signals:
    void on_client_add(int port);
private slots:
    void on_pushButton_clicked();
};

#endif // CLIENTSTART_H
