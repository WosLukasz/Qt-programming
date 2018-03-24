#include "okno.h"

#include <QMouseEvent>
#include <QPainter>
#include <math.h>


Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(600,350,QImage::Format_RGB32);

    im.fill(Qt::black);

    x=0;
    y=0;
    x9=0;
    y9=0;

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
    drawCircle2(x, y, ev->x(), ev->y(),0);
  //  x9=x();
   // y9=y();
    update();
}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{
    drawCircle2(x, y, ev->x(), ev->y(),0);
    x9=ev->x();
    y9=ev->y();
}

void Okno::obsl(int p)
{
    im.fill(Qt::black);
    drawCircle2( x,  y,  x9,  y9, p);
    update();

    qDebug("%d",p);
}


void Okno::drawCircle(float x1, float y1, float x2, float y2)
{

    float rkw = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    float r = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    int yy,xx;


    for(yy=0;yy<=r/sqrt(2);yy++)
    {
        xx=sqrt(rkw-yy*yy);

        putPixel(xx+x1,yy+y1,255,255,255);
        putPixel(-xx+x1,-yy+y1,255,255,255);
        putPixel(-xx+x1,yy+y1,255,255,255);
        putPixel(xx+x1,-yy+y1,255,255,255);
        putPixel(yy+x1,xx+y1,255,255,255);
        putPixel(-yy+x1,-xx+y1,255,255,255);
        putPixel(-yy+x1,xx+y1,255,255,255);
        putPixel(yy+x1,-xx+y1,255,255,255);

    }

}

void Okno::drawCircle2(int x1, int y1, int x2, int y2,int al)
{

    float r1 = abs((x2-x1)/2);
    float r2 = abs((y2-y1)/2);
    int x0 = (x1+x2)/2;
    int y0 = (y1+y2)/2;

    int N=64;

    int xx,yy,xxx,yyy;

    int tx=r1;
    int ty=0;

    float beta=float((float)al*M_PI)/180.0;

    tx=tx*cos(beta)-ty*sin(beta);
    ty=r1*sin(beta)+ty*(cos(beta));


    for(int i=1;i<=N;i++)
    {
        float alpha = ((float)i/N)*2 * M_PI;

        xx = r1*cos(alpha);
        yy = r2*sin(alpha);

        xxx=xx*cos(beta)-yy*sin(beta);
        yyy=xx*sin(beta)+yy*(cos(beta));

        drawLine(xxx+x0, yyy+y0, tx+x0, ty+y0, 255,255,255);

        tx=xxx;
        ty=yyy;

    }


}


void Okno::drawWheel(float x1, float y1, float x2, float y2)
{

    float rkw = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    float r = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    int yy,xx;

    uchar *buf;

    for(yy=0;yy<=r;yy++)
    {

        xx=sqrt(rkw-yy*yy);

        for(int i=0;i<2*xx;i++)
        {
            putPixel(x1-xx+i,y1+yy,255,255,255);
            putPixel(x1-xx+i,y1-yy,255,255,255);
        }

    }
}

void Okno::drawLine(float x1, float y1, float x2, float y2, int r, int g, int b)
{


        float a,N;
        int x,y;

        uchar *buf ;




        if(abs(x2-x1) >=abs(y2-y1))
        {

            if(x1<x2)
            {


                for(x=x1;x<=x2;x++)
                {

                        y=(y2-y1)*(x-x1)/(x2-x1)+y1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(x=x2;x<=x1;x++)
                {

                        y=(y1-y2)*(x-x2)/(x1-x2)+y2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }


        }else
        {
            if(y1<y2)
            {


                for(y=y1;y<=y2;y++)
                {

                        x=(x2-x1)*(y-y1)/(y2-y1)+x1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(y=y2;y<=y1;y++)
                {

                        x=(x1-x2)*(y-y2)/(y1-y2)+x2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }

}
}
void Okno::putPixel(int x, int y, int r, int g, int b)
{

    uchar *buf;


        if(x>=0 && x<im.width() && y>=0 && y<im.height())
        {
            buf= im.scanLine(y);

            buf[4*x]=b;
            buf[4*x+1]=g;
            buf[4*x+2]=r;

        }


    update();


}
