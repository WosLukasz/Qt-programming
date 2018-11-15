#include "okno.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <vector>

okno::okno(QWidget *parent) : QWidget(parent)
{
    im=QImage(800,550,QImage::Format_RGB32);
    im.fill(Qt::black);
    im00=im;
    im0=im;
    im1=QImage("01.jpg",Q_NULLPTR);
    im2=QImage("02.jpg",Q_NULLPTR);
    im3=QImage("03.jpg",Q_NULLPTR);

    im4=im;

    Warstwa one;
    one.id=1;
    one.mix=1;
    one.al=0;
    warstwy.push_back(one);
    one.id=2;
    one.mix=1;
    one.al=0;
    warstwy.push_back(one);
    one.id=3;
    one.mix=1;
    one.al=0;
    warstwy.push_back(one);
    k=3;

}
void okno::paintEvent(QPaintEvent *)
{

    QPainter p(this);

    p.drawImage(0,0,im);
}

void okno:: zmiana1(){
    k=1;
    rysuj();

}
void okno:: zmiana2(){
    k=2;
    rysuj();
}
void okno:: zmiana3(){
    k=3;
    rysuj();
}
void okno::alpha_change(int a){
    warstwy[k-1].al=a;
    rysuj();
}
void okno:: mix_1(){
    warstwy[k-1].mix=1;
    rysuj();
}
void okno::mix_2(){
    warstwy[k-1].mix=2;
    rysuj();
}
void okno::mix_3(){
    warstwy[k-1].mix=3;
    rysuj();
}
void okno::mix_4(){
    warstwy[k-1].mix=4;
    rysuj();
}
void okno::mix_5(){
    warstwy[k-1].mix=5;
    rysuj();
}

void okno:: dodawanie(QImage imm){

    im0=imm;
    im00=im;

    uchar *buf;
    uchar *buf2;
    for(int i=0;i<im.height();i++){
        buf = im.scanLine(i);
        buf2 = im0.scanLine(i);
        for(int j=0;j<im.width();j++){
            if(buf[4*j]+buf2[4*j]>255){
                buf[4*j]=255;
            }
            else{
                buf[4*j]=buf[4*j]+buf2[4*j];
            }
            if(buf[4*j+1]+buf2[4*j+1]>255){
                buf[4*j+1]=255;
            }
            else{
                buf[4*j+1]=(buf[4*j+1]+buf2[4*j+1]);
            }
            if(buf[4*j+2]+buf2[4*j+2]>255){
                buf[4*j+2]=255;
            }
            else{
                buf[4*j+2]=(buf[4*j+2]+buf2[4*j+2]);
            }


        }

    }
    update();
}




void okno:: odejmowanie(QImage imm){

    im0=imm;
    im00=im;


    uchar *buf;
    uchar *buf2;
    for(int i=0;i<im.height();i++){
        buf = im.scanLine(i);
        buf2 = im0.scanLine(i);
        for(int j=0;j<im.width();j++){
            if(buf[4*j]-buf2[4*j]<0){
                buf[4*j]=0;
            }
            else{
                buf[4*j]=buf[4*j]-buf2[4*j];
            }
            if(buf[4*j+1]-buf2[4*j+1]<0){
                buf[4*j+1]=0;
            }
            else{
                buf[4*j+1]=(buf[4*j+1]-buf2[4*j+1]);
            }
            if(buf[4*j+2]-buf2[4*j+2]<0){
                buf[4*j+2]=0;
            }
            else{
                buf[4*j+2]=(buf[4*j+2]-buf2[4*j+2]);
            }
        }
    }
    update();
    im0=im;
}

void okno:: mnozenie(QImage imm){

    im0=imm;
    im00=im;


    uchar *buf;
    uchar *buf2;
    for(int i=0;i<im.height();i++){
        buf = im.scanLine(i);
        buf2 = im0.scanLine(i);
        for(int j=0;j<im.width();j++){


            buf[4*j]=(int)buf[4*j]*buf2[4*j]/255;
            buf[4*j+1]=(int)buf[4*j+1]*buf2[4*j+2]/255;
            buf[4*j+2]=(int)buf[4*j+1]*buf2[4*j+2]/255;
        }
    }
    update();
    im0=im;
}

void okno:: lighten(QImage imm){

    im0=imm;
    im00=im;


    uchar *buf;
    uchar *buf2;
    for(int i=0;i<im.height();i++){
        buf = im.scanLine(i);
        buf2 = im0.scanLine(i);
        for(int j=0;j<im.width();j++){
            if(buf[4*j]<buf2[4*j]){
                buf[4*j]=buf2[4*j];
            }
            if(buf[4*j+1]<buf2[4*j+1]){
                buf[4*j+1]=buf2[4*j+1];
            }
            if(buf[4*j+2]<buf2[4*j+2]){
                buf[4*j+2]=buf2[4*j+2];
            }
        }
    }
    update();
    im0=im;
}

void okno:: difference(QImage imm){

    im0=imm;
    im00=im;


    uchar *buf;
    uchar *buf2;
    for(int i=0;i<im.height();i++){
        buf = im.scanLine(i);
        buf2 = im0.scanLine(i);
        for(int j=0;j<im.width();j++){
            buf[4*j]=abs(buf[4*j]-buf2[4*j]);
            buf[4*j+1]=abs(buf[4*j+1]-buf2[4*j+1]);
            buf[4*j+2]=abs(buf[4*j+2]-buf2[4*j+2]);
        }
    }
    update();
    im0=im;
}


void okno:: alphaupdate(int a){

    uchar *buf;
    uchar *buf2;
    uchar *buf3;
    for(int i=0;i<im.height();i++){
        buf = im00.scanLine(i);
        buf2 = im0.scanLine(i);
        buf3 = im.scanLine(i);
        for(int j=0;j<im.width();j++){
            buf3[4*j]=(int)(buf2[4*j]*(100-a)+a*buf[4*j])/100;
            buf3[4*j+1]=(int)(buf2[4*j+1]*(100-a)+a*buf[4*j+1])/100;
            buf3[4*j+2]=(int)(buf2[4*j+2]*(100-a)+a*buf[4*j+2])/100;
        }
    }
    update();

}

void okno::rysuj(){

    im.fill(Qt::black);
    for(int i=0;i<k;i++){
        int id=warstwy[i].id;
        int mix=warstwy[i].mix;
        int al=warstwy[i].al;
        if(id==1){
            im4=im1;
        }
        else if(id==2){
            im4=im2;
        }
        else if(id==3){
            im4=im3;
        }
        if(mix==1){
            dodawanie(im4);
        }
        else if(mix==2){
            odejmowanie(im4);
        }
        else if(mix==3){
            mnozenie(im4);
        }
        else if(mix==4){
            lighten(im4);
        }
        else if(mix==5){
            difference(im4);
        }
        alphaupdate(al);
    }

}
