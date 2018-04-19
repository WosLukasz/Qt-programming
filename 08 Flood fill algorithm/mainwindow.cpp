#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->p1,SIGNAL(clicked(bool)),ui->widget,SLOT(rysuj()));
    connect(ui->p2,SIGNAL(clicked(bool)),ui->widget,SLOT(wypelniaj()));



}

MainWindow::~MainWindow()
{
    delete ui;
}
