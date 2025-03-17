#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCore/QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // 调用父类 QMainWindow 的构造函数
    , ui(new Ui::MainWindow)  // 动态分配 UI 资源
{
    ui->setupUi(this);  // 关联 UI 组件
    this->Init_MinWindow();  // 调用自定义初始化函数
}


MainWindow::~MainWindow()
{
    delete ui;  // 释放 UI 资源，防止内存泄漏
}


void MainWindow::on_pushButton_clicked()
{
    QPixmap pixmap(":/img/1.png");  // 从资源文件加载图片
    this->ui->label->setPixmap(pixmap);  // 在 `label` 控件上显示图片
    this->ui->label->setScaledContents(true); // 启用自动缩放，适应 `label` 大小
}



void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)  // 如果按钮被选中
    {
        this->ui->radioButton->setText("true");  // 设置文本为 "true"
    }
    else
    {
        this->ui->radioButton->setText("false");  // 设置文本为 "false"
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    switch(arg1)  // 根据复选框状态切换
    {
    case Qt::Checked:
        this->ui->checkBox->setText("Checked");  // 选中状态
        break;
    case Qt::Unchecked:
        this->ui->checkBox->setText("Unchecked");  // 未选中状态
        break;
    case Qt::PartiallyChecked:
        this->ui->checkBox->setText("PartiallyChecked");  // 部分选中状态
        break;
    default:
        break;
    }
}



void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    // 获取按钮对应的标准按钮类型
    QDialogButtonBox::StandardButton btnType = this->ui->buttonBox->standardButton(button);

    switch (btnType)
    {
    case QDialogButtonBox::Cancel:  // 取消按钮
        QMessageBox::information(this, "topic", "取消");  // 弹出提示框
        this->timer->stop();  // 停止 QTimer
        killTimer(timer_id1); // 终止 `startTimer()` 生成的定时器
        qDebug() << "timer1 stop";
        break;

    case QDialogButtonBox::Ok:  // 确定按钮
        if(QMessageBox::question(this, "提问", "是否开启定时器", QMessageBox::Yes|QMessageBox::Cancel))
        {
            this->timer->start(); // 启动 QTimer
            this->timer_id1 = startTimer(500); // 启动 `startTimer()` 以 500ms 间隔执行
            qDebug() << "timer1 start";
        }
        break;

    default:
        qDebug() << "timer_id:" << timer_id1;
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


// toolButton 点击事件处理函数：打开文件并读取内容
void MainWindow::on_toolButton_clicked()
{
    QFile file; // 创建 QFile 对象
    QString fileName = QFileDialog::getOpenFileName(this); // 弹出文件选择对话框，获取文件路径
    qDebug() << fileName << "\n"; // 输出选中文件的路径

    file.setFileName("./txt/01.txt"); // 设置要打开的文件路径（固定路径）

    if (!file.exists())// 检查文件是否存在，不存在则返回
    {
        qDebug() << "No File\n";
        return;
    }
    else// 文件存在，打印日志
    {
        qDebug() << "Yes File\n";
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text); // 以只读、文本模式打开文件
    QString str = file.readAll(); // 读取文件内容

    file.close(); // 关闭文件
    qDebug() << str; // 打印读取到的文件内容
}



//重载的定时器事件函数 （设置是500ms）
void MainWindow::timerEvent(QTimerEvent* event)
{
    if(event->timerId()==timer_id1) // 判断定时器 ID
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
// 自定义日志处理函数，替代 Qt 默认日志输出
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    (void)context;  // 忽略 context 参数，避免编译器警告

    QByteArray localMsg = msg.toLocal8Bit();  // 将日志消息转换为本地编码，确保支持中文
    QString strMsg("");  // 存储日志级别的字符串

    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug");  // 处理 qDebug() 类型日志
        break;
    case QtInfoMsg:
        strMsg = QString("Info");  // 处理 qInfo() 类型日志
        break;
    case QtWarningMsg:
        strMsg = QString("Warning");  // 处理 qWarning() 类型日志
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");  // 处理 qCritical() 类型日志
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");  // 处理 qFatal() 类型日志
        break;
    default:
        break;
    }

    // 获取当前时间并格式化为 "yyyy-MM-dd hh:mm:ss"
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 格式化日志消息：时间 + 日志级别 + 实际日志内容
    QString strMessage = QString("%1 %2 %3").arg(strDateTime, strMsg, localMsg);

    // pw 被用来访问 MainWindow 内的 debug_text（一个 QTextEdit 控件），将日志信息写入其中。
    // 将日志消息插入到 textEdit_2 文本框中
    pw->debug_text->insertPlainText(strMessage);
}


// 自定义初始化
void MainWindow::Init_MinWindow(void)
{
    debug_text = this->ui->textEdit_2;  // 绑定调试输出文本框
    this->timer_id1 = 0;  // 初始化定时器 ID
    this->timer = new QTimer(this);  // 创建 `QTimer`
    this->timer->setInterval(1000);  // 设置定时器间隔 1s
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));  // 连接定时器信号
    qInstallMessageHandler(myMessageOutput);  // 安装日志处理函数

    this->ui->checkBox->setCheckState(Qt::Checked); //设置默认状态
    this->ui->comboBox->addItem("COM1"); //添加串口选项
    this->ui->comboBox->addItem("COM2");
}


