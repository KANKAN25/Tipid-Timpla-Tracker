#include <QApplication>
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create and show the login dialog
    Login loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // If login is successful, create and show the main window
        MainWindow mainWindow;
        mainWindow.show();
        return a.exec();
    } else {
        // If login is not successful, exit the application
        return 0;
    }
}
