/********************************************************************************
** Form generated from reading UI file 'sensor_form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSOR_FORM_H
#define UI_SENSOR_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sensor_form
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QStatusBar *statusbar;

    void setupUi(QWidget *sensor_form)
    {
        if (sensor_form->objectName().isEmpty())
            sensor_form->setObjectName(QString::fromUtf8("sensor_form"));
        sensor_form->resize(1001, 694);
        verticalLayout_3 = new QVBoxLayout(sensor_form);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(sensor_form);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        pushButton = new QPushButton(sensor_form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        scrollArea = new QScrollArea(sensor_form);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 963, 600));
        scrollAreaWidgetContents->setMinimumSize(QSize(800, 600));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        horizontalLayout_2->addLayout(verticalLayout_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        statusbar = new QStatusBar(sensor_form);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));

        verticalLayout_3->addWidget(statusbar);


        retranslateUi(sensor_form);

        QMetaObject::connectSlotsByName(sensor_form);
    } // setupUi

    void retranslateUi(QWidget *sensor_form)
    {
        sensor_form->setWindowTitle(QApplication::translate("sensor_form", "MainWindow", nullptr));
        comboBox->setItemText(0, QApplication::translate("sensor_form", "topic_Ultrasound", nullptr));
        comboBox->setItemText(1, QApplication::translate("sensor_form", "topic_ENV", nullptr));

        pushButton->setText(QApplication::translate("sensor_form", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sensor_form: public Ui_sensor_form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSOR_FORM_H
