/********************************************************************************
** Form generated from reading UI file 'install_option.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_OPTION_H
#define UI_INSTALL_OPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_option
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *install_option)
    {
        if (install_option->objectName().isEmpty())
            install_option->setObjectName(QString::fromUtf8("install_option"));
        install_option->resize(400, 229);
        label = new QLabel(install_option);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 121, 17));
        label_2 = new QLabel(install_option);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 80, 101, 17));
        label_3 = new QLabel(install_option);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 41, 17));
        comboBox = new QComboBox(install_option);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 40, 171, 25));
        lineEdit = new QLineEdit(install_option);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 80, 171, 25));
        lineEdit_2 = new QLineEdit(install_option);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(160, 120, 171, 25));
        pushButton = new QPushButton(install_option);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 180, 89, 25));
        label_4 = new QLabel(install_option);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 10, 91, 17));
        label_5 = new QLabel(install_option);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 10, 171, 17));

        retranslateUi(install_option);

        QMetaObject::connectSlotsByName(install_option);
    } // setupUi

    void retranslateUi(QWidget *install_option)
    {
        install_option->setWindowTitle(QApplication::translate("install_option", "Form", nullptr));
        label->setText(QApplication::translate("install_option", "Package Name:", nullptr));
        label_2->setText(QApplication::translate("install_option", "Interface:", nullptr));
        label_3->setText(QApplication::translate("install_option", "IP:", nullptr));
        lineEdit->setText(QApplication::translate("install_option", "eth0", nullptr));
        lineEdit_2->setText(QApplication::translate("install_option", "dhcp", nullptr));
        pushButton->setText(QApplication::translate("install_option", "OK", nullptr));
        label_4->setText(QApplication::translate("install_option", "Host Name:", nullptr));
        label_5->setText(QApplication::translate("install_option", "Undefined Text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_option: public Ui_install_option {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_OPTION_H
