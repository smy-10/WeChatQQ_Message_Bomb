#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread_.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUI();

    void send();

    void ui_enlabled(bool flag);
public slots:
    void send_slot();
    void done_slot();

private slots:
    void on_about_btn_clicked();

    void on_specification_btn_clicked();

    void on_setText_btn_clicked();

    void on_resetText_btn_clicked();

    void on_send_btn_clicked();

    void on_stop_btn_clicked();

private:
    Ui::MainWindow *ui;
    thread_* m_thread;
};

#endif // MAINWINDOW_H
