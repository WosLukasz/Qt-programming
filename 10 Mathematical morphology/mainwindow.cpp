#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->dy,SIGNAL(clicked(bool)),ui->widget,SLOT(dylatacja()));
    connect(ui->er,SIGNAL(clicked(bool)),ui->widget,SLOT(erozja()));
    connect(ui->p2,SIGNAL(clicked(bool)),ui->widget,SLOT(wypelniaj()));
    connect(ui->ot,SIGNAL(clicked(bool)),ui->widget,SLOT(otwarcie()));
    connect(ui->zm,SIGNAL(clicked(bool)),ui->widget,SLOT(zamkniecie()));



}

MainWindow::~MainWindow()
{
    delete ui;
}
