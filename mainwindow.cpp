#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JSONCarrienderiaHandler.h"
#include <QPixmap>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , jsonHandler(new JSONCarrienderiaHandler())  // Initialize JSON handler
{
    ui->setupUi(this);
    this->setFixedSize(761, 461); // Main window's fixed size

    ui->horizontalSlider->setPageStep(1);
    ui->stackedWidget->setCurrentWidget(ui->page_1); // Ensure Page 1 is shown when logging out, so when logging back in it will show page 1

    QPixmap pix(":/images/academia king.jpg"); // Load the pixmap from the resource
    // Get the dimensions of the label
    int w = ui->label_4->width();
    int h = ui->label_4->height();
    ui->label_4->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatioByExpanding)); // Fill the whole space with the picture

    // Setup connections for navigating pages
    connect(ui->next_1, &QPushButton::clicked, this, &MainWindow::page2Widget);
    connect(ui->next_2, &QPushButton::clicked, this, &MainWindow::page1Widget);

    // Load eatery names and set the labels
    loadEateryNames();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete jsonHandler;  // Clean up JSON handler
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << value;
    ui->Rating->setText(QString::number(value));
}

void MainWindow::on_logout_clicked()
{
    emit loggedOut(); // Emit the loggedOut signal
}

void MainWindow::page1Widget()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}

void MainWindow::page2Widget()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_Place1_clicked()
{
    Eatery *eatery = new Eatery(this); // Declaration
    eatery->show(); // Show the Eatery window

    this->hide(); // Hide the Main window

    connect(eatery, &QObject::destroyed, eatery, &QObject::deleteLater); // deallocates when closed
}

void MainWindow::on_pushButton_Eatery_clicked()
{
    AddEatery *addEatery = new AddEatery(this); // Declaration
    addEatery->show(); // Show the Eatery window

    connect(addEatery, &QObject::destroyed, addEatery, &QObject::deleteLater); // deallocates when closed
}

void MainWindow::loadEateryNames()
{
    jsonHandler->load("CarriendariaList.json");  // Load the JSON file
    auto eateries = jsonHandler->getAllEateries();

    // Print Name
    for (int i = 9; i < 18; ++i) {
        QString labelName = QString("label_EateryName_%1").arg(i + 1);
        QLabel *label = findChild<QLabel *>(labelName);
        if (label && i < eateries.size()) {
            label->setText(QString::fromStdString(eateries[i]["Name"]));
        }
    }

    // Print Rating
    for (int i = 9; i < 18; ++i) {
        QString labelName = QString("label_Rating_%1").arg(i + 1);
        QLabel *label = findChild<QLabel *>(labelName);
        if (label) {
            label->setText(QString::fromStdString(eateries[i]["Average Rating"].dump()));
        }
    }
}

void MainWindow::on_pushButton_Confirm_clicked()
{
    int sliderValue = ui->horizontalSlider->value();
    int lowerBound = sliderValue - 1;
    int upperBound = sliderValue + 1;

    jsonHandler->load("CarriendariaList.json");  // Reload the JSON file
    auto eateries = jsonHandler->getAllEateries();

    int index = 9;
    for (const auto& eatery : eateries) {
        if (index >= 18) {
            break;
        }

        try {
            int rating = eatery["Average Rating"];
            if (rating >= lowerBound && rating <= upperBound) {
                QString nameLabel = QString("label_EateryName_%1").arg(index + 1);
                QString ratingLabel = QString("label_Rating_%1").arg(index + 1);
                QString priceLabel = QString("label_Price_%1").arg(index + 1);

                QLabel *nameLabelWidget = findChild<QLabel *>(nameLabel);
                QLabel *ratingLabelWidget = findChild<QLabel *>(ratingLabel);
                QLabel *priceLabelWidget = findChild<QLabel *>(priceLabel);

                if (nameLabelWidget && ratingLabelWidget && priceLabelWidget) { // Updated
                    nameLabelWidget->setText(QString::fromStdString(eatery["Name"]));
                    ratingLabelWidget->setText(QString::number(rating));
                    priceLabelWidget->clear(); // Updated
                }
                ++index;
            }
        } catch (const std::exception& e) {
            qDebug() << "Error parsing eatery: " << e.what();
        }
    }

    // Clear remaining labels if fewer than 9 eateries match
    for (; index < 18; ++index) {
        QString nameLabel = QString("label_EateryName_%1").arg(index + 1);
        QString ratingLabel = QString("label_Rating_%1").arg(index + 1);
        QString priceLabel = QString("label_Price_%1").arg(index + 1);

        QLabel *nameLabelWidget = findChild<QLabel *>(nameLabel);
        QLabel *ratingLabelWidget = findChild<QLabel *>(ratingLabel);
        QLabel *priceLabelWidget = findChild<QLabel *>(priceLabel);

        if (nameLabelWidget) {
            nameLabelWidget->clear();
        }
        if (ratingLabelWidget) {
            ratingLabelWidget->clear();
        }
        if (priceLabelWidget) {
            priceLabelWidget->clear();
        }
    }
}

