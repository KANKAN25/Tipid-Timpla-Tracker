#include "addreview.h"
#include "ui_addreview.h"

AddReview::AddReview(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddReview)
{
    ui->setupUi(this);
    this->setFixedSize(438, 261); // Add Reviews's fixed size
}

AddReview::~AddReview()
{
    delete ui;
}
