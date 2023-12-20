/********************************************************************************
** Form generated from reading UI file 'image_form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_FORM_H
#define UI_IMAGE_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Image_form
{
public:
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Image_form)
    {
        if (Image_form->objectName().isEmpty())
            Image_form->setObjectName(QString::fromUtf8("Image_form"));
        Image_form->resize(1400, 900);
        comboBox = new QComboBox(Image_form);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(50, 10, 741, 25));
        pushButton = new QPushButton(Image_form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 40, 741, 25));
        pushButton_2 = new QPushButton(Image_form);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 70, 341, 25));
        label = new QLabel(Image_form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 110, 1280, 720));
        pushButton_3 = new QPushButton(Image_form);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(410, 70, 381, 25));

        retranslateUi(Image_form);

        QMetaObject::connectSlotsByName(Image_form);
    } // setupUi

    void retranslateUi(QWidget *Image_form)
    {
        Image_form->setWindowTitle(QApplication::translate("Image_form", "Form", nullptr));
        pushButton->setText(QApplication::translate("Image_form", "\346\233\264\346\226\260", nullptr));
        pushButton_2->setText(QApplication::translate("Image_form", "\351\200\243\347\267\232", nullptr));
        label->setText(QApplication::translate("Image_form", "image", nullptr));
        pushButton_3->setText(QApplication::translate("Image_form", "\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Image_form: public Ui_Image_form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_FORM_H
