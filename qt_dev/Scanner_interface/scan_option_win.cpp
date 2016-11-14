#include "scan_option_win.h"
#include "ui_scan_option_win.h"

scan_option_win::scan_option_win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scan_option_win)
{
    ui->setupUi(this);
}

scan_option_win::~scan_option_win()
{
    delete ui;
}

void scan_option_win::on_radioButton_clicked(bool checked)
{
    if (checked==true)
    {
        on_radioButton_2_clicked(false);

    }
}

void scan_option_win::on_radioButton_2_clicked(bool checked)
{
    if (checked == true)
    {
         on_radioButton_clicked(false);
    }
}


void scan_option_win::on_brightness_actionTriggered(int action)
{

}

void scan_option_win::on_label_linkActivated(const QString &link)
{

}
