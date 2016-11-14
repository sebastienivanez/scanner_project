#include "mail_window.h"
#include "ui_mail_window.h"

mail_window::mail_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mail_window)
{
    ui->setupUi(this);
}

mail_window::~mail_window()
{
    delete ui;
}
