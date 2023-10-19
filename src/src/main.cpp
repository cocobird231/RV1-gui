
#include "mainwindow.h"
//#include "form.h"
#include <QApplication>

int main(int argc, char * argv[])
{
    rclcpp::init(0,NULL);
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon("./mirdc.ico"));
    w.setWindowTitle("無人載具圖形化介面顯示");
    w.show(); //TO DO
    

    return a.exec();
}
