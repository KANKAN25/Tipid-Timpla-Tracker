#include "editeatery.h"
#include "ui_editeatery.h"
#include "JSONCarrienderiaHandler.h"
#include "JSONCarrienderiaMenuHandler.h"

#include <QMessageBox>
#include <QSlider>

EditEatery::EditEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditEatery)
{
    ui->setupUi(this);
    this->setFixedSize(450, 444); // Edit Eatery's fixed size
    QObject::connect(ui->horizontalSlider_Index, &QSlider::valueChanged, this, [=](){
        ui->label_Index->setText(QString::number(ui->horizontalSlider_Index->value()));
    });
}

EditEatery::~EditEatery()
{
    delete ui;
}

void EditEatery::on_pushButton_updateEatery_clicked()
{
    JSONCarrienderiaHandler handler;

    std::string eateryName = ui->lineEdit_eateryName->text().toStdString();
    std::string status = ui->comboBox_Status->currentText().toStdString();
    std::string address = ui->lineEdit_Address->text().toStdString();
    std::string landmarks = ui->lineEdit_Landmarks->text().toStdString();
    std::string accomodations = ui->lineEdit_Accomodations->text().toStdString();

    handler.load(eateryName);
    if(!status.empty()){
        handler.receiveAttribute("Status", status);
    }
    if(!address.empty()){
        handler.receiveAttribute("Address", address);
    }
    if(!landmarks.empty()){
        handler.receiveAttribute("Landmarks", landmarks);
    }
    if(!accomodations.empty()){
        handler.receiveAttribute("Dining Accomodations", accomodations);
    }

    if (eateryName.empty() && address.empty() && landmarks.empty() && accomodations.empty()) {
        QMessageBox::warning(this, "Input Error", "All fields are empty. Nothing to edit.");
        return;
    }

    handler.editEatery(eateryName);
    handler.save();

    QMessageBox::information(this, "Success", "Eatery Edit Successful!");
}


void EditEatery::on_pushButton_updateMenu_clicked()
{
    JSONCarrienderiaMenuHandler menus;

    std::string eateryName = ui->lineEdit_eateryName->text().toStdString();
    if(eateryName.empty()){
        QMessageBox::warning(this, "No Eatery Name", "Please input eatery name!");
        return;
    }
    menus.load(eateryName);

    int index = ui->horizontalSlider_Index->value();
    std::string menuName = ui->lineEdit_MenuName->text().toStdString();
    double price = ui->lineEdit_Price->text().toDouble();
    std::string details = ui->lineEdit_Details->text().toStdString();
    std::string category = ui->comboBox_Category->currentText().toStdString();

    if (menuName.empty() || price <= 0 || details.empty()) {
        QMessageBox::warning(this, "Input Error", "All menu fields must be filled out and price must be positive.");
        return;
    }

    menus.editItem(category, menuName, details, price, index);
    menus.save();

    QMessageBox::information(this, "Success", "Menu Edit Successful!");

    ui->lineEdit_MenuName->clear();
    ui->lineEdit_Price->clear();
    ui->lineEdit_Details->clear();
}


void EditEatery::on_pushButton_done_clicked()
{
    this->hide();
}

