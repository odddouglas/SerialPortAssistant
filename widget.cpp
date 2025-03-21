#include "widget.h"
#include "./ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->init_widget();// 初始化界面
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_widget()
{
    on_pushButton_fresh_com_clicked();//初始化时自动刷新一次
    ui->pushButton_led->setStyleSheet("background-color:grey;");// 设置指示灯初始状态（灰色）
    ui->comboBox_baud->setCurrentText("115200");
    ui->label_rx_num->setText(QString::number(this->rx_num));// 更新接收字节数显示
    ui->label_tx_num->setText(QString::number(this->tx_num)); // 更新发送字节数显示
}

void Widget::on_pushButton_fresh_com_clicked()
{
    ui->comboBox_com->clear(); //清空端口选项
    ui->label_info0->setText("[correct] freshed the COM");
    foreach(const QSerialPortInfo &Info,QSerialPortInfo::availablePorts()) //获取可用的端口
    {
        ui->comboBox_com->addItem(Info.portName()); // 添加串口到下拉选项
    }
}

void Widget::on_pushButton_onoff_com_clicked()
{
    //ui->label_info0->setText("[");
    if(ui->pushButton_onoff_com->text()=="OPEN")
    {
        my_Serial.setPortName(ui->comboBox_com->currentText()); //设置端口名
        my_Serial.setBaudRate(ui->comboBox_baud->currentText().toInt()); //设置波特率

        my_Serial.open(QIODevice::ReadWrite); //打开串口（读写模式）
        if(my_Serial.isOpen())//如果串口打开
        {
            connect(&my_Serial,&QSerialPort::readyRead,this,&Widget::msgRecevied);//绑定串口接收信号
            ui->pushButton_led->setStyleSheet("background-color:green;");//界面指示灯
            ui->pushButton_onoff_com->setText("CLOSE");  // 按钮显示“CLOSE”
            ui->label_info0->setText("[correct] Opened the port successfully!"); // 提示成功打开
        }
        else
        {
            ui->label_info0->setText("[error] Opened the port failed!"); // 提示打开失败
        }
    }
    else
    {
        my_Serial.close();// 关闭串口
        if(!my_Serial.isOpen())//如果串口未打开
        {
            ui->pushButton_led->setStyleSheet("background-color:grey;");//界面指示灯
            ui->pushButton_onoff_com->setText("OPEN"); // 按钮显示“OPEN”
            ui->label_info0->setText("[correct] Closed the port successfully!"); // 提示成功关闭
        }
        else
        {
            ui->label_info0->setText("[error] Closed the port failed!");// 提示关闭失败
        }
    }
}

void Widget::on_pushButton_clear_rx_clicked()
{
    ui->textBrowser_rx->clear(); //清空接收区
    ui->label_info0->setText("[correct] Cleared the BUF(rx) successfully!");// 提示清空成功
    this->rx_num=0;// 归零接收计数
    //ui->label_rx_num->setText(" "); //清空接收字节数
}


void Widget::on_pushButton_clear_tx_clicked()
{
    ui->textEdit_tx->clear(); //清空发送区
    ui->label_info0->setText("[correct] Cleared the BUF(tx) successfully!");// 提示清空成功
    this->tx_num=0; // 归零发送计数
    //ui->label_tx_num->setText(" "); //清空发送字节数
}

void Widget::on_pushButton_hex_rx_clicked()
{
    ui->label_rx->setText("RX [HEX]");
    ui->label_info0->setText("[correct] Toggled the HEX(rx_mode) successfully!");// 提示转换成功
    this->rx_mode=1; //rx的hex标志位
}


void Widget::on_pushButton_str_rx_clicked()
{
    ui->label_rx->setText("RX [STR]");
    ui->label_info0->setText("[correct] Toggled the STR(rx_mode) successfully!");// 提示转换成功
    this->rx_mode=0; //rx的str标志位
}


void Widget::on_pushButton_hex_tx_clicked()
{
    ui->label_tx->setText("TX [HEX]");
    ui->label_info0->setText("[correct] Toggled the HEX(tx_mode) successfully!");// 提示转换成功
    this->rx_mode=1; //tx的hex标志位
}


void Widget::on_pushButton_str_tx_clicked()
{
    ui->label_tx->setText("TX [STR]");
    ui->label_info0->setText("[correct] Toggled the STR(tx_mode) successfully!");// 提示转换成功
    this->rx_mode=0; //tx的str标志位
}


void Widget::msgRecevied()
{
    QByteArray buf = my_Serial.readAll(); // 读取串口缓冲区数据
    this->rx_num += buf.size();// 统计接收到的字节数

    if(this->rx_mode==0) // 字符串模式接收
    {
        ui->textBrowser_rx->insertPlainText(tr(buf)); //将接收到的string字符显示到接收区(tr可以将参数转换成QString)
    }
    else// HEX 模式接收
    {
        QString str;
        for(int i=0;i<buf.size();i++)
        {
            str+= QString("%1").arg(buf[i]&0xff,2,16,QLatin1Char('0'));// 转换为 HEX（16进制）
        }
        ui->textBrowser_rx->insertPlainText(str); //将接收到的hex字符显示到接收区
        ui->textBrowser_rx->moveCursor(QTextCursor::End); //光标移动到最后
    }
    ui->label_rx_num->setText(QString::number(this->rx_num));// 更新接收字节数显示
}
void Widget::on_pushButton_tx_clicked()
{
    if(my_Serial.isOpen())// 确保串口已打开
    {
        ui->label_info0->setText("[correct] COM avaliable!");
        if(this->tx_mode==0) //字符串发送
        {
            this->tx_num += my_Serial.write(ui->textEdit_tx->toPlainText().toLatin1());// 发送字符串

        }
        else //hex发送
        {
            this->tx_num += my_Serial.write(QByteArray::fromHex(ui->textEdit_tx->toPlainText().toLatin1()));
        }
        ui->label_tx_num->setText(QString::number(this->tx_num)); // 更新发送字节数显示
        if(this->tx_num!=0) ui->label_info0->setText("[correct] transmit successfully!");
    }
    else
    {
        ui->label_info0->setText("[error] COM error!");// 提示转换成功
    }
}

