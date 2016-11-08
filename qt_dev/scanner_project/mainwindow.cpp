#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copyfile.h"
#include "sendmail.h"
#include "scanner.h"
#include "logger.h"
#include <QDesktopServices>
#include <QUrl>

#define LOG_PATH (char*)"log.txt"
#define PDF_PATH (char*)"aap.pdf"
#define PNM_PATH (char*)"aap.pnm"
#define USB_PATH (char*)"copy.pdf"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_window = new QWidget(this);
    //main_window->setStyleSheet("QWidget {background: grey}");

    // Create the buttons
    button_scan = new QPushButton("SCAN", this);
    button_usb = new QPushButton("USB", this);
    button_mail =  new QPushButton("MAIL", this);

    // Set font of the button
    button_scan->setFont(QFont("Comic Sans MS", 20));
    button_usb->setFont(QFont("Comic Sans MS", 20));
    button_mail->setFont(QFont("Comic Sans MS", 20));

    // Connect buttons
    QObject::connect(button_scan, SIGNAL(clicked()),this, SLOT(scanHandler()));
    QObject::connect(button_usb, SIGNAL(clicked()),this, SLOT(usbHandler()));
    QObject::connect(button_mail, SIGNAL(clicked()),this, SLOT(mailHandler()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button_scan, 1);
    layout->addWidget(button_usb, 1);
    layout->addWidget(button_mail, 1);

    main_window->setLayout(layout);
    this->setCentralWidget(main_window);
}

void MainWindow::scanHandler()
{
    char text[6][1024]={{"penguin"},{"duck"},{"donkey"},{"llama"},{"monkey"},{"duck"}};
    for (int i = 0; i<6; i++) {
        logging(text[i], LOG_PATH);
    }

    char *arg[10];
    arguments (arg);

    scanner(PNM_PATH, arg);
    create_pdf(PNM_PATH, PDF_PATH);

    QDesktopServices::openUrl(QUrl("file:///home/sivanez/graduate_program/project/scanner_project/qt_dev/build-scanner_project-Desktop_Qt_5_7_0_GCC_64bit-Debug/aap.pdf"));
}

void MainWindow::usbHandler()
{
    int ret;
    QString ret_copy;

    // Copies PDF file on the USB key
    ret = copyFile(PDF_PATH, USB_PATH);

    if (ret < 0 ) {
        ret_copy = "FAILED";
    } else {
        ret_copy = "DONE";
    }

    QMessageBox usb_box;
    usb_box.setText(ret_copy);
    usb_box.exec();
}

void MainWindow::mailHandler()
{
    // Create the button
    QPushButton *send_mail = new QPushButton("Send");
    send_mail->setFont(QFont("Comic Sans MS", 20));

    // Variables to store the email infos
    email = new QLineEdit;
    msg_subject = new QLineEdit;
    msg_body = new QLineEdit;

    // Update the mainwindow
    mail_window = new QWidget(this);
    QFormLayout *mail_layout = new QFormLayout;
    mail_layout->addRow("Email", email);
    mail_layout->addRow("Subject", msg_subject);
    mail_layout->addRow("Body", msg_body);
    mail_layout->addWidget(send_mail);
    mail_window->setLayout(mail_layout);
    this->setCentralWidget(mail_window);

    // Connect button
    QObject::connect(send_mail, SIGNAL(clicked()),this, SLOT(sendHandler()));
}

void MainWindow::sendHandler()
{
    int ret;
    QString ret_mail;

    // System call to send an email using mailx library
    ret = system(qPrintable("echo \"" + msg_body->text() + "\" | mailx -s \"" + msg_subject->text() + "\" -a " + msg_attachement + " " + email->text()));

    if (ret < 0 ) {
        ret_mail = "FAILED";
    } else {
        ret_mail = "DONE";
    }

    QMessageBox mail_box;
    mail_box.setText(ret_mail);
    mail_box.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
