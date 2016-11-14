#ifndef SCAN_OPTION_WIN_H
#define SCAN_OPTION_WIN_H

#include <QDialog>

namespace Ui {
class scan_option_win;
}

class scan_option_win : public QDialog
{
    Q_OBJECT

public:
    explicit scan_option_win(QWidget *parent = 0);
    ~scan_option_win();

private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_brightness_actionTriggered(int action);

    void on_label_linkActivated(const QString &link);

private:
    Ui::scan_option_win *ui;
};

#endif // SCAN_OPTION_WIN_H
