#include "addeatery.h"
#include "ui_addeatery.h"

AddEatery::AddEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEatery)
{
    ui->setupUi(this);
}

AddEatery::~AddEatery()
{
    delete ui;
}
