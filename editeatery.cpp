#include "editeatery.h"
#include "ui_editeatery.h"

EditEatery::EditEatery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditEatery)
{
    ui->setupUi(this);
}

EditEatery::~EditEatery()
{
    delete ui;
}
