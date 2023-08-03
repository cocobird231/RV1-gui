/********************************************************************************
** Form generated from reading UI file 'install_shell.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_SHELL_H
#define UI_INSTALL_SHELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_shell
{
public:
    QPushButton *pushButton;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QListView *listView;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QListView *listView_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_5;

    void setupUi(QWidget *install_shell)
    {
        if (install_shell->objectName().isEmpty())
            install_shell->setObjectName(QString::fromUtf8("install_shell"));
        install_shell->resize(887, 562);
        pushButton = new QPushButton(install_shell);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(610, 20, 89, 25));
        comboBox = new QComboBox(install_shell);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 20, 571, 25));
        pushButton_2 = new QPushButton(install_shell);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(720, 20, 89, 25));
        listView = new QListView(install_shell);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(40, 70, 256, 192));
        pushButton_3 = new QPushButton(install_shell);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(610, 70, 89, 25));
        pushButton_4 = new QPushButton(install_shell);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(610, 110, 89, 25));
        listView_2 = new QListView(install_shell);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));
        listView_2->setGeometry(QRect(320, 70, 256, 192));
        label = new QLabel(install_shell);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 300, 67, 17));
        label_2 = new QLabel(install_shell);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 340, 67, 17));
        label_3 = new QLabel(install_shell);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 370, 81, 17));
        lineEdit = new QLineEdit(install_shell);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 340, 171, 25));
        lineEdit_2 = new QLineEdit(install_shell);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 370, 171, 25));
        pushButton_5 = new QPushButton(install_shell);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 410, 271, 31));

        retranslateUi(install_shell);

        QMetaObject::connectSlotsByName(install_shell);
    } // setupUi

    void retranslateUi(QWidget *install_shell)
    {
        install_shell->setWindowTitle(QApplication::translate("install_shell", "Form", nullptr));
        pushButton->setText(QApplication::translate("install_shell", "update", nullptr));
        pushButton_2->setText(QApplication::translate("install_shell", "choose", nullptr));
        pushButton_3->setText(QApplication::translate("install_shell", "update", nullptr));
        pushButton_4->setText(QApplication::translate("install_shell", "install", nullptr));
        label->setText(QApplication::translate("install_shell", "infor", nullptr));
        label_2->setText(QApplication::translate("install_shell", "IP:", nullptr));
        label_3->setText(QApplication::translate("install_shell", "HostName:", nullptr));
        pushButton_5->setText(QApplication::translate("install_shell", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_shell: public Ui_install_shell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_SHELL_H
