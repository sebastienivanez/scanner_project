#include "scanner_window.h"
#include "ui_scanner_window.h"
#include "scan_option_win.h"

scanner_window::scanner_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scanner_window)
{
    ui->setupUi(this);
}

scanner_window::~scanner_window()
{
    delete ui;
}

void scanner_window::on_pushButton_clicked()
{
    scan_option_win sowin;
    sowin.setModal(true);
    sowin.exec();
}
