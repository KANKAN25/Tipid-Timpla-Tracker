#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void loggedOut();  // Signal to be emitted when the user logs out

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_logout_clicked();

private:
    Ui::MainWindow *ui;
};

#endif
