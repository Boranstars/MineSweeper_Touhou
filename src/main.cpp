#include <QApplication>
#include "gui/include/mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.init();
    window.show();
    return QApplication::exec();
}