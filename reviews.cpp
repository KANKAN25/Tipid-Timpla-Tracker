#include "reviews.h"
#include "ui_reviews.h"
#include "addreview.h"

Reviews::Reviews(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reviews)
{
    ui->setupUi(this);
    this->setFixedSize(347, 459); // Main window's fixed size

    QWidget *page = new QWidget();
    QWidget *page2 = new QWidget();

    // Index
    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->addWidget(page2);

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
    addreview->show(); // Show the Add Review window
}

