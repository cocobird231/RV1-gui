#ifndef DATA_SERVE_RECORD_H
#define DATA_SERVE_RECORD_H

#include <QWidget>

namespace Ui {
class data_server_record;
}

class data_server_record : public QWidget
{
    Q_OBJECT

public:
    explicit data_server_record(QWidget *parent = nullptr);
    ~data_server_record();

private:
    Ui::data_server_record *ui;
};

#endif // DATA_SERVE_RECORD_H
