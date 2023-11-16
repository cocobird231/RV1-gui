
#include "mainwindow.h"
//#include "form.h"
#include <QApplication>

inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}
int main(int argc, char * argv[])
{
    rclcpp::init(0,NULL);
    QApplication a(argc, argv);

    if(exists_test1("./mirdc.ico")){
    a.setWindowIcon(QIcon("./mirdc.ico"));
    }
    if (exists_test1("/ros2_ws/src/cpp_gui/mirdc.ico"))
    {
        a.setWindowIcon(QIcon("/ros2_ws/src/cpp_gui/mirdc.ico"));
    }
    
    MainWindow w;
    w.setWindowTitle("無人載具圖形化介面顯示");
    w.show(); //TO DO
    

    return a.exec();
}
