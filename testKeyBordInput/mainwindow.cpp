#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QMessageBox>
#include <QTimer>
#include "windows.h"
#include "winuser.h"
#pragma comment(lib,"Wmgr_c.lib")

/*
 *  windows  keybd_event API:
 *  https://docs.microsoft.com/en-us/previous-versions/windows/embedded/ms927178(v=msdn.10)
 *
 *
 *
 *
 * */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();

    m_thread = new thread_();
    connect(m_thread,&thread_::send_signal,this,&MainWindow::send_slot);
    connect(m_thread,&thread_::done_signal,this,&MainWindow::done_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this->setWindowTitle("QQ/微信 ..PC消息轰炸器 β-version");

    ui->setText_btn->setFocusPolicy(Qt::NoFocus);
    ui->send_btn->setFocusPolicy(Qt::NoFocus);
    ui->single_rb->setChecked(true);

    ui->interval_doubleSpinBox->setRange(1,9999999);
    ui->interval_doubleSpinBox2->setRange(1,9999999);
    ui->time_spinBox->setRange(1,9999999);

    ui->interval_doubleSpinBox->setValue(400);
    ui->interval_doubleSpinBox2->setValue(400);
    ui->time_spinBox->setValue(10);
}

void MainWindow::send()
{
    QTimer::singleShot(3000,this,[=]{
        keybd_event(0x11,0,0,0);//ctrl
        keybd_event(0x56,0,0,0);

        keybd_event(0x11,0,KEYEVENTF_KEYUP,0);    //松开ctrl
        //keybd_event(0X23,0,0,0);
        keybd_event(0x0d,0,0,0);
    });
}

void MainWindow::ui_enlabled(bool flag)
{
    ui->single_rb->setEnabled(flag);
    ui->multple_rb->setEnabled(flag);
    ui->while_rb->setEnabled(flag);
    ui->send_btn->setEnabled(flag);
    ui->interval_doubleSpinBox->setEnabled(flag);
    ui->interval_doubleSpinBox2->setEnabled(flag);
    ui->time_spinBox->setEnabled(flag);
}

void MainWindow::send_slot()
{
    keybd_event(0x11,0,0,0);//ctrl
    keybd_event(0x56,0,0,0);

    keybd_event(0x11,0,KEYEVENTF_KEYUP,0);    //松开ctrl
    //keybd_event(0X23,0,0,0);
    keybd_event(0x0d,0,0,0);
}

void MainWindow::done_slot()
{

    ui->send_btn->setText("开始轰炸");
    ui_enlabled(true);
}



void MainWindow::on_about_btn_clicked()
{

    QString html = "<a href=\"https://blog.csdn.net/weixin_42837024/\">博主博客";

    QMessageBox::information(NULL,"QQ/微信 ..PC消息轰炸器 β-version",html);
}

void MainWindow::on_specification_btn_clicked()
{
    QMessageBox::information(NULL,"QQ/微信 ..PC消息轰炸器 β-version",

                                     "1.在信息框中输入指定信息 - 设置\n"
                                     "2.设置好轰炸模式\n"
                                     "3.点击开始,3s之后会把信息框信息写入微信/QQ"
                                     "注意:点击开始以后一定要把光标焦点放入想输入的位置!\n");
}


void MainWindow::on_setText_btn_clicked()
{
    QClipboard* d= QApplication::clipboard();
    d->setText(ui->textEdit->toPlainText());

    ui->textEdit->setEnabled(false);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);

    QMessageBox::about(NULL,"","设置成功");
}

void MainWindow::on_resetText_btn_clicked()
{
    ui->textEdit->setEnabled(true);
    ui->textEdit->setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::on_send_btn_clicked()
{
    ui_enlabled(false);

    if(ui->single_rb->isChecked())
    {
        ui->send_btn->setText("轰炸中");
        send();
        ui->send_btn->setText("开始轰炸");
        ui_enlabled(true);
    }

    if(ui->multple_rb->isChecked())
    {
        QTimer::singleShot(3000,this,[=]{
            ui->send_btn->setText("轰炸中");
            m_thread->setMode(thread_::RUNMODE::forMode);
            m_thread->setTime(ui->time_spinBox->value());
            m_thread->setInterval(ui->interval_doubleSpinBox->value());
            m_thread->setRun(true);
            m_thread->start();
        });
    }

    if(ui->while_rb->isChecked())
    {
        QTimer::singleShot(3000,this,[=]{
            ui->send_btn->setText("轰炸中");
            m_thread->setMode(thread_::RUNMODE::whileMode);
            m_thread->setInterval(ui->interval_doubleSpinBox2->value());
            m_thread->setRun(true);
            m_thread->start();
        });
    }

}

void MainWindow::on_stop_btn_clicked()
{
    ui->send_btn->setText("开始轰炸");
    m_thread->setRun(false);
    ui_enlabled(true);
}
