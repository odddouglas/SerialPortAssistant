#include "mainwindow.h"

#include <QApplication>

MainWindow *pw = nullptr; // ����ȫ��ָ����� pw����ʼֵΪ��ָ�루nullptr��

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // ���� Qt Ӧ�ó�����󣬹����¼�ѭ��
    MainWindow w; // ���� MainWindow ���ڶ���

    pw = &w; // �� MainWindow ʵ���ĵ�ַ��ֵ��ȫ��ָ�� pw��ʹ��ָ��������

    w.show(); // ��ʾ������
    return a.exec(); // ���� Qt �¼�ѭ��
}
