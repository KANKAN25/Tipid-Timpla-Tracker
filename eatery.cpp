#include "eatery.h"
#include "ui_eatery.h"
#include "mainwindow.h"
#include "reviews.h"
#include "editeatery.h"
#include "JSONCarrienderiaHandler.h"
#include "JSONCarrienderiaMenuHandler.h"

#include <QMessageBox>

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
    QString eateryName = ui->Filters->text(); // Get the text of the "Filters"

    Reviews *reviews = new Reviews(eateryName, this); // Declaration
    reviews->show(); // Show the Reviews window

    connect(reviews, &QObject::destroyed, reviews, &QObject::deleteLater); // deallocates when closed
}


void Eatery::on_pushButton_Edit_clicked()
{
    EditEatery *editeatery = new EditEatery(this); //Declaration
    editeatery->show(); // Show the edit eatery window

    connect(editeatery, &QObject::destroyed, editeatery, &QObject::deleteLater); // deallocates when closed
}

// Function to extract item names from JSON data
std::vector<std::string> extractItemNames(const json& jsonData, const std::string& targetCategory) {
    std::vector<std::string> itemNames;
    for (const auto& offering : jsonData["Menu Offerings"]) {
        if (offering["Category"] == targetCategory) {
            for (const auto& item : offering["Items"]) {
                itemNames.push_back(item["Name"]);
            }
            break;
        }
    }
    return itemNames;
}

void Eatery::on_pushButton_refresh_clicked()
{
    JSONCarrienderiaMenuHandler menus;

    std::string eateryName = ui->Filters->text().toStdString();
    if(eateryName.empty()){
        QMessageBox::warning(this, "No Eatery Name", "Please input eatery name!");
        return;
    }
    menus.load(eateryName);

    // Extract item names for Meals and Drinks
    std::vector<std::string> mealNames = extractItemNames(menus.carrienderia, "Meals");
    std::vector<std::string> drinkNames = extractItemNames(menus.carrienderia, "Drinks");


    // Set row count to the maximum of mealNames and drinkNames sizes
    int rowCount = std::max(mealNames.size(), drinkNames.size());
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(2); // Two columns: one for Meals, one for Drinks

    // Populate the table with meal and drink names
    for (int i = 0; i < mealNames.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(mealNames[i])));
    }
    for (int i = 0; i < drinkNames.size(); ++i) {
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(drinkNames[i])));
    }

}

