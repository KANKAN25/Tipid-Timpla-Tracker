// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->verticalScrollBar, &QScrollBar::valueChanged, this, &MainWindow::on_verticalScrollBar_valueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_verticalScrollBar_valueChanged(int value)
{
    ui->filterarea->move(0, -value);
}





