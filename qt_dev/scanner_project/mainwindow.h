#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *main_window;
    QWidget *scan_window;
    QWidget *mail_window;

    //main_window->setStyle();
    QPushButton *button_scan;
    QPushButton *button_usb;
    QPushButton *button_mail;

    QLineEdit *email;
    QLineEdit *msg_subject;
    QLineEdit *msg_body;
    QString msg_attachement = "/home/sivanez/graduate_program/project/datasheet_ttl_rs232.pdf";

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void scanHandler();
    void usbHandler();
    void mailHandler();
    void sendHandler();
};

#endif // MAINWINDOW_H
