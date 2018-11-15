#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->sx,SIGNAL(valueChanged(int)),ui->widget,SLOT(sxchange(int)));
    connect(ui->sy,SIGNAL(valueChanged(int)),ui->widget,SLOT(sychange(int)));
    connect(ui->tx,SIGNAL(valueChanged(int)),ui->widget,SLOT(txchange(int)));
    connect(ui->ty,SIGNAL(valueChanged(int)),ui->widget,SLOT(tychange(int)));
    connect(ui->rr,SIGNAL(valueChanged(int)),ui->widget,SLOT(rrchange(int)));








   /*
    connect(ui->er,SIGNAL(clicked(bool)),ui->widget,SLOT(erozja()));
    connect(ui->p2,SIGNAL(clicked(bool)),ui->widget,SLOT(wypelniaj()));
    connect(ui->ot,SIGNAL(clicked(bool)),ui->widget,SLOT(otwarcie()));
    connect(ui->zm,SIGNAL(clicked(bool)),ui->widget,SLOT(zamkniecie()));
*/


}

MainWindow::~MainWindow()
{
    delete ui;
}
