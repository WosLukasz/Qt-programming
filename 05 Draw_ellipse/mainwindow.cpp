#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->slider,SIGNAL(valueChanged(int)),ui->widget,SLOT(obsl(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
