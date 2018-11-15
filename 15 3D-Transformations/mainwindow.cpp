#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // connect(ui->p1,SIGNAL(clicked(bool)),ui->widget,SLOT(rysuj()));

    connect(ui->TX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTX(int)));
    connect(ui->TY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTY(int)));
    connect(ui->TZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTZ(int)));

    connect(ui->RX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRX(int)));
    connect(ui->RY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRY(int)));
    connect(ui->RZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRZ(int)));

    connect(ui->SX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSX(int)));
    connect(ui->SY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSY(int)));
    connect(ui->SZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSZ(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
