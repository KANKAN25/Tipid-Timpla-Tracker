#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"

CreateAccount::CreateAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    this->setFixedSize(374,272); // Login window's fixed size
    login = new Login(this); // Instantiate the Login window
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_pushButton_New_clicked()
{
    login->show(); // Show the main window
    this->close(); // Close the eatery window
}

