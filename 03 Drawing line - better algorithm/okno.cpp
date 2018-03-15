#include "okno.h"
#include <QPaintEvent>
#include <QPainter>
#include <math.h>

Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(600,350,QImage::Format_RGB32);

    im.fill(Qt::black);

    x=0;
    y=0;

    //setMouseTracking(true);

}
void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);

   // p.fillRect(0,0,width(),height(),Qt::blue);

    p.drawImage(0,0,im);

}

void Okno::mousePressEvent(QMouseEvent *ev)
{
    x=ev->x();
    y=ev->y();
}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{
    im.fill(Qt::black);
    putPixel(x, y, ev->x(), ev->y(), 255, 255, 255);
    update();

}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{
    putPixel(x, y, ev->x(), ev->y(), 255, 255, 255);
}

void Okno::putPixel(float x1, float y1, float x2, float y2, int r, int g, int b)
{

    float a,N;
    int x,y;

    uchar *buf ;


    N = 2*sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    for(int i=0;i<N;i++)
    {

        a=(float)i/(N-1);
        x=(int)(x1+a*(x2-x1));
        y=(int)(y1+a*(y2-y1));

        if(x>=0 && x<600 && y>=0 && y<350)
        {
            buf= im.scanLine(y);

            buf[4*x]=b;
            buf[4*x+1]=g;
            buf[4*x+2]=r;

        }

    }
    update();


}

