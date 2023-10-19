/********************************************************************************
** Form generated from reading UI file 'install_process.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_PROCESS_H
#define UI_INSTALL_PROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_process
{
public:
    QLabel *label;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *install_process)
    {
        if (install_process->objectName().isEmpty())
            install_process->setObjectName(QString::fromUtf8("install_process"));
        install_process->resize(1112, 742);
        label = new QLabel(install_process);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 91, 17));
        label_2 = new QLabel(install_process);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 20, 131, 17));
        textBrowser = new QTextBrowser(install_process);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 130, 1061, 521));
        pushButton = new QPushButton(install_process);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(530, 700, 89, 25));
        label_3 = new QLabel(install_process);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 50, 101, 17));
        label_4 = new QLabel(install_process);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 90, 91, 17));
        label_5 = new QLabel(install_process);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(340, 20, 91, 17));
        label_6 = new QLabel(install_process);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(340, 60, 81, 17));
        label_7 = new QLabel(install_process);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(340, 90, 67, 17));
        label_8 = new QLabel(install_process);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(140, 50, 121, 17));
        label_9 = new QLabel(install_process);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(140, 90, 121, 17));
        label_10 = new QLabel(install_process);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(440, 20, 121, 17));
        label_11 = new QLabel(install_process);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(440, 60, 121, 17));
        label_12 = new QLabel(install_process);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(440, 90, 121, 17));

        retranslateUi(install_process);

        QMetaObject::connectSlotsByName(install_process);
    } // setupUi

    void retranslateUi(QWidget *install_process)
    {
        install_process->setWindowTitle(QApplication::translate("install_process", "Form", nullptr));
        label->setText(QApplication::translate("install_process", "Host Name:", nullptr));
        label_2->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        pushButton->setText(QApplication::translate("install_process", "close", nullptr));
        label_3->setText(QApplication::translate("install_process", "mac address:", nullptr));
        label_4->setText(QApplication::translate("install_process", "IP address:", nullptr));
        label_5->setText(QApplication::translate("install_process", "pack name:", nullptr));
        label_6->setText(QApplication::translate("install_process", "interface:", nullptr));
        label_7->setText(QApplication::translate("install_process", "IP rule:", nullptr));
        label_8->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        label_9->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        label_10->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        label_11->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        label_12->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_process: public Ui_install_process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_PROCESS_H
