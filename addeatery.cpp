#include "addeatery.h"
#include "ui_addeatery.h"

AddEatery::AddEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEatery)
{
    ui->setupUi(this);
    this->setFixedSize(438, 261); // Add Eatery's fixed size
}

AddEatery::~AddEatery()
{
    delete ui;
}
