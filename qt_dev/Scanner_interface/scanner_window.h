#ifndef SCANNER_WINDOW_H
#define SCANNER_WINDOW_H

#include <QDialog>

namespace Ui {
class scanner_window;
}

class scanner_window : public QDialog
{
    Q_OBJECT

public:
    explicit scanner_window(QWidget *parent = 0);
    ~scanner_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::scanner_window *ui;
};

#endif // SCANNER_WINDOW_H
