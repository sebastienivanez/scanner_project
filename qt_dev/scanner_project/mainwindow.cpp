#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copyfile.h"
#include "sendmail.h"
#include "scanner.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_window = new QWidget(this);

    // Create the button
    button_scan = new QPushButton("SCAN", this);
    button_usb = new QPushButton("USB", this);
    button_mail =  new QPushButton("MAIL", this);

    // Set font of the button
    button_scan->setFont(QFont("Comic Sans MS", 20));
    button_usb->setFont(QFont("Comic Sans MS", 20));
    button_mail->setFont(QFont("Comic Sans MS", 20));

    // Connect
    QObject::connect(button_scan, SIGNAL(clicked()),this, SLOT(scanHandler()));
    QObject::connect(button_usb, SIGNAL(clicked()),this, SLOT(usbHandler()));
    QObject::connect(button_mail, SIGNAL(clicked()),this, SLOT(mailHandler()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button_scan, 1);
    layout->addWidget(button_usb, 1);
    layout->addWidget(button_mail, 1);

    my_window->setLayout(layout);
    this->setCentralWidget(my_window);
}

void MainWindow::scanHandler()
{
    char* path = "/home/sivanez/test/log.txt";
    char text[6][1024]={{"penguin"},{"duck"},{"donkey"},{"llama"},{"monkey"},{"duck"}};
    for (int i = 0; i<6; i++)
    {
        int ret = logging(text[i],path);
    }
    scanner(path);
}

void MainWindow::usbHandler()
{
    copyFile("/home/sivanez/graduate_program/project/scanner_project/datasheet_ttl_rs232.pdf", "/home/sivanez/graduate_program/project/scanner_project/copy.pdf");

    /*QWidget fenetre;

    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *age = new QLineEdit;

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Votre nom", nom);
    layout->addRow("Votre prénom", prenom);
    layout->addRow("Votre âge", age);

    fenetre.setLayout(layout);
    fenetre.show();*/
}

void MainWindow::mailHandler()
{
    string email = "sebastien@ivanez.com";
    string msg_body = "Hello from Qt";
    string msg_subject = "Try2";
    string msg_attachement = "/home/sivanez/graduate_program/project/datasheet_ttl_rs232.pdf";

    sendMail(email, msg_subject, msg_body, msg_attachement);
}

MainWindow::~MainWindow()
{
    delete ui;
}
