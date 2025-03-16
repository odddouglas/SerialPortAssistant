#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Init_MinWindow(void);
    void timerEvent(QTimerEvent* event);

    int timer_id1;
    QTimer* timer;
    QTextEdit *debug_text;
private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_checkBox_stateChanged(int arg1);

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void timerTimeOut();

    void on_textEdit_2_textChanged();

private:
    Ui::MainWindow *ui;
};

extern MainWindow *pw; //使用定义的MainWindow对象指针
#endif // MAINWINDOW_H
