#include "startup_window.h"
#include "ui_startup_window.h"
#include "scanner_window.h"
#include "usbsave_window.h"
#include "mail_window.h"
Startup_window::Startup_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Startup_window)
{
    ui->setupUi(this);
}

Startup_window::~Startup_window()
{
    delete ui;
}

void Startup_window::on_pushButton_clicked()
{
    scanner_window swin;
    swin.setModal(true);
    //swin.showFullScreen();
    swin.exec();


}

void Startup_window::on_pushButton_2_clicked()
{
    usbsave_window uwin;
    uwin.setModal(true);
    uwin.exec();
}

void Startup_window::on_pushButton_3_clicked()
{
    mail_window mwin;
    mwin.setModal(true);
    mwin.exec();
}
