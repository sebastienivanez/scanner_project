#ifndef USBSAVE_WINDOW_H
#define USBSAVE_WINDOW_H

#include <QDialog>

namespace Ui {
class usbsave_window;
}

class usbsave_window : public QDialog
{
    Q_OBJECT

public:
    explicit usbsave_window(QWidget *parent = 0);
    ~usbsave_window();

private:
    Ui::usbsave_window *ui;
};

#endif // USBSAVE_WINDOW_H
