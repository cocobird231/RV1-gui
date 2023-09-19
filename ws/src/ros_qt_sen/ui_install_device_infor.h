/********************************************************************************
** Form generated from reading UI file 'install_device_infor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_DEVICE_INFOR_H
#define UI_INSTALL_DEVICE_INFOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_device_infor
{
public:
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_4;

    void setupUi(QWidget *install_device_infor)
    {
        if (install_device_infor->objectName().isEmpty())
            install_device_infor->setObjectName(QString::fromUtf8("install_device_infor"));
        install_device_infor->resize(888, 618);
        textBrowser = new QTextBrowser(install_device_infor);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 60, 861, 481));
        pushButton = new QPushButton(install_device_infor);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 570, 89, 25));
        label_2 = new QLabel(install_device_infor);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 20, 121, 17));
        pushButton_2 = new QPushButton(install_device_infor);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(718, 10, 121, 25));
        label_4 = new QLabel(install_device_infor);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 20, 81, 17));

        retranslateUi(install_device_infor);

        QMetaObject::connectSlotsByName(install_device_infor);
    } // setupUi

    void retranslateUi(QWidget *install_device_infor)
    {
        install_device_infor->setWindowTitle(QApplication::translate("install_device_infor", "Form", nullptr));
        pushButton->setText(QApplication::translate("install_device_infor", "close", nullptr));
        label_2->setText(QApplication::translate("install_device_infor", "Undefinded Text", nullptr));
        pushButton_2->setText(QApplication::translate("install_device_infor", "SFTP\346\211\223\351\226\213\350\267\257\345\276\221", nullptr));
        label_4->setText(QApplication::translate("install_device_infor", "Ip address:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_device_infor: public Ui_install_device_infor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_DEVICE_INFOR_H
