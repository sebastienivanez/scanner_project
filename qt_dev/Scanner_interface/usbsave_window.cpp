#include "usbsave_window.h"
#include "ui_usbsave_window.h"

usbsave_window::usbsave_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usbsave_window)
{
    ui->setupUi(this);
}

usbsave_window::~usbsave_window()
{
    delete ui;
}
