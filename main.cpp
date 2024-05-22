#include <QApplication>
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login loginDialog;
    MainWindow mainWindow;

    // Connect the login dialog's accepted signal to the main window's show slot
    QObject::connect(&loginDialog, &Login::accepted, [&mainWindow, &loginDialog]() {
        loginDialog.hide();
        mainWindow.show();
    });

    // Connect the main window's loggedOut signal to the login dialog's show slot
    QObject::connect(&mainWindow, &MainWindow::loggedOut, [&mainWindow, &loginDialog]() {
        mainWindow.hide();
        loginDialog.show();
    });

    loginDialog.show();  // Show the login dialog initially

    return a.exec();
}
