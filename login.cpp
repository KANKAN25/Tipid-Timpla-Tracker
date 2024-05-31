#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(374,272); // Login window's fixed size
    //mainwindow = nullptr;
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_Login_clicked()
{
    JSONUserHandler account("UserInfo.json");

    if (!account.load()) {
        QMessageBox::warning(this, "Error", "Unable to load user data.");
        return;
    }

    std::string username = ui->lineEdit_Username->text().toStdString();
    std::string password = ui->lineEdit_Password->text().toStdString();

    if (!account.findUser(username, password)) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
        return;
    }

    ui->lineEdit_Username->clear();
    ui->lineEdit_Password->clear();

    emit loginRequest();

}

void Login::on_CreateButton_clicked()
{
    emit createAccount();
}


