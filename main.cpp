#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "json.hpp"
#include "JSONFileInitializer.h"
#include "JSONUserHandler.h"
#include <fstream>
#include <iostream>
#include <qstring.h>
#include <QDir>
#include "createaccount.h"


using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Login loginDialog;
    MainWindow mainWindow;
    CreateAccount createnewaccount;

    // Initializers for both files to be used if absent
    JSONFileInitializer inituserlist("UserInfo.json");
    if (!inituserlist.initialize()) {
        return EXIT_FAILURE;
    }

    JSONFileInitializer initcarrienderialist("CarrinderiaList.json");
    if (!initcarrienderialist.initialize()) {
        return EXIT_FAILURE;
    }


    // Connect the login dialog's login request signal to the main window's show slot
    QObject::connect(&loginDialog, &Login::loginRequest, [&]() {
        loginDialog.hide();
        mainWindow.show();
    });

    // Connect the login dialog's create account signal to the main window's show slot
    QObject::connect(&loginDialog, &Login::createAccount, [&]() {
        loginDialog.hide();
        createnewaccount.show();
    });

    // Connect the main window's loggedOut signal to the login dialog's show slot
    QObject::connect(&mainWindow, &MainWindow::loggedOut, [&]() {
        mainWindow.hide();
        loginDialog.show();
    });

    // Connect the create account's account created signal to the login dialog's show slot
    QObject::connect(&createnewaccount, &CreateAccount::accountCreated, [&]() {
        createnewaccount.hide();
        loginDialog.show();
    });

    // Connect the create account's cancel account signal to the login dialog's show slot
    QObject::connect(&createnewaccount, &CreateAccount::cancelAccount, [&]() {
        createnewaccount.hide();
        loginDialog.show();
    });

    loginDialog.show();  // Show the login dialog initially

    return a.exec();
}
