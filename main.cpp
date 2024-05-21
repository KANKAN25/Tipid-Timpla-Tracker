#include "mainwindow.h"

#include <QApplication>
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
