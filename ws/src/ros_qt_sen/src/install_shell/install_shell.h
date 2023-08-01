#ifndef INSTALL_SHELL_H
#define INSTALL_SHELL_H

#include <QWidget>

namespace Ui {
class install_shell;
}

class install_shell : public QWidget
{
    Q_OBJECT

public:
    explicit install_shell(QWidget *parent = nullptr);
    ~install_shell();

private:
    Ui::install_shell *ui;
};

#endif // INSTALL_SHELL_H
