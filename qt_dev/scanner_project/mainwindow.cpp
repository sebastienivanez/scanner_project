#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copyfile.h"
#include "sendmail.h"
#include "scanner.h"

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
    /*char* path = "/home/sivanez/test/log.txt";
    char text[6][1024]={{"penguin"},{"duck"},{"donkey"},{"llama"},{"monkey"},{"duck"}};
    for (int i = 0; i<6; i++)
    {
        logging(text[i],path);
    }
    scanner(path);

    mail_window = new QWidget(this);
*/

}

void MainWindow::usbHandler()
{
    copyFile("/home/sivanez/graduate_program/project/scanner_project/datasheet_ttl_rs232.pdf", "/home/sivanez/graduate_program/project/scanner_project/copy.pdf");
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
    system(qPrintable("echo \"" + msg_body->text() + "\" | mailx -s \"" + msg_subject->text() + "\" -a " + msg_attachement + " " + email->text()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
