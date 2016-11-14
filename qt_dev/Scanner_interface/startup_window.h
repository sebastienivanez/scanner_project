#ifndef STARTUP_WINDOW_H
#define STARTUP_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Startup_window;
}

class Startup_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Startup_window(QWidget *parent = 0);
    ~Startup_window();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Startup_window *ui;
};

#endif // STARTUP_WINDOW_H
