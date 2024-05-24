#ifndef EATERY_H
#define EATERY_H

#include <QDialog>

// Forward declaration of the MainWindow class
class MainWindow;

namespace Ui {
class Eatery;
}

class Eatery : public QDialog
{
    Q_OBJECT

public:
    explicit Eatery(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~Eatery();

private slots:
    void on_back_clicked();

private:
    Ui::Eatery *ui;
    MainWindow *mainWindow; // Pointer to MainWindow
};

#endif // EATERY_H
