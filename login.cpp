#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(374,272); // Login window's fixed size
    mainwindow = nullptr;
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_Login_clicked()
{

    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();

    if (username == "user" && password == "password") {
        // If login is successful, accept dialog
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
