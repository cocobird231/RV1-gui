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

    void setupUi(QWidget *install_process)
    {
        if (install_process->objectName().isEmpty())
            install_process->setObjectName(QString::fromUtf8("install_process"));
        install_process->resize(984, 587);
        label = new QLabel(install_process);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 91, 17));
        label_2 = new QLabel(install_process);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 20, 131, 17));
        textBrowser = new QTextBrowser(install_process);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 50, 931, 471));
        pushButton = new QPushButton(install_process);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(450, 550, 89, 25));

        retranslateUi(install_process);

        QMetaObject::connectSlotsByName(install_process);
    } // setupUi

    void retranslateUi(QWidget *install_process)
    {
        install_process->setWindowTitle(QApplication::translate("install_process", "Form", nullptr));
        label->setText(QApplication::translate("install_process", "Host Name:", nullptr));
        label_2->setText(QApplication::translate("install_process", "Undefine Text", nullptr));
        pushButton->setText(QApplication::translate("install_process", "close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_process: public Ui_install_process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_PROCESS_H
