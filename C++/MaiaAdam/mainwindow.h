#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainview.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setView(MainView* view);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainView* view;
};

#endif // MAINWINDOW_H
