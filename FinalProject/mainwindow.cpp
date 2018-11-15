#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->TX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTX(int)));
    connect(ui->TY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTY(int)));
    connect(ui->TZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeTZ(int)));

    connect(ui->RX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRX(int)));
    connect(ui->RY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRY(int)));
    connect(ui->RZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeRZ(int)));

    connect(ui->SX,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSX(int)));
    connect(ui->SY,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSY(int)));
    connect(ui->SZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSZ(int)));

    connect(ui->szkielet,SIGNAL(clicked(bool)),ui->widget,SLOT(if_szkielet(bool)));
    connect(ui->texturowanie,SIGNAL(clicked(bool)),ui->widget,SLOT(if_texturowanie(bool)));
    connect(ui->backface,SIGNAL(clicked(bool)),ui->widget,SLOT(if_backface(bool)));
    connect(ui->obr,SIGNAL(clicked(bool)),ui->widget,SLOT(if_obr(bool)));
    connect(ui->zBuff,SIGNAL(clicked(bool)),ui->widget,SLOT(if_z_buff(bool)));

    connect(ui->brakOsw,SIGNAL(clicked(bool)),ui->widget,SLOT(if_brakOsw(bool)));
    connect(ui->oswietlenie1,SIGNAL(clicked(bool)),ui->widget,SLOT(if_oswietlenie1(bool)));
    connect(ui->oswietlenie2,SIGNAL(clicked(bool)),ui->widget,SLOT(if_oswietlenie2(bool)));
    connect(ui->S1X,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeS1X(int)));
    connect(ui->S1Y,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeS1Y(int)));
    connect(ui->S1Z,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeS1Z(int)));


    connect(ui->szescian,SIGNAL(clicked(bool)),ui->widget,SLOT(change_to_1(bool)));
    connect(ui->pikachu,SIGNAL(clicked(bool)),ui->widget,SLOT(change_to_3(bool)));
    connect(ui->inny,SIGNAL(clicked(bool)),ui->widget,SLOT(change_to_4(bool)));
    connect(ui->inne,SIGNAL(clicked(bool)),ui->widget,SLOT(change_to_5(bool)));

    connect(ui->inneText,SIGNAL(textChanged(QString)),ui->widget,SLOT(change_text(QString)));



}

MainWindow::~MainWindow()
{
    delete ui;
}


