#ifndef install_common_H
#define install_common_H

#include <QWidget>
#include <libssh/sftp.h>
#include <libssh/libssh.h>
namespace Ui {
class install_common;
}

class install_common : public QWidget
{
    Q_OBJECT

public:
    explicit install_common(QWidget *parent = nullptr,QString device="");
    ~install_common();

private:
    Ui::install_common *ui;
    int write_sftp(ssh_session session, sftp_session sftp);

private slots:
    void on_device_select_pushbutton_clicked();
    void on_save_pushbutton_clicked();
    void on_load_file_pushbutton_clicked();
    void on_save_file_pushbutton_clicked();
};

#endif // install_common_H
