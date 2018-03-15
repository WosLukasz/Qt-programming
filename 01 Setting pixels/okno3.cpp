#include "okno3.h"

#include <QPaintEvent>
#include <QPainter>
#include <windows.h>


Okno3::Okno3(QWidget *parent) : QWidget(parent)
{
    im = QImage(400,250,QImage::Format_RGB32);

    im.fill(Qt::white);

    int z,r;

    QWidget::setMouseTracking(true);

    for(int i=0;i<250;i++)
    {
       uchar *buf = im.scanLine(i);
        for(int j=0;j<400;j++)
        {
            z=rand()%2;

            if(z==0)
            {
                r=255;
            }else
            {
                r=0;
            }

               buf[4*j]=r;
               buf[4*j+1]=r;
               buf[4*j+2]=r;
        }
    }
}

void Okno3::wywolaj()
{

       zmieniaj();


}

void Okno3::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(0,0,width(),height(),Qt::black);

    p.drawImage(70,50,im);

    //!odswiezanie caly czas
    update();
    zmieniaj();



}

void Okno3::mouseMoveEvent(QMouseEvent *)
{
    zmieniaj();
}



void Okno3::zmieniaj()
{
    int z,r;

    for(int i=0;i<250;i++)
    {
       uchar *buf = im.scanLine(i);
        for(int j=0;j<400;j++)
        {
            z=rand()%2;

            if(z==0)
            {
                r=255;
            }else
            {
                r=0;
            }

               buf[4*j]=r;
               buf[4*j+1]=r;
               buf[4*j+2]=r;
        }
    }

    update();
    Sleep(100);

}
