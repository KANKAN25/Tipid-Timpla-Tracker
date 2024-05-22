#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "login.h"

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
    emit loggedOut(); // Emit the loggedOut signal
    this->hide(); // Hide the Main window
}
