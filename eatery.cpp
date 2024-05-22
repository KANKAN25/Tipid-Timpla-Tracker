#include "eatery.h"
#include "ui_eatery.h"

Eatery::Eatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Eatery)
{
    ui->setupUi(this);
    this->setFixedSize(761, 461); // Main window's fixed size


}

Eatery::~Eatery()
{
    delete ui;
}
