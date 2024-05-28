#include "login.h"
#include "ui_login.h"
#include "createaccount.h"
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

    accept();


    //if (username == "user" && password == "password") {
        // If login is successful, accept dialog
      //  ui->lineEdit_Username->clear(); // Clear the username field
      //  ui->lineEdit_Password->clear(); // Clear the password field
      //  accept();
    //} else {
      //  QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    //}
}

void Login::on_CreateButton_clicked()
{
    CreateAccount *createaccount = new CreateAccount(this); // Declaration
    createaccount->show(); // Show the CreateAccount window

    connect(createaccount, &CreateAccount::finished, this, [this, createaccount](){
        if (createaccount->result() == QDialog::Rejected) {
            ui->lineEdit_Username->clear(); // Clear the username field
            ui->lineEdit_Password->clear(); // Clear the password field
            this->show(); // Show the login window if the CreateAccount dialog was canceled
            delete createaccount; // Delete the CreateAccount instance if it was canceled
        }
    });

    this->hide(); // Hide the Login window
}


