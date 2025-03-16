#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCore/QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Init_MinWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPixmap pixmap(":/img/1.png");
    this->ui->label->setPixmap(pixmap);
    this->ui->label->setScaledContents(true); // 启用自动缩放
}


void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        this->ui->radioButton->setText("true");
    }
    else
    {
        this->ui->radioButton->setText("false");
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    switch(arg1)
    {
        case Qt::Checked:
        {
            this->ui->checkBox->setText("Checked");
            break;
        }
        case Qt::Unchecked:
        {
            this->ui->checkBox->setText("Unchecked");
            break;
        }
        case Qt::PartiallyChecked:
        {
            this->ui->checkBox->setText("PartiallyChecked");
            break;
        }
        default:break;
    }
}


void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    // 获取按钮对应的标准按钮类型
    QDialogButtonBox::StandardButton btnType = this->ui->buttonBox->standardButton(button);

    switch (btnType)
    {
    case QDialogButtonBox::Cancel:
        QMessageBox::information(this,"topic","取消");
        this->timer->stop();  //停止timer定时器
        killTimer(timer_id1); //杀死timer_id1定时器
        qDebug() << "timer1 stop";

        break;
    case QDialogButtonBox::Ok:
        if(QMessageBox::question(this,"提问","是否开启定时器",QMessageBox::Yes|QMessageBox::Cancel))
        {
            this->timer->start(); //启动定时器
            this->timer_id1=startTimer(500);//启动timer_id1定时器
            qDebug()<< "timer1 start";
        }
        break;
    default:
        qDebug() << "timer_id:"<<timer_id1; //每次定时器的id都会随机生成
        break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();

    //打印时间戳
    qDebug()<<dateTime;
    qDebug()<<dateTime.toSecsSinceEpoch(); //获取秒为单位的时间戳
    qDebug()<<dateTime.toMSecsSinceEpoch(); // 获取毫秒为单位的时间戳
    //qDebug()<<dateTime.toTime_t(); //获取时间戳（已失效）


    // 按下按钮改变界面颜色并在label框显示时间
    this->ui->label->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setStyleSheet("QMainWindow { background-color: lightgray; }");

    //输出lineEdit、comboBox和textEdit的当前内容
    qDebug()<<"line:"<<this->ui->lineEdit->text();
    qDebug()<<"combo:"<<this->ui->comboBox->currentText();
    qDebug()<<"text:"<<this->ui->textEdit->toPlainText();

    this->ui->lineEdit->setText("line readonly");
    // 清空comboBox的现有项，并添加新项"A"和"B
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("A");
    this->ui->comboBox->addItem("B");
    this->ui->textEdit->setText("text readonly");

    this->ui->comboBox->setEditable(false);
    this->ui->textEdit->setReadOnly(true);
    this->ui->lineEdit->setReadOnly(true);

}

void MainWindow::on_textEdit_2_textChanged()
{
    this->ui->textEdit_2->moveCursor(QTextCursor::End);
}


void MainWindow::on_toolButton_clicked()
{
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(this);
    qDebug()<<fileName<<"\n";
    file.setFileName("./txt/01.txt"); //左斜杠

    if(!file.exists())
    {
        qDebug()<<"No File\n";
        return;
    }
    else
    {
        qDebug()<<"Yes File\n";
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file.readAll();

    file.close();
    qDebug()<<str;

}

//重载的定时器事件函数 （设置是500ms）
void MainWindow::timerEvent(QTimerEvent* event)
{
    if(event->timerId()==timer_id1)
    {
        qDebug()<<"timerEvent 1"; //如果发现id是timer1，就执行
    }
}

//connect(this->timer, SIGNAL(timeout()),this,SLOT(timerTimeOut())); （设置是1000ms）
void MainWindow::timerTimeOut()
{
    qDebug()<<"timerout";
}

//qInstallMessageHandler
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    (void)context;
    QByteArray localMsg = msg.toLocal8Bit();
    QString strMsg("");
    switch(type)
    {
        case QtDebugMsg:
            strMsg = QString("Debug");
            break;
        case QtInfoMsg:
            strMsg = QString("Info");
            break;
        case QtWarningMsg:
            strMsg = QString("Warning");
            break;
        case QtCriticalMsg:
            strMsg = QString("Critical:");
            break;
        case QtFatalMsg:
            strMsg = QString("Fatal:");
            break;
        default:
            break;
    }
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString strMessage = QString("%1 %2 %3").arg(strDateTime,strMsg,localMsg);
    pw->debug_text->insertPlainText(strMessage);
}

// 自定义初始化
void MainWindow::Init_MinWindow(void)
{
    debug_text=this->ui->textEdit_2;

    this->timer_id1=0;
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(this->timer, SIGNAL(timeout()),this,SLOT(timerTimeOut())); //连接信号到槽函数(额外手动连接）
    qInstallMessageHandler(myMessageOutput); //

    this->ui->checkBox->setCheckState(Qt::Checked); //设置默认状态
    this->ui->comboBox->addItem("COM1"); //添加串口选项
    this->ui->comboBox->addItem("COM2");
}


