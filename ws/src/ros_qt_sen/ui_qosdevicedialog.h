/********************************************************************************
** Form generated from reading UI file 'qosdevicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QOSDEVICEDIALOG_H
#define UI_QOSDEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QosDeviceDialog
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;

    void setupUi(QDialog *QosDeviceDialog)
    {
        if (QosDeviceDialog->objectName().isEmpty())
            QosDeviceDialog->setObjectName(QString::fromUtf8("QosDeviceDialog"));
        QosDeviceDialog->resize(580, 441);
        comboBox = new QComboBox(QosDeviceDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(180, 20, 381, 31));
        label = new QLabel(QosDeviceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 101, 17));
        label_2 = new QLabel(QosDeviceDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 70, 67, 17));
        label_3 = new QLabel(QosDeviceDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 110, 67, 17));
        label_4 = new QLabel(QosDeviceDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 150, 67, 17));
        label_5 = new QLabel(QosDeviceDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 190, 67, 17));
        label_6 = new QLabel(QosDeviceDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 230, 101, 17));
        label_7 = new QLabel(QosDeviceDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 270, 91, 17));
        label_8 = new QLabel(QosDeviceDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 310, 81, 17));
        label_9 = new QLabel(QosDeviceDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 350, 211, 17));
        pushButton = new QPushButton(QosDeviceDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 400, 89, 25));
        comboBox_2 = new QComboBox(QosDeviceDialog);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(180, 70, 381, 25));
        comboBox_3 = new QComboBox(QosDeviceDialog);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(180, 150, 381, 25));
        comboBox_4 = new QComboBox(QosDeviceDialog);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(180, 190, 381, 25));
        comboBox_5 = new QComboBox(QosDeviceDialog);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(180, 310, 381, 25));
        lineEdit = new QLineEdit(QosDeviceDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 110, 381, 25));
        lineEdit_2 = new QLineEdit(QosDeviceDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 230, 381, 25));
        lineEdit_3 = new QLineEdit(QosDeviceDialog);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(180, 270, 381, 25));
        lineEdit_4 = new QLineEdit(QosDeviceDialog);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(240, 350, 321, 25));

        retranslateUi(QosDeviceDialog);

        QMetaObject::connectSlotsByName(QosDeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *QosDeviceDialog)
    {
        QosDeviceDialog->setWindowTitle(QApplication::translate("QosDeviceDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("QosDeviceDialog", "Topic Name", nullptr));
        label_2->setText(QApplication::translate("QosDeviceDialog", "History", nullptr));
        label_3->setText(QApplication::translate("QosDeviceDialog", "depth", nullptr));
        label_4->setText(QApplication::translate("QosDeviceDialog", "reliability", nullptr));
        label_5->setText(QApplication::translate("QosDeviceDialog", "durability", nullptr));
        label_6->setText(QApplication::translate("QosDeviceDialog", "deadline_ms", nullptr));
        label_7->setText(QApplication::translate("QosDeviceDialog", "lifespan_ms", nullptr));
        label_8->setText(QApplication::translate("QosDeviceDialog", "liveliness", nullptr));
        label_9->setText(QApplication::translate("QosDeviceDialog", "liveliness_lease_duration_ms", nullptr));
        pushButton->setText(QApplication::translate("QosDeviceDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QosDeviceDialog: public Ui_QosDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QOSDEVICEDIALOG_H