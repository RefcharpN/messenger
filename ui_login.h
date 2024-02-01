/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(252, 236);
        verticalLayout_2 = new QVBoxLayout(login);
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEdit = new QLineEdit(login);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(login);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_2->addWidget(lineEdit_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        radioButton = new QRadioButton(login);
        radioButton->setObjectName("radioButton");

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(login);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setChecked(true);

        verticalLayout->addWidget(radioButton_2);

        lineEdit_3 = new QLineEdit(login);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(login);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(login);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

        pushButton_3 = new QPushButton(login);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout_2->addWidget(pushButton_3);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "\320\262\321\205\320\276\320\264", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("login", "\320\273\320\276\320\263\320\270\320\275", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("login", "\320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        radioButton->setText(QCoreApplication::translate("login", "\321\202\320\276\320\272\320\265\320\275 \320\261\320\265\320\267 \321\215\320\272\321\200\320\260\320\275", nullptr));
        radioButton_2->setText(QCoreApplication::translate("login", "\321\202\320\276\320\272\320\265\320\275 \321\201 \321\215\320\272\321\200\320\260\320\275\320\276\320\274", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("login", "\321\202\320\276\320\272\320\265\320\275", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "\320\262\320\276\320\271\321\202\320\270", nullptr));
        pushButton_2->setText(QCoreApplication::translate("login", "\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("login", "\320\262\321\213\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
