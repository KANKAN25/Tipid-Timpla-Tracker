#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include "JSONUserHandler.h"
#include "login.h"

class Login;

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

signals:
    void accountCreated();

    void cancelAccount();

private slots:
    void on_pushButton_Confirm_clicked();

    void on_CancelButton_clicked();

private:
    Ui::CreateAccount *ui;
    Login *login;
};

#endif // CREATEACCOUNT_H
