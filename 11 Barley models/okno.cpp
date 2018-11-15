#include "okno.h"

#include <QMouseEvent>
#include <QPainter>
#include <stack>
#include <vector>
#include <sstream>
#include <iostream>

Okno::Okno(QWidget *parent) : QWidget(parent)
{

    im2 = QImage(450,500,QImage::Format_RGB32);
    im=QImage("01.jpg");


        x=0;
        y=0;

        im2.fill(Qt::white);
}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPainter p1(this);


    p.drawImage(0,0,im);
    p1.drawImage(460,0,im2);
}

void Okno::mousePressEvent(QMouseEvent *ev)
{
   // Point z;

  //  z.x=ev->x();
   // z.y=ev->y();

    x=ev->x();
    y=ev->y();

  //  p.push_back(z);

  //  drawDot(z.x,z.y,255,255,255);
  //  update();

}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{

}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{
    drawLine(x,y,ev->x(),ev->y(),RR,GG,BB);

    update();
}

void Okno::convert()
{

    uchar *buf ;
    uchar *buf2 ;
    double r,g,b;
    HSV hsv;
    RGB rgb;

    for(int y=0;y<im.height();y++)
    {
            buf= im.scanLine(y);
            buf2= im2.scanLine(y);

            for(int x=0;x<im.width();x++)
            {
                b=buf[4*x];
                g=buf[4*x+1];
                r=buf[4*x+2];

                rgb.r=r;
                rgb.g=g;
                rgb.b=b;


                    hsv = converttoHSV(r,g,b);

                    hsv.h= (int)(360+hsv.h + przesunH)%360;

                    hsv.s+=przesunS;
                    if(hsv.s>1)
                    {
                        hsv.s=1;
                    }

                    if(hsv.s<0)
                    {
                        hsv.s=0;
                    }

                    hsv.v+=przesunV;

                    if(hsv.v>1)
                    {
                        hsv.v=1;
                    }

                    if(hsv.v<0)
                    {
                        hsv.v=0;
                    }


                    rgb= converttoRGB(hsv);



                buf2[4*x]=rgb.b;
                buf2[4*x+1]=rgb.g;
                buf2[4*x+2]=rgb.r;

            }
    }

    update();

}

void Okno::changeH(int x)
{

    std::cout<< x<<std::endl;

     przesunH =x;

    convert();


}

void Okno::changeS(int x)
{

    std::cout<< x<<std::endl;
    double ss;


        ss=((double)x)/100.0;


     przesunS =ss;

    convert();
}

void Okno::changeV(int x)
{

    std::cout<< x<<std::endl;
    double vv;


        vv=((double)x)/100.0;


     przesunV = vv;

    convert();
}

void Okno::rysujR(QString s)
{
    if(s!=NULL && s.length()!=0)
    {
        std::stringstream ss;
        ss << s.toStdString();
        ss >> RR;
    }


}

void Okno::rysujG(QString s)
{
    if(s!=NULL && s.length()!=0)
    {
        std::stringstream ss;
        ss << s.toStdString();
        ss >> GG;
    }
}

void Okno::rysujB(QString s)
{
    if(s!=NULL && s.length()!=0)
    {
        std::stringstream ss;
        ss << s.toStdString();
        ss >> BB;
    }
}

Okno::RGB Okno::converttoRGB(Okno::HSV hsv)
{
    RGB rgb;

    double c = hsv.v * hsv.s;
    double x = c*(1-abs(((2+(int)(hsv.h/60))%2)-1));

    double m = hsv.v - c;


    if(hsv.h>=0 && hsv.h<60)
    {
       rgb.r = c;
       rgb.g = x;
       rgb.b = 0;

    }else if(60<=hsv.h && hsv.h<120)
    {
        rgb.r = x;
        rgb.g = c;
        rgb.b = 0;
    }
    else if(120<=hsv.h && hsv.h<180)
    {
        rgb.r = 0;
        rgb.g = c;
        rgb.b = x;
    }
    else if(180<=hsv.h && hsv.h<240)
    {
        rgb.r = 0;
        rgb.g = x;
        rgb.b = c;
    }
    else if(240<=hsv.h && hsv.h<300)
    {
        rgb.r = x;
        rgb.g = 0;
        rgb.b = c;
    }
    else if(300<=hsv.h && hsv.h<360)
    {
        rgb.r = c;
        rgb.g = 0;
        rgb.b = x;
    }

    rgb.r=(rgb.r+m)*255;
    rgb.g=(rgb.g+m)*255;
    rgb.b=(rgb.b+m)*255;


    return rgb;
}


