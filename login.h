#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "JSONUserHandler.h"
#include "createaccount.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginRequest();

    void createAccount();

private slots:
    void on_pushButton_Login_clicked();

    void on_CreateButton_clicked();

private:
    Ui::Login *ui;
    //MainWindow *mainwindow;
};

#endif // LOGIN_H
