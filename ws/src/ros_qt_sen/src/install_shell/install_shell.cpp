#include "install_shell.h"
#include "ui_install_shell.h"

install_shell::install_shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::install_shell)
{
    ui->setupUi(this);
}

install_shell::~install_shell()
{
    delete ui;
}
