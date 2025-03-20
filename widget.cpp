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
    on_pushButton_fresh_com_clicked();//��ʼ��ʱ�Զ�ˢ��һ��
    ui->pushButton_led->setStyleSheet("background-color:grey;");
}

void Widget::on_pushButton_fresh_com_clicked()
{
    ui->comboBox_com->clear(); //��ն˿�ѡ��
    foreach(const QSerialPortInfo &Info,QSerialPortInfo::availablePorts()) //��ȡ���õĶ˿�
    {
        ui->comboBox_com->addItem(Info.portName()); //��ӵ��˿�ѡ����
    }
}

void Widget::on_pushButton_onoff_com_clicked()
{
    if(ui->pushButton_onoff_com->text()=="OPEN COM")
    {

        my_Serial.setPortName(ui->comboBox_com->currentText()); //���ö˿�
        my_Serial.setBaudRate(ui->comboBox_baud->currentText().toInt()); //���ò�����

        my_Serial.open(QIODevice::ReadWrite); //�򿪴��ڣ�ģʽΪֻ��
        qDebug()<<"OPEN COM";
        if(my_Serial.isOpen())//������ڴ�
        {
            ui->pushButton_led->setStyleSheet("background-color:green;");//����ָʾ��
            ui->pushButton_onoff_com->setText("CLOSE COM"); //�޸���ʾ����
            ui->label_info0->setText("[correct] Open the port successfully!"); //��ʾ�ɹ�
        }
        else
        {
            ui->label_info0->setText("[error] Open the port failed!"); //��ʾʧ��
        }
    }
    else
    {
        my_Serial.close();
        qDebug()<<"CLOSE COM";
        if(!my_Serial.isOpen())//�������δ��
        {
            ui->pushButton_led->setStyleSheet("background-color:grey;");//����ָʾ��
            ui->pushButton_onoff_com->setText("OPEN COM"); //�޸���ʾ����
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

