/********************************************************************************
** Form generated from reading UI file 'install_common.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_COMMON_H
#define UI_INSTALL_COMMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_install_common
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_9;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QPushButton *pushButton_2;

    void setupUi(QWidget *install_common)
    {
        if (install_common->objectName().isEmpty())
            install_common->setObjectName(QString::fromUtf8("install_common"));
        install_common->resize(757, 551);
        label = new QLabel(install_common);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 80, 121, 17));
        label_2 = new QLabel(install_common);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 0, 67, 17));
        comboBox = new QComboBox(install_common);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 0, 501, 25));
        checkBox_4 = new QCheckBox(install_common);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(420, 80, 121, 23));
        checkBox = new QCheckBox(install_common);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(120, 80, 92, 23));
        checkBox_2 = new QCheckBox(install_common);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(220, 80, 92, 23));
        checkBox_5 = new QCheckBox(install_common);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(550, 80, 92, 23));
        checkBox_3 = new QCheckBox(install_common);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(320, 80, 92, 23));
        checkBox_10 = new QCheckBox(install_common);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(550, 110, 92, 23));
        checkBox_7 = new QCheckBox(install_common);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(220, 110, 121, 23));
        checkBox_8 = new QCheckBox(install_common);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(360, 110, 61, 23));
        checkBox_6 = new QCheckBox(install_common);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(120, 110, 92, 23));
        checkBox_9 = new QCheckBox(install_common);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(420, 110, 111, 23));
        label_3 = new QLabel(install_common);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 40, 51, 17));
        comboBox_2 = new QComboBox(install_common);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(120, 40, 501, 25));
        pushButton = new QPushButton(install_common);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(640, 0, 89, 25));
        textEdit = new QTextEdit(install_common);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(190, 180, 301, 201));
        pushButton_2 = new QPushButton(install_common);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 440, 89, 25));

        retranslateUi(install_common);

        QMetaObject::connectSlotsByName(install_common);
    } // setupUi

    void retranslateUi(QWidget *install_common)
    {
        install_common->setWindowTitle(QApplication::translate("install_common", "Form", nullptr));
        label->setText(QApplication::translate("install_common", "Message Type:", nullptr));
        label_2->setText(QApplication::translate("install_common", "Device:", nullptr));
        checkBox_4->setText(QApplication::translate("install_common", "GroundDetect", nullptr));
        checkBox->setText(QApplication::translate("install_common", "Distance", nullptr));
        checkBox_2->setText(QApplication::translate("install_common", "Environment", nullptr));
        checkBox_5->setText(QApplication::translate("install_common", "Image", nullptr));
        checkBox_3->setText(QApplication::translate("install_common", "GPS", nullptr));
        checkBox_10->setText(QApplication::translate("install_common", "MotorAxle", nullptr));
        checkBox_7->setText(QApplication::translate("install_common", "MotorSteering", nullptr));
        checkBox_8->setText(QApplication::translate("install_common", "UPS", nullptr));
        checkBox_6->setText(QApplication::translate("install_common", "IMU", nullptr));
        checkBox_9->setText(QApplication::translate("install_common", "WheelState", nullptr));
        label_3->setText(QApplication::translate("install_common", "Node:", nullptr));
        pushButton->setText(QApplication::translate("install_common", "select", nullptr));
        pushButton_2->setText(QApplication::translate("install_common", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class install_common: public Ui_install_common {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_COMMON_H