Okno::HSV Okno::converttoHSV(double r, double  g, double b)
{
    HSV out;

    r=r/255.0;
    g=g/255.0;
    b=b/255.0;

    double mi = r;
    double ma = r;

    if(g<mi)
    {
        mi=g;
    }

    if(b<mi)
    {
        mi=b;
    }

    if(g>ma)
    {
        ma=g;
    }

    if(b>ma)
    {
        ma=b;
    }


    double delta = ma-mi;

    if(delta==0)
    {
        out.h=0;
    }else if(ma==r)
    {
        out.h=(int)(360+60*(((g-b)/delta)))%360;
    }else if(ma==g)
    {
        out.h=60*(((b-r)/delta)+2);
    }else if(ma==b)
    {
        out.h=60*(((r-g)/delta)+4);
    }

    if(ma==0)
    {
        out.s=0;

    }else
    {
        out.s=delta/ma;
    }

    out.v=ma;


    return out;

}



void Okno::drawDot2(int x, int y,int r, int g, int b)
{
    if(x>=0 && x<im2.width() && y>=0 && y<im2.height())
    {
         uchar *buf= im2.scanLine(y);

        buf[4*x]=b;
        buf[4*x+1]=g;
        buf[4*x+2]=r;

    }
}



void Okno::drawDot(int x, int y, int r, int g, int b)
{
    if(x>=0 && x<im.width() && y>=0 && y<im.height())
    {
         uchar *buf= im.scanLine(y);

        buf[4*x]=b;
        buf[4*x+1]=g;
        buf[4*x+2]=r;

    }
}

void Okno::scan_line(std::vector<Okno::Point> p, int r, int g, int bb)
{
    float y_min=p[0].y;
    float y_max=p[0].y;


    for(int i=0;i<p.size();i++)
    {
        if(p[i].y<y_min)
        {
            y_min=p[i].y;
        }

        if(p[i].y>y_max)
        {
            y_max=p[i].y;
        }
    }


    for(int y=y_min;y<y_max;y++)
    {

         std::vector<float> tab;
          Point a,b;
          int x;

        for(int i=0;i<p.size()-1;i++)
        {
            a=p[i];
            b=p[i+1];

            if((y<=a.y && y>b.y) ||(y<=b.y && y>a.y))
                if(b.y!=a.y)
                {
                    x = a.x+((y-a.y)/(b.y-a.y))*(b.x-a.x);
                    /*
                    Point k;
                    k.x=x;
                    k.y=y;
                    bool is =1;

                    for(int j=0;j<p.size();j++)
                    {
                        if(k.x==p[j].x && k.y==p[j].y)
                        {
                            is=0;
                        }
                    }

                    if(is==1)
                    */
                    tab.push_back(x);
                }
        }

        a=p[p.size()-1];
        b=p[0];
        if((y<=a.y && y>b.y) ||(y<=b.y && y>a.y))
            if(b.y!=a.y)
            {
                x = a.x+((y-a.y)/(b.y-a.y))*(b.x-a.x);
               /*
                Point k;
                k.x=x;
                k.y=y;
                bool is =1;

                for(int j=0;j<p.size();j++)
                {
                    if(k.x==p[j].x && k.y==p[j].y)
                    {
                        is=0;
                    }
                }

                if(is==1)
                */
                tab.push_back(x);
            }




        sort(tab.begin(),tab.end());

        for(int i=0;i<tab.size();i++)
        {
            if(i%2==0)
            {
                drawLine(tab[i],(float)y,tab[i+1],(float)y,r,g,bb);
            }

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

void Okno::fill(float x1, float y1, int r1, int g1, int b1, int r2, int g2, int b2)
{
    if(r1==r2, g1==g2, b1==b2)
    {

    }else
    {
        Point p,b;
        uchar *buf;

        p.x = x1;
        p.y = y1;

        std::stack<Point> stos;

        stos.push(p);

        while(!stos.empty())
        {
            b= stos.top();
            stos.pop();

            if(b.x>=0 && b.x<im.width() && b.y >= 0 && b.y <im.height())
            {
                buf = im.scanLine(b.y);
                if(buf[(int)b.x*4]==b1 && buf[(int)b.x*4+1]==g1 && buf[(int)b.x*4+2]==r1)
                {

                    buf[(int)b.x*4]=b2;
                    buf[(int)b.x*4+1]=g2;
                    buf[(int)b.x*4+2]=r2;

                    p.x=b.x-1;
                    p.y=b.y;
                    stos.push(p);
                    p.x=b.x+1;
                    p.y=b.y;
                    stos.push(p);
                    p.x=b.x;
                    p.y=b.y+1;
                    stos.push(p);
                    p.x=b.x;
                    p.y=b.y-1;
                    stos.push(p);

                }

            }

        }
    }


}


