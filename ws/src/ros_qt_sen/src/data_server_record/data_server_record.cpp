#include "data_server_record.h"
#include "./../../ui_data_server_record.h"

data_server_record::data_server_record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_server_record)
{
    ui->setupUi(this);
}

data_server_record::~data_server_record()
{
    delete ui;
}
