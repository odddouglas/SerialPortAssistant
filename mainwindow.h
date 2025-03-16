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

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_checkBox_stateChanged(int arg1);

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
