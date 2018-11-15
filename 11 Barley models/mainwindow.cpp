#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->convert,SIGNAL(clicked(bool)),ui->widget,SLOT(convert()));

    connect(ui->H,SIGNAL(sliderMoved(int)),ui->widget,SLOT(changeH(int)));
    connect(ui->S,SIGNAL(sliderMoved(int)),ui->widget,SLOT(changeS(int)));
    connect(ui->V,SIGNAL(sliderMoved(int)),ui->widget,SLOT(changeV(int)));

    connect(ui->Rr,SIGNAL(textChanged(QString)),ui->widget,SLOT(rysujR(QString)));
    connect(ui->Gg,SIGNAL(textChanged(QString)),ui->widget,SLOT(rysujG(QString)));
    connect(ui->Bb,SIGNAL(textChanged(QString)),ui->widget,SLOT(rysujB(QString)));
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
