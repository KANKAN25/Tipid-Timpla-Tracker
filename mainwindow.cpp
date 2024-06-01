#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(761, 461); // Main window's fixed size

    ui->horizontalSlider->setPageStep(1);

    QPixmap pix(":/images/academia king.jpg"); // Load the pixmap from the resource
    // Get the dimensions of the label
    int w = ui->label_4->width();
    int h = ui->label_4->height();
    ui->label_4->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatioByExpanding)); // Fill the whole space with the picture

    // Setup connections for navigating pages
    connect(ui->next_1, &QPushButton::clicked, this, &MainWindow::page2Widget);
    connect(ui->next_2, &QPushButton::clicked, this, &MainWindow::page1Widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << value;
    ui->Rating->setText(QString::number(value));
}

void MainWindow::on_logout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1); // Ensure Page 1 is shown when logging out, so when logging back in it will show page 1
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

