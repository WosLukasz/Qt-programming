#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->b1,SIGNAL(clicked(bool)),ui->widget,SLOT(but1()));
    connect(ui->b2,SIGNAL(clicked(bool)),ui->widget,SLOT(but2()));
    connect(ui->b3,SIGNAL(clicked(bool)),ui->widget,SLOT(but3()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
