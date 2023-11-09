/********************************************************************************
** Form generated from reading UI file 'data_server_record.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_SERVER_RECORD_H
#define UI_DATA_SERVER_RECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_data_server_record
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_4;

    void setupUi(QWidget *data_server_record)
    {
        if (data_server_record->objectName().isEmpty())
            data_server_record->setObjectName(QString::fromUtf8("data_server_record"));
        data_server_record->resize(521, 321);
        label = new QLabel(data_server_record);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 141, 17));
        label_2 = new QLabel(data_server_record);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 90, 131, 17));
        label_3 = new QLabel(data_server_record);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 140, 121, 17));
        lineEdit = new QLineEdit(data_server_record);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(220, 30, 161, 25));
        lineEdit_2 = new QLineEdit(data_server_record);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(220, 90, 161, 25));
        lineEdit_3 = new QLineEdit(data_server_record);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(220, 140, 161, 25));
        pushButton = new QPushButton(data_server_record);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 30, 89, 25));
        pushButton_2 = new QPushButton(data_server_record);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 90, 89, 25));
        pushButton_3 = new QPushButton(data_server_record);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(400, 140, 89, 25));
        pushButton_4 = new QPushButton(data_server_record);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(220, 190, 151, 25));
        label_4 = new QLabel(data_server_record);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 190, 67, 17));

        retranslateUi(data_server_record);

        QMetaObject::connectSlotsByName(data_server_record);
    } // setupUi

    void retranslateUi(QWidget *data_server_record)
    {
        data_server_record->setWindowTitle(QApplication::translate("data_server_record", "Form", nullptr));
        label->setText(QApplication::translate("data_server_record", "Sampling Step(ms):", nullptr));
        label_2->setText(QApplication::translate("data_server_record", "Auto Save Time(s):", nullptr));
        label_3->setText(QApplication::translate("data_server_record", "Record Time(s):", nullptr));
        pushButton->setText(QApplication::translate("data_server_record", "set", nullptr));
        pushButton_2->setText(QApplication::translate("data_server_record", "set", nullptr));
        pushButton_3->setText(QApplication::translate("data_server_record", "set", nullptr));
        pushButton_4->setText(QApplication::translate("data_server_record", "Enabled Record", nullptr));
        label_4->setText(QApplication::translate("data_server_record", "Record:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class data_server_record: public Ui_data_server_record {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_SERVER_RECORD_H
