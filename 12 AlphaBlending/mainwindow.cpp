#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dodawanie2,SIGNAL(clicked(bool)),ui->obraz,SLOT(mix_1()));
    connect(ui->odejmowanie2,SIGNAL(clicked(bool)),ui->obraz,SLOT(mix_2()));
    connect(ui->mnozenie2,SIGNAL(clicked(bool)),ui->obraz,SLOT(mix_3()));
    connect(ui->lighten2,SIGNAL(clicked(bool)),ui->obraz,SLOT(mix_4()));
    connect(ui->difference2,SIGNAL(clicked(bool)),ui->obraz,SLOT(mix_5()));
    connect(ui->alpha,SIGNAL(valueChanged(int)),ui->obraz, SLOT(alpha_change(int)));
    connect(ui->obraz1,SIGNAL(clicked(bool)),ui->obraz,SLOT(zmiana1()));
    connect(ui->obraz2,SIGNAL(clicked(bool)),ui->obraz,SLOT(zmiana2()));
    connect(ui->obraz3,SIGNAL(clicked(bool)),ui->obraz,SLOT(zmiana3()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

