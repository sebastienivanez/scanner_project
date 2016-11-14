#ifndef MAIL_WINDOW_H
#define MAIL_WINDOW_H

#include <QDialog>

namespace Ui {
class mail_window;
}

class mail_window : public QDialog
{
    Q_OBJECT

public:
    explicit mail_window(QWidget *parent = 0);
    ~mail_window();

private:
    Ui::mail_window *ui;
};

#endif // MAIL_WINDOW_H
