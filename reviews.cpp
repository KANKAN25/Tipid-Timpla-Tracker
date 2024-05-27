#include "reviews.h"
#include "ui_reviews.h"
#include "addreview.h"

Reviews::Reviews(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reviews)
{
    ui->setupUi(this);
    this->setFixedSize(347, 459); // Main window's fixed size

    // Assuming ui->stackedWidget is already defined in your UI file
    QWidget *page = new QWidget();
    QWidget *page2 = new QWidget();

    ui->stackedWidget->addWidget(page); // Index 0
    ui->stackedWidget->addWidget(page2); // Index 1

    // Setup connections for navigating pages
    connect(ui->next, &QPushButton::clicked, this, &Reviews::showPage2);
    connect(ui->back, &QPushButton::clicked, this, &Reviews::showPage);

    showPage(); // Ensure page1 is shown first
}

Reviews::~Reviews()
{
    delete ui;
}

void Reviews::showPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Reviews::showPage2()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Reviews::on_pushButton_AddReview_clicked()
{
    AddReview *addreview = new AddReview(this); // Declaration
    addreview->show(); // Show the Eatery window
}

