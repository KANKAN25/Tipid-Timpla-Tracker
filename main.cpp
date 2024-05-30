#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "json.hpp"
#include "createaccount.h"
#include "JSONFileInitializer.h"
#include "JSONUserHandler.h"
#include <fstream>
#include <iostream>
#include <qstring.h>
#include <QDir>


using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Login loginDialog;
    MainWindow mainWindow;

    // Initializers for both files to be used if absent
    JSONFileInitializer inituserlist("UserInfo.json");
    if (!inituserlist.initialize()) {
        return EXIT_FAILURE;
    }

    JSONFileInitializer initcarrienderialist("CarrinderiaList.json");
    if (!initcarrienderialist.initialize()) {
        return EXIT_FAILURE;
    }

    loginDialog.show();  // Show the login dialog initially

    // Connect the main window's loggedOut signal to the login dialog's show slot
    QObject::connect(&mainWindow, &MainWindow::loggedOut, [&mainWindow, &loginDialog]() {
        mainWindow.hide();
        loginDialog.show();
    });

    // Connect the login dialog's accepted signal to the main window's show slot
    QObject::connect(&loginDialog, &Login::accepted, [&mainWindow, &loginDialog]() {
        loginDialog.hide();
        mainWindow.show();
    });




    return a.exec();
}
