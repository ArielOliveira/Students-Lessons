#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setView(MainView* view)
{
    this->view = view;
}

MainWindow::~MainWindow()
{
    delete ui;
}
