#include "editeatery.h"
#include "ui_editeatery.h"

EditEatery::EditEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditEatery)
{
    ui->setupUi(this);
    this->setFixedSize(438, 401); // Edit Eatery's fixed size
}

EditEatery::~EditEatery()
{
    delete ui;
}
