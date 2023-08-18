#include "install_option.h"
#include "./../ui_install_option.h"

install_option::install_option(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_option)
{
    ui->setupUi(this);
}

install_option::~install_option()
{
    delete ui;
}
