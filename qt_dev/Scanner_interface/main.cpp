#include "startup_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Startup_window w;
    w.show();

    return a.exec();
}
