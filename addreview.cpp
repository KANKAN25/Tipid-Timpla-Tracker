#include "addreview.h"
#include "ui_addreview.h"

AddReview::AddReview(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddReview)
{
    ui->setupUi(this);
}

AddReview::~AddReview()
{
    delete ui;
}
