#include "widget.h"
#include "./ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->init_widget();// ��ʼ������
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_widget()
{
    on_pushButton_fresh_com_clicked();//��ʼ��ʱ�Զ�ˢ��һ��
    ui->pushButton_led->setStyleSheet("background-color:grey;");// ����ָʾ�Ƴ�ʼ״̬����ɫ��
    ui->comboBox_baud->setCurrentText("115200");
    ui->label_rx_num->setText(QString::number(this->rx_num));// ���½����ֽ�����ʾ
    ui->label_tx_num->setText(QString::number(this->tx_num)); // ���·����ֽ�����ʾ
}

void Widget::on_pushButton_fresh_com_clicked()
{
    ui->comboBox_com->clear(); //��ն˿�ѡ��
    ui->label_info0->setText("[correct] freshed the COM");
    foreach(const QSerialPortInfo &Info,QSerialPortInfo::availablePorts()) //��ȡ���õĶ˿�
    {
        ui->comboBox_com->addItem(Info.portName()); // ��Ӵ��ڵ�����ѡ��
    }
}

void Widget::on_pushButton_onoff_com_clicked()
{
    //ui->label_info0->setText("[");
    if(ui->pushButton_onoff_com->text()=="OPEN")
    {
        my_Serial.setPortName(ui->comboBox_com->currentText()); //���ö˿���
        my_Serial.setBaudRate(ui->comboBox_baud->currentText().toInt()); //���ò�����

        my_Serial.open(QIODevice::ReadWrite); //�򿪴��ڣ���дģʽ��
        if(my_Serial.isOpen())//������ڴ�
        {
            connect(&my_Serial,&QSerialPort::readyRead,this,&Widget::msgRecevied);//�󶨴��ڽ����ź�
            ui->pushButton_led->setStyleSheet("background-color:green;");//����ָʾ��
            ui->pushButton_onoff_com->setText("CLOSE");  // ��ť��ʾ��CLOSE��
            ui->label_info0->setText("[correct] Opened the port successfully!"); // ��ʾ�ɹ���
        }
        else
        {
            ui->label_info0->setText("[error] Opened the port failed!"); // ��ʾ��ʧ��
        }
    }
    else
    {
        my_Serial.close();// �رմ���
        if(!my_Serial.isOpen())//�������δ��
        {
            ui->pushButton_led->setStyleSheet("background-color:grey;");//����ָʾ��
            ui->pushButton_onoff_com->setText("OPEN"); // ��ť��ʾ��OPEN��
            ui->label_info0->setText("[correct] Closed the port successfully!"); // ��ʾ�ɹ��ر�
        }
        else
        {
            ui->label_info0->setText("[error] Closed the port failed!");// ��ʾ�ر�ʧ��
        }
    }
}

void Widget::on_pushButton_clear_rx_clicked()
{
    ui->textBrowser_rx->clear(); //��ս�����
    ui->label_info0->setText("[correct] Cleared the BUF(rx) successfully!");// ��ʾ��ճɹ�
    this->rx_num=0;// ������ռ���
    //ui->label_rx_num->setText(" "); //��ս����ֽ���
}


void Widget::on_pushButton_clear_tx_clicked()
{
    ui->textEdit_tx->clear(); //��շ�����
    ui->label_info0->setText("[correct] Cleared the BUF(tx) successfully!");// ��ʾ��ճɹ�
    this->tx_num=0; // ���㷢�ͼ���
    //ui->label_tx_num->setText(" "); //��շ����ֽ���
}

void Widget::on_pushButton_hex_rx_clicked()
{
    ui->label_rx->setText("RX [HEX]");
    ui->label_info0->setText("[correct] Toggled the HEX(rx_mode) successfully!");// ��ʾת���ɹ�
    this->rx_mode=1; //rx��hex��־λ
}


void Widget::on_pushButton_str_rx_clicked()
{
    ui->label_rx->setText("RX [STR]");
    ui->label_info0->setText("[correct] Toggled the STR(rx_mode) successfully!");// ��ʾת���ɹ�
    this->rx_mode=0; //rx��str��־λ
}


void Widget::on_pushButton_hex_tx_clicked()
{
    ui->label_tx->setText("TX [HEX]");
    ui->label_info0->setText("[correct] Toggled the HEX(tx_mode) successfully!");// ��ʾת���ɹ�
    this->rx_mode=1; //tx��hex��־λ
}


void Widget::on_pushButton_str_tx_clicked()
{
    ui->label_tx->setText("TX [STR]");
    ui->label_info0->setText("[correct] Toggled the STR(tx_mode) successfully!");// ��ʾת���ɹ�
    this->rx_mode=0; //tx��str��־λ
}


void Widget::msgRecevied()
{
    QByteArray buf = my_Serial.readAll(); // ��ȡ���ڻ���������
    this->rx_num += buf.size();// ͳ�ƽ��յ����ֽ���

    if(this->rx_mode==0) // �ַ���ģʽ����
    {
        ui->textBrowser_rx->insertPlainText(tr(buf)); //�����յ���string�ַ���ʾ��������(tr���Խ�����ת����QString)
    }
    else// HEX ģʽ����
    {
        QString str;
        for(int i=0;i<buf.size();i++)
        {
            str+= QString("%1").arg(buf[i]&0xff,2,16,QLatin1Char('0'));// ת��Ϊ HEX��16���ƣ�
        }
        ui->textBrowser_rx->insertPlainText(str); //�����յ���hex�ַ���ʾ��������
        ui->textBrowser_rx->moveCursor(QTextCursor::End); //����ƶ������
    }
    ui->label_rx_num->setText(QString::number(this->rx_num));// ���½����ֽ�����ʾ
}
void Widget::on_pushButton_tx_clicked()
{
    if(my_Serial.isOpen())// ȷ�������Ѵ�
    {
        ui->label_info0->setText("[correct] COM avaliable!");
        if(this->tx_mode==0) //�ַ�������
        {
            this->tx_num += my_Serial.write(ui->textEdit_tx->toPlainText().toLatin1());// �����ַ���

        }
        else //hex����
        {
            this->tx_num += my_Serial.write(QByteArray::fromHex(ui->textEdit_tx->toPlainText().toLatin1()));
        }
        ui->label_tx_num->setText(QString::number(this->tx_num)); // ���·����ֽ�����ʾ
        if(this->tx_num!=0) ui->label_info0->setText("[correct] transmit successfully!");
    }
    else
    {
        ui->label_info0->setText("[error] COM error!");// ��ʾת���ɹ�
    }
}

