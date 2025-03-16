#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCore/QDebug>
#include <QFile>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Init_MinWindow();
}
void MainWindow::Init_MinWindow(void)
{
    this->ui->checkBox->setCheckState(Qt::Checked); //设置默认状态
    this->ui->comboBox->addItem("COM1"); //添加串口选项
    this->ui->comboBox->addItem("COM2");
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
        qDebug() << "cancel\n";
        break;
    case QDialogButtonBox::Ok:
        qDebug() << "ok\n";
        break;
    default:
        qDebug() << "other button clicked\n";
        break;
    }
}



void MainWindow::on_pushButton_2_clicked()
{

    this->ui->label->setText("pushButton2");
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

