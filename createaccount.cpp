#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include <QMessageBox>

CreateAccount::CreateAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    this->setFixedSize(374,272); // Window's fixed size
    login = new Login(this); // Instantiate the Login window
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_pushButton_New_clicked()
{
    login->show(); // Show the main window
    this->close(); // Close the login window
}


void CreateAccount::on_pushButton_Login_okay_clicked()
{
    JSONUserHandler account("UserInfo.json");

    if (!account.load()) {
        QMessageBox::warning(this, "Error", "Unable to load user data.");
        return;
    }

    std::string username = ui->lineEdit_Username->text().toStdString();
    std::string password = ui->lineEdit_Password->text().toStdString();

    if (account.findUsername(username)) {
        QMessageBox::information(this, "Create New Account", "Username exists.");
        return;
    }

    if (!account.addUser(username, password)) {
        QMessageBox::warning(this, "Error", "Failed to add user.");
        return;
    }

    if (!account.save()) {
        QMessageBox::warning(this, "Error", "Unable to save user data.");
        return;
    }

    this->hide();
    login->show();
}

