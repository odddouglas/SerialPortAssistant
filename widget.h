#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QLatin1Char>
#include <QDebug>
#include <qforeach.h>

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

    void on_pushButton_clear_rx_clicked();

    void on_pushButton_clear_tx_clicked();

    void msgRecevied();

    void on_pushButton_hex_rx_clicked();

    void on_pushButton_str_rx_clicked();

    void on_pushButton_hex_tx_clicked();

    void on_pushButton_str_tx_clicked();

    void on_pushButton_tx_clicked();

private:
    Ui::Widget *ui;
    QSerialPort my_Serial; //创建串口组件
    int rx_num,tx_num; //收发的字节数
    bool rx_mode=0,tx_mode=0;
};
#endif // WIDGET_H
