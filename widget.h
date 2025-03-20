#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void init_widget(void);
private slots:
    void on_pushButton_fresh_com_clicked();
    void on_pushButton_onoff_com_clicked();

private:
    Ui::Widget *ui;
    QSerialPort my_Serial; //创建串口组件
};
#endif // WIDGET_H
