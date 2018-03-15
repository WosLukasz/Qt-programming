#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->SliderX,SIGNAL(valueChanged(int)),ui->widget,SLOT(setX(int)));
    connect(ui->SliderY,SIGNAL(valueChanged(int)),ui->widget,SLOT(setY(int)));
    connect(ui->czysc,SIGNAL(clicked(bool)),ui->widget2,SLOT(czysc()));
    connect(ui->przy,SIGNAL(clicked(bool)),ui->widget3,SLOT(wywolaj()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
