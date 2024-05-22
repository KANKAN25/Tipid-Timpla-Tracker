#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "json.hpp"

using json = nlohmann::json;
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_horizontalSlider_valueChanged(int value);

    void on_logout_clicked();
//    void on_loadJsonButton_clicked();

private:
    Ui::MainWindow *ui;
    void loadJsonData();
};
#endif // MAINWINDOW_H
