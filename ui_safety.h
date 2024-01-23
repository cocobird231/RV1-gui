/********************************************************************************
** Form generated from reading UI file 'safety.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAFETY_H
#define UI_SAFETY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_safety
{
public:
    QLabel *label;
    QLabel *label_2;
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
    QLabel *label_13;

    void setupUi(QWidget *safety)
    {
        if (safety->objectName().isEmpty())
            safety->setObjectName(QString::fromUtf8("safety"));
        safety->resize(651, 670);
        label = new QLabel(safety);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 40, 491, 531));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(safety);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 40, 81, 20));
        label_3 = new QLabel(safety);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(246, 40, 171, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(safety);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(430, 40, 71, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(safety);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 190, 21, 201));
        label_6 = new QLabel(safety);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(480, 190, 21, 201));
        label_7 = new QLabel(safety);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 510, 91, 20));
        label_8 = new QLabel(safety);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(250, 510, 171, 20));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(safety);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(430, 510, 71, 20));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(safety);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(150, 40, 21, 121));
        label_11 = new QLabel(safety);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(480, 40, 21, 131));
        label_12 = new QLabel(safety);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(480, 400, 21, 121));
        label_13 = new QLabel(safety);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(150, 410, 21, 111));

        retranslateUi(safety);

        QMetaObject::connectSlotsByName(safety);
    } // setupUi

    void retranslateUi(QWidget *safety)
    {
        safety->setWindowTitle(QApplication::translate("safety", "Form", nullptr));
        label->setText(QApplication::translate("safety", "\350\273\212", nullptr));
        label_2->setText(QApplication::translate("safety", "\345\267\246\345\211\215", nullptr));
        label_3->setText(QApplication::translate("safety", "\345\211\215", nullptr));
        label_4->setText(QApplication::translate("safety", "\345\217\263\345\211\215", nullptr));
        label_5->setText(QApplication::translate("safety", "\345\267\246", nullptr));
        label_6->setText(QApplication::translate("safety", "\345\217\263", nullptr));
        label_7->setText(QApplication::translate("safety", "\345\267\246\345\276\214", nullptr));
        label_8->setText(QApplication::translate("safety", "\345\276\214", nullptr));
        label_9->setText(QApplication::translate("safety", "\345\217\263\345\276\214", nullptr));
        label_10->setText(QApplication::translate("safety", "\345\267\246\345\211\215-2", nullptr));
        label_11->setText(QApplication::translate("safety", "\345\217\263\345\211\215-2", nullptr));
        label_12->setText(QApplication::translate("safety", "\345\217\263\345\276\214-2", nullptr));
        label_13->setText(QApplication::translate("safety", "\345\267\246\345\276\214-2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class safety: public Ui_safety {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAFETY_H
