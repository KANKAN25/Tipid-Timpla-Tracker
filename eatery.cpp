#include "eatery.h"
#include "ui_eatery.h"
#include "mainwindow.h"
#include "reviews.h"
#include "editeatery.h"

// Correct the constructor definition to match the declaration
Eatery::Eatery(MainWindow *mainWindow, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Eatery)
    , mainWindow(mainWindow) // Initialize the mainWindow pointer
{
    ui->setupUi(this);
    this->setFixedSize(761, 461); // Main window's fixed size
}

Eatery::~Eatery()
{
    delete ui;
}

void Eatery::on_back_clicked()
{
    mainWindow->show(); // Show the main window
    this->close(); // Close the eatery window
}

void Eatery::on_pushButton_Reviews_clicked()
{
    Reviews *reviews = new Reviews(this); // Declaration
    reviews->show(); // Show the Reviews' window

    connect(reviews, &QObject::destroyed, reviews, &QObject::deleteLater); // deallocates when closed
}


void Eatery::on_pushButton_Edit_clicked()
{
    EditEatery *editeatery = new EditEatery(this); //Declaration
    this->close(); // Close the eatery window
    editeatery->show(); // Show the edit eatery window

    connect(editeatery, &QObject::destroyed, editeatery, &QObject::deleteLater); // deallocates when closed
}
