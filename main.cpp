#include "mainwindow.h"

#include <QApplication>

MainWindow *pw = nullptr; // 定义全局指针变量 pw，初始值为空指针（nullptr）

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // 创建 Qt 应用程序对象，管理事件循环
    MainWindow w; // 创建 MainWindow 窗口对象

    pw = &w; // 将 MainWindow 实例的地址赋值给全局指针 pw，使其指向主窗口

    w.show(); // 显示主窗口
    return a.exec(); // 进入 Qt 事件循环
}
