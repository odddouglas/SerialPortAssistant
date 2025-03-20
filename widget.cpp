#include "widget.h"
#include "./ui_widget.h"
#include <qforeach.h>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->init_widget();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_widget()
{
    on_pushButton_fresh_com_clicked();//初始化时自动刷新一次
    ui->pushButton_led->setStyleSheet("background-color:grey;");
}

void Widget::on_pushButton_fresh_com_clicked()
{
    ui->comboBox_com->clear(); //清空端口选项
    foreach(const QSerialPortInfo &Info,QSerialPortInfo::availablePorts()) //获取可用的端口
    {
        ui->comboBox_com->addItem(Info.portName()); //添加到端口选项中
    }
}

void Widget::on_pushButton_onoff_com_clicked()
{
    if(ui->pushButton_onoff_com->text()=="OPEN COM")
    {

        my_Serial.setPortName(ui->comboBox_com->currentText()); //设置端口
        my_Serial.setBaudRate(ui->comboBox_baud->currentText().toInt()); //设置波特率

        my_Serial.open(QIODevice::ReadWrite); //打开串口，模式为只读
        qDebug()<<"OPEN COM";
        if(my_Serial.isOpen())//如果串口打开
        {
            ui->pushButton_led->setStyleSheet("background-color:green;");//界面指示灯
            ui->pushButton_onoff_com->setText("CLOSE COM"); //修改显示字样
            ui->label_info0->setText("[correct] Open the port successfully!"); //提示成功
        }
        else
        {
            ui->label_info0->setText("[error] Open the port failed!"); //提示失败
        }
    }
    else
    {
        my_Serial.close();
        qDebug()<<"CLOSE COM";
        if(!my_Serial.isOpen())//如果串口未打开
        {
            ui->pushButton_led->setStyleSheet("background-color:grey;");//界面指示灯
            ui->pushButton_onoff_com->setText("OPEN COM"); //修改显示字样
            ui->label_info0->setText("[correct] Close the port successfully!");
        }
        else
        {
            ui->label_info0->setText("[error] Close the port failed!");
        }
    }
}


void Widget::on_pushButton_clear_rx_clicked()
{
    ui->textBrowser_rx->clear();
}

