#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setCheckState(Qt::Checked); //init the checkBox
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

