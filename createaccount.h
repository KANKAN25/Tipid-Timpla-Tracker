#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>

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

private slots:
    void on_pushButton_New_clicked();

private:
    Ui::CreateAccount *ui;
    Login *login;
};

#endif // CREATEACCOUNT_H
