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
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *install_device_infor)
    {
        if (install_device_infor->objectName().isEmpty())
            install_device_infor->setObjectName(QString::fromUtf8("install_device_infor"));
        install_device_infor->resize(888, 565);
        textBrowser = new QTextBrowser(install_device_infor);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 50, 861, 471));
        pushButton = new QPushButton(install_device_infor);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 530, 89, 25));
        label = new QLabel(install_device_infor);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 101, 17));
        label_2 = new QLabel(install_device_infor);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 10, 121, 17));

        retranslateUi(install_device_infor);

        QMetaObject::connectSlotsByName(install_device_infor);
    } // setupUi

    void retranslateUi(QWidget *install_device_infor)
    {
        install_device_infor->setWindowTitle(QApplication::translate("install_device_infor", "Form", nullptr));
        pushButton->setText(QApplication::translate("install_device_infor", "close", nullptr));
        label->setText(QApplication::translate("install_device_infor", "Host Name:", nullptr));
        label_2->setText(QApplication::translate("install_device_infor", "Undefinded Text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_device_infor: public Ui_install_device_infor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_DEVICE_INFOR_H
