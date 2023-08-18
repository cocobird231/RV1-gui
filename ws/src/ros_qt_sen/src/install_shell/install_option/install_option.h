#ifndef INSTALL_OPTION_H
#define INSTALL_OPTION_H

#include <QWidget>

namespace Ui {
class install_option;
}

class install_option : public QWidget
{
    Q_OBJECT

public:
    explicit install_option(QWidget *parent = nullptr);
    ~install_option();

private:
    Ui::install_option *ui;
};

#endif // INSTALL_OPTION_H
