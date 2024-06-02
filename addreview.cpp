#include "addreview.h"
#include "ui_addreview.h"
#include <iostream> // Include for debug output

AddReview::AddReview(const QString& eateryName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddReview)
    , userHandler("UserInfo.json")
    , reviewHandler()
    , name_eateryName(eateryName)
{
    ui->setupUi(this);
    this->setFixedSize(438, 157); // Add Review's fixed size

    // Add debug output
    std::cout << "User handler initialized." << std::endl;

    // Verify if user information is loaded correctly
    if (!userHandler.load()) {
        std::cerr << "Failed to load user information." << std::endl;
    } else {
        std::string currentUser = userHandler.getCurrentUsername();
        std::cout << "Current user: " << currentUser << std::endl;
    }
}

AddReview::~AddReview()
{
    delete ui;
}

void AddReview::on_submitButton_clicked()
{
    // User input
    QString reviewMessage = ui->lineEdit->text();

    std::string currentUser = userHandler.getCurrentUsername();
    if (currentUser.empty()) {
        std::cerr << "Current user is empty." << std::endl;
        return;
    }

    std::string review = reviewMessage.toStdString(); // Convert QString to std::string because it doesn't accept it in Json Code

    // Load
    std::string carrienderiaName = name_eateryName.toStdString(); // Convert QString to std::string
    if (!reviewHandler.load(carrienderiaName))
    {
        std::cerr << "Failed to load Carrienderia: " << carrienderiaName << std::endl;
        return;
    }

    reviewHandler.receiveReview(currentUser, review); // Receive

    reviewHandler.save(); // Save the review

    this->close();
}
