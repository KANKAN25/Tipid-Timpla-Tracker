#include "addreview.h"
#include "ui_addreview.h"

AddReview::AddReview(const QString& eateryName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddReview)
    , userHandler("UserInfo.json")
    , reviewHandler()
    , name_eateryName(eateryName)
{
    ui->setupUi(this);
    this->setFixedSize(438, 157); // Add Review's fixed size
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
    std::string review = reviewMessage.toStdString(); // Convert QString to std::string because it doesn't accept it in Json Code

    // Load
    std::string carrienderiaName = name_eateryName.toStdString(); // Convert QString to std::string
    if (!reviewHandler.load(carrienderiaName))
    {
        std::cerr << "Failed to load Carrienderia: " << carrienderiaName << std::endl;
        return;
    }

    reviewHandler.receiveReview(currentUser, review); // Receive

    reviewHandler.save(); // Save the review to

    this->close();
}
