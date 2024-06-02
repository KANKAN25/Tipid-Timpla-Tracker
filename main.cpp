#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "json.hpp"
#include "createaccount.h"
#include "JSONFileInitializer.h"
#include <fstream>
#include <iostream>
#include <qstring.h>
#include <QDir>
#include "addeatery.h"


using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Login loginDialog;
    MainWindow mainWindow;
    CreateAccount createnewaccount;
    //AddEatery addeatery;

    // Initializers for both files to be used if absent
    JSONFileInitializer inituserlist("UserInfo.json");
    if (!inituserlist.initialize()) {
        return EXIT_FAILURE;
    }

    JSONFileInitializer initcarrienderialist("CarriendariaList.json");
    if (!initcarrienderialist.initialize()) {
        return EXIT_FAILURE;
    }

    loginDialog.show();  // Show the login dialog initially

    // Connect the main window's loggedOut signal to the login dialog's show slot
    QObject::connect(&mainWindow, &MainWindow::loggedOut, [&mainWindow, &loginDialog]() {
        mainWindow.hide();
        loginDialog.show();
    });

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

// Usage Guide ofr Handler and Menu Handler
/*
        JSONCarrienderiaHandler handler;
        JSONCarrienderiaMenuHandler menus;

    // Example usage of adding a carrienderia
        no loading means we are adding a new carrienderia, blank slate
        handler.receiveAttribute("Name", "Grand Hospitality");
        handler.receiveAttribute("Average Rating", 4);
        handler.save();

    // Example usage of editing a carrienderia
        handler.load("Grand Hospitality");     // the third carrienderia
        handler.receiveAttribute("Name", "Grand Hospitality 2");
        handler.receiveAttribute("Average Rating", 5);
        handler.editEatery("Grand Hospitality");
        handler.save();

    // Example usage of using Menu Handling to add to existing carrienderia menu
        menus.Menuload("CarriendariaList.json", 2); // the third carrienderia
        menus.addItem("Drinks", "CokaCola", "Local Style", 30);
        menus.Menusave("CarriendariaList.json");

    // Example usage of using Menu Handling to edit existing carrienderia menu
        menus.Menuload("CarriendariaList.json", 2);
        menus.editItem("Drinks", "CokaCola", "Local Style Premium", 40, 0); // 0 means the first item in the drinks category
        menus.Menusave("CarriendariaList.json");
*/
