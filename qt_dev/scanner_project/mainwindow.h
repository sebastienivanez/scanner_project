#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
//#include "copyfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *button_scan;
    QPushButton *button_usb;
    QPushButton *button_mail;
    QWidget *my_window;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void scanHandler();
    void usbHandler();
    void mailHandler();
};

#endif // MAINWINDOW_H
