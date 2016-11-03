#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_window = new QWidget(this);

    // Create the button
    button_scan = new QPushButton("SCAN", this);
    button_usb = new QPushButton("USB", this);

    // Set font of the button
    button_scan->setFont(QFont("Comic Sans MS", 20));
    button_usb->setFont(QFont("Comic Sans MS", 20));

    // Connect
    QObject::connect(button_scan, SIGNAL(clicked()),this, SLOT(scanHandler()));
    QObject::connect(button_usb, SIGNAL(clicked()),this, SLOT(usbHandler()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button_scan, 1);
    layout->addWidget(button_usb, 1);

    my_window->setLayout(layout);
    this->setCentralWidget(my_window);
}

void MainWindow::scanHandler()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("SCAN");
    msgBox.exec();
}

void MainWindow::usbHandler()
{
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

MainWindow::~MainWindow()
{
    delete ui;
}
