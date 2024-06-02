#include "addeatery.h"
#include "ui_addeatery.h"
#include "JSONCarrienderiaHandler.h"
#include "JSONCarrienderiaMenuHandler.h"

//#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

AddEatery::AddEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEatery)
{
    ui->setupUi(this);
    this->setFixedSize(444, 430); // Add Eatery's fixed size
    //MainWindow *mainWindow = new MainWindow;
    //connect(ui->pushButton_addEatery, QPushButton::clicked, mainWindow, )
    ui->pushButton_addMenu->setEnabled(false);
}

AddEatery::~AddEatery()
{
    delete ui;
}

void AddEatery::on_pushButton_addEatery_clicked()
{
    JSONCarrienderiaHandler handler;

    std::string EateryName = ui->lineEdit_eateryName->text().toStdString();
    std::string status = ui->comboBox_status->currentText().toStdString();
    std::string address = ui->lineEdit_address->text().toStdString();
    std::string landmarks = ui->lineEdit_landmarks->text().toStdString();
    std::string accomodations = ui->lineEdit_accomodations->text().toStdString();

    if (EateryName.empty() || status.empty() || address.empty() || landmarks.empty() || accomodations.empty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    handler.receiveAttribute("Name", EateryName);
    handler.receiveAttribute("Status", status);
    handler.receiveAttribute("Address", address);
    handler.receiveAttribute("Landmarks", landmarks);
    handler.receiveAttribute("Dining Accomodations", accomodations);
    handler.addEatery();
    handler.save();

    ui->pushButton_addMenu->setEnabled(true);

    QMessageBox::information(this, "Success", "Eatery Successfully Added!");
}


void AddEatery::on_pushButton_addMenu_clicked()
{
    JSONCarrienderiaMenuHandler menus;

    std::string EateryName = ui->lineEdit_eateryName->text().toStdString();
    menus.load(EateryName);

    std::string MenuName = ui->lineEdit_menuName->text().toStdString();
    std::string category = ui->comboBox_category->currentText().toStdString();
    double price = ui->lineEdit_price->text().toDouble();
    std::string details = ui->lineEdit_details->text().toStdString();

    if (MenuName.empty() || category.empty() || price <= 0 || details.empty()) {
        QMessageBox::warning(this, "Input Error", "All menu fields must be filled out and price must be positive.");
        return;
    }

    menus.addItem(category, MenuName, details, price);
    menus.save();

    QMessageBox::information(this, "Success", "Menu Successfully Added!");

    ui->lineEdit_menuName->clear();
    ui->lineEdit_price->clear();
    ui->lineEdit_details->clear();
}


void AddEatery::on_pushButton_done_clicked()
{
    this->hide();
}

