#include "createaccount.h"
#include "ui_createaccount.h"
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


void CreateAccount::on_pushButton_Confirm_clicked()
{
    JSONUserHandler account("UserInfo.json");

    if (!account.load()) {
        QMessageBox::warning(this, "Error", "Unable to load user data.");
        return;
    }

    std::string username = ui->lineEdit_Username->text().toStdString();
    std::string password = ui->lineEdit_Password->text().toStdString();

    if (username == "" && password == ""){
        QMessageBox::information(this, "Create New Account", "Please input valid username and password.");
        return;
    }

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

    emit accountCreated();

}


void CreateAccount::on_CancelButton_clicked()
{
    emit cancelAccount();
};

