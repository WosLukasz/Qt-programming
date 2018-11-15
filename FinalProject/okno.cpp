#include "okno.h"

#include <QPainter>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <QThread>
#include <macierz.h>
#include <fstream>

Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(900,500,QImage::Format_RGB32);
    im2= QImage("textura.jpg");

    im.fill(Qt::white);

    //USTAWIENIE SRODKA EKRANU
    cx=im.width()/2.;
    cy=im.height()/2.;

    //Sciezka do katalogu z modelami .obj
    path = "D:/QT_Przyklady/ProjektZaliczeniowy/";

    //Zainicjalizowanie z-bufora
    zbuffor = new int* [im.height()];
    for(int i=0;i<im.height();i++)
    {
      zbuffor[i] = new int [im.width()];
    }

    //PIERWSZE NADANIE ZMIENNYM WARTOSCI
    if_sz = true;
    if_text = false;
    is_backface = false;
    is_oswietlenie1 = false;
    is_oswietlenie2 = false;
    obracanie = false;
    isZbuff = false;

    //SLONCE
    S1.x = 0.;
    S1.y = 0.;
    S1.z = 0.;

    //USTAWIENIE PRZESUNIECIA OBIEKTU
    zx=0;
    zy=0;
    z =600;

    SX=100.0/100.0;
    SY=100.0/100.0;
    SZ=100.0/100.0;

    TX=0;
    TY=0;
    TZ=0;

    RX=0;
    RY=0;
    RZ=0;


    wczytajPlik("a.obj");
    rysuj_w_perspektywie();
}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);
    if(obracanie)
    {

        RY++;
        if(RY>=360.)
        {
            RY=0.;
        }

        QThread::msleep(10);
    }
    rysuj_w_perspektywie();
}

float Okno::projekcja_perspX(float x, float y, float z)
{
    return (f*(x/z)+(float)cx);
}

float Okno::projekcja_perspY(float x, float y, float z)
{
    return (f*-(y/z)+(float)cy);
}

void Okno::drawLine(float x1, float y1, float x2, float y2, int r, int g, int b)
{
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

void Okno::b_sort( int ile_liczb)
{
    int i,zmiana;
    Face temp;
    do
    {
        zmiana=0;
        i=ile_liczb-1;
        do
        {
            i--;
            float sredniaJeden = (p[face[i+1].a].z + p[face[i+1].b].z + p[face[i+1].c].z)/3.;
            float sredniaDwa = (p[face[i].a].z + p[face[i].b].z + p[face[i].c].z)/3.;
            if (sredniaJeden>sredniaDwa)
            {
                temp=face[i];
                face[i]=face[i+1];
                face[i+1]=temp;
                zmiana=1;
            }
        }
        while (i!=0);
    }
    while (zmiana!=0);
}

bool Okno::backface_culling(Point A, Point B, Point C)
{
    Point view;

    view.x = 450;
    view.y = 250;
    view.z = 0;

    Vertex VIEW;

    VIEW.x = view.x -A.x;
    VIEW.y = view.y -A.y;
    VIEW.z = view.z -A.z;

    float ax = B.x - A.x;
    float ay = B.y - A.y;
    float az = B.z - A.z;
    float bx = C.x - A.x;
    float by = C.y - A.y;
    float bz = C.z - A.z;
    Vertex PROD;

    PROD.x = ay*bz-az*by;
    PROD.y = az*bx-ax*bz;
    PROD.z = ax*by-ay*bx;

    return ((ax*by-ay*bx)>0);
}

void Okno::wczytajPlik(std::string p)
{
    v.clear();
    face.clear();
    std::ifstream myfile(path+p,std::ios::in);
    std::string buf;
    if(myfile)
    {
        while(!myfile.eof())
        {
            std::getline(myfile,buf);

            if(buf[0]!='f' && buf[0]!='v'){

                continue;
            }

            if(buf[0]=='v' && buf[1]==' ')
            {
                float tmp_x,tmp_y,tmp_z;
                Point t;
                sscanf_s(buf.c_str(),"v %f %f %f",&tmp_x,&tmp_y,&tmp_z);

                t.x = (float)zx+(tmp_x);
                t.y = (float)zy+(tmp_y);
                t.z = (float)z+(tmp_z);

                v.push_back(t);
            }

            if(buf[0]=='f' && buf[1]==' ')
            {

                Face t;
                int a,b,c,a1,b1,c1;
                sscanf_s(buf.c_str(),"f %d//%d %d//%d %d//%d",&a,&a1,&b,&b1,&c,&c1);

                t.a = a-1;
                t.b = b-1;
                t.c = c-1;

                face.push_back(t);
            }
            buf.clear();
        }
    }else
    {
        std::cout<<"Nie mozna otworzyc wskazanego pliku."<<std::endl;
    }
}

void Okno::rysuj_swiatlo()
{
    float x =S1.x;
    float y = S1.y;

    drawDot(x,y,0,0,0);
    drawDot(x-1,y,0,0,0);
    drawDot(x+1,y,0,0,0);
    drawDot(x,y+1,0,0,0);
    drawDot(x,y-1,0,0,0);
}

void Okno::rysuj_w_perspektywie()
{
    //Ustawienie z-buffera do nastepnej sceny na infinity
    for(int i=0;i<im.height();i++)
    {
        for(int j=0;j<im.width();j++)
        {
            zbuffor[i][j] = INFINITY;
        }
    }

    float obrotx[16] = {1.,0.,0.,0.,
                        0.,cos((RX*M_PI)/180.),-sin((RX*M_PI)/180.),0.,
                        0.,sin((RX*M_PI)/180.),cos((RX*M_PI)/180.),0.,
                        0.,0.,0.,1.};
    float obroty[16] = {cos((RY*M_PI)/180.),0.,sin((RY*M_PI)/180.),0.,
                        0.,1.,0.,0.,
                        -sin((RY*M_PI)/180.),0.,cos((RY*M_PI)/180.),0.,
                        0.,0.,0.,1.};
    float obrotz[16] = {cos((RZ*M_PI)/180.),-sin((RZ*M_PI)/180.),0.,0.,
                        sin((RZ*M_PI)/180.),cos((RZ*M_PI)/180.),0.,0.,
                        0.,0.,1.,0.,
                        0.,0.,0.,1.};

    float przesuniecie[16] = {1.,0.,0.,TX,0.,1.,0.,TY,0.,0.,1.,TZ,0.,0.,0.,1.};
    float skala[16] = {SX,0.,0.,0.,0.,SY,0.,0.,0.,0.,SZ,0.,0.,0.,0.,1.};

    float przesuniecieDoPoczatku[16] = {1.,0.,0.,-(float)zx,0.,1.,0.,-(float)zy,0.,0.,1.,-z,0.,0.,0.,1.};
    float przesuniecieDoSrodka[16] = {1.,0.,0.,(float)zx,0.,1.,0.,(float)zy,0.,0.,1.,z,0.,0.,0.,1.};

    macierz A0(4,4,przesuniecieDoPoczatku);
    macierz A1(4,4,obrotx);
    macierz A2(4,4,obroty);
    macierz A3(4,4,obrotz);
    macierz A4(4,4,przesuniecieDoSrodka);

    macierz B= macierz(4,4,przesuniecie);
    macierz C= macierz(4,4,skala);

    macierz WYNIKOWAObrotu = WYNIKOWAObrotu.mnoz(A1,A2);
    macierz WYNIKOWAObrotu1 = WYNIKOWAObrotu.mnoz(WYNIKOWAObrotu,A3);


    macierz WYNIKOWA = WYNIKOWA.mnoz(B,C);

    p.clear();
    v2d.clear();

    srand(0);
    for(int i=0;i<v.size();i++)
    {

        float tab1[4] = {v[i].x,v[i].y,v[i].z,1.};

        macierz D= macierz(4,1,tab1);
        macierz poczatkowaObrotu = poczatkowaObrotu.mnoz(A0,D);
        macierz SRODKOWAObrotu = SRODKOWAObrotu.mnoz(WYNIKOWAObrotu1,poczatkowaObrotu);
        macierz E=E.mnoz(A4,SRODKOWAObrotu);
        macierz F=F.mnoz(WYNIKOWA,E);

        Point vp;
        vp.x=F.tab[0][0];
        vp.y=F.tab[1][0];
        vp.z=F.tab[2][0];

        Point v2dPoint;

        v2dPoint.x=projekcja_perspX(vp.x,vp.y,vp.z);
        v2dPoint.y=projekcja_perspY(vp.x,vp.y,vp.z);
        v2dPoint.z = vp.z;
        v2d.push_back(v2dPoint);

        Point z;

        z.x = (int)v2dPoint.x;
        z.y = (int)v2dPoint.y;
        z.z = (int)vp.z;

        //zeby bylo widac teksture(rand()%100)/100.0
        z.u=0.5*im2.width();
        z.v=0.5*im2.height();
        p.push_back(z);
    }


    //Algorytm malarza
    b_sort(face.size());

    im.fill(Qt::white);
    rysuj_swiatlo();

    for(int i=0;i<face.size();i++)
    {
        //BACKFACE CULLING
        if(is_backface)
        {
            if(Okno::backface_culling(p[face[i].a],p[face[i].b],p[face[i].c]))
            {
                continue;
            }
        }

        //TEXTUROWANIE
        std::vector<Point> pp;
        if(if_text)
        {
            Point k;

            k.x = (p[face[i].a].x + p[face[i].b].x + p[face[i].c].x)/3;
            k.y = (p[face[i].a].y + p[face[i].b].y + p[face[i].c].y)/3;
            k.z = (p[face[i].a].z + p[face[i].b].z + p[face[i].c].z)/3;
            cs = cos_norm_light(p[face[i].a],p[face[i].b],p[face[i].c]);


            pp.push_back(p[face[i].a]);
            pp.push_back(p[face[i].b]);
            pp.push_back(p[face[i].c]);

            scan_line2(pp);
        }
        pp.clear();

        //Rysowanie linii pomocniczych szescianu
        if(if_sz)
        {
            drawLine(v2d[face[i].a].x,v2d[face[i].a].y,v2d[face[i].b].x,v2d[face[i].b].y,0,255,0);
            drawLine(v2d[face[i].b].x,v2d[face[i].b].y,v2d[face[i].c].x,v2d[face[i].c].y,0,255,0);
            drawLine(v2d[face[i].c].x,v2d[face[i].c].y,v2d[face[i].a].x,v2d[face[i].a].y,0,255,0);
        }

    }
    update();
}


//WYZNACZANIE NORMALNYCH POCZATEK
Okno::Vertex Okno::normalna(Point a, Point b, Point c)
{
    Vertex KA,KB;

    KA.x = b.x - a.x;
    KA.y = b.y - a.y;
    KA.z = b.z - a.z;

    KB.x = c.x - a.x;
    KB.y = c.y - a.y;
    KB.z = c.z - a.z;

    Vertex K;

    K.x = KA.y*KB.z-KA.z*KB.y;
    K.y = KA.z*KB.x-KA.x*KB.z;
    K.z = KA.x*KB.y-KA.y*KB.x;

    return K;
}

float Okno::cos_norm_light(Point a, Point b, Point c) // do cieniowania plaskiego
{
    Point k;

     k.x = (a.x + b.x + c.x)/3;
     k.y = (a.y + b.y + c.y)/3;
     k.z = (a.z + b.z + c.z)/3;

     Vertex KA, KB;

     KA.x = a.x-k.x;
     KA.y = a.y-k.y;
     KA.z = a.z-k.z;

     KB.x = b.x-k.x;
     KB.y = b.y-k.y;
     KB.z = b.z-k.z;

     Vertex K, S;

     K.x = KA.y*KB.z-KA.z*KB.y;
     K.y = KA.z*KB.x-KA.x*KB.z;
     K.z = KA.x*KB.y-KA.y*KB.x;

     S.x = S1.x-k.x;
     S.y = S1.y-k.y;
     S.z = S1.z-k.z;

    return (S.x*K.x + S.y*K.y + S.z*K.z)/(sqrt(S.x*S.x+S.y*S.y+S.z*S.z)*sqrt(K.x*K.x+K.y*K.y+K.z*K.z));

}

float Okno::cos_norm_light3(Point a, Vertex K)
{
     Vertex S;

     S.x = S1.x-a.x;
     S.y = S1.y-a.y;
     S.z = S1.z-a.z;

    return (S.x*K.x + S.y*K.y + S.z*K.z)/(sqrt(S.x*S.x+S.y*S.y+S.z*S.z)*sqrt(K.x*K.x+K.y*K.y+K.z*K.z));

}

float Okno::cos_odbite_view(Point a, Vertex K, float B)
{
    Point view;

    view.x = 450;
    view.y = 250;
    view.z = 0;

     Vertex S;

     S.x = view.x-a.x;
     S.y = view.y-a.y;
     S.z = view.z-a.z;

     double kat = acos((S.x*K.x + S.y*K.y + S.z*K.z)/(sqrt(S.x*S.x+S.y*S.y+S.z*S.z)*sqrt(K.x*K.x+K.y*K.y+K.z*K.z)));
     double beta = acos(B);
     double alfa = kat - beta;
     double k = (alfa*180)/M_PI;

     return cos(alfa);
}

float Okno::cos_odbite_view2(Point a, Vertex K, float B)
{

    Vertex L; //wektor miedzy swiatlem a punktem na plaszczyznie

    L.x = S1.x-a.x;
    L.y = S1.y-a.y;
    L.z = S1.z-a.z;

    Vertex R; // wektor odbity

    R.x = 2*K.x*(K.y*L.z-K.z*L.y)-L.x;
    R.y = 2*K.y*(K.z*L.x-K.x*L.z)-L.y;
    R.z = 2*K.z*(K.x*L.y-K.y*L.x)-L.z;


    Point view;

    view.x = 450;
    view.y = 250;
    view.z = 0;

     Vertex S; //wektor miedzy widzem a punktem na plaszczyznie

     S.x = view.x-a.x;
     S.y = view.y-a.y;
     S.z = view.z-a.z;

     return (S.x*R.x + S.y*R.y + S.z*R.z)/(sqrt(S.x*S.x+S.y*S.y+S.z*S.z)*sqrt(R.x*R.x+R.y*R.y+R.z*R.z));

/*
     double kat = acos((S.x*K.x + S.y*K.y + S.z*K.z)/(sqrt(S.x*S.x+S.y*S.y+S.z*S.z)*sqrt(K.x*K.x+K.y*K.y+K.z*K.z)));
     double beta = acos(B);
     double alfa = kat - beta;
     double k = (alfa*180)/M_PI;

     return cos(alfa);
     */
}
//WYZNACZANIE NORMALNYCH KONIEC


//TEXTUROWANIE I CIENIOWANIE POCZATEK
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

bool comp(const Okno::Point & a,const  Okno::Point & b)
{
    return (a.y<b.y);
}

void Okno::scan_line2(std::vector<Point> pp)
{

    Vertex A,B,C;

    A = normalna(pp[0],pp[1],pp[2]);
    B = normalna(pp[1],pp[2],pp[0]);
    C = normalna(pp[2],pp[0],pp[1]);

    pp[0].N = A;
    pp[1].N = B;
    pp[2].N = C;

    sort(pp.begin(),pp.end(),comp);

    float ll,xl,ul,vl, lr,xr,ur,vr;

    for(int y=(int)pp[0].y;y<(int)pp[1].y;y++)
    {

           if(pp[1].y==pp[0].y)
           {
               continue;
           }else
           {
                ll=((float)y-pp[0].y)/(pp[1].y-pp[0].y);
           }

        xl=pp[0].x + ll*(pp[1].x-pp[0].x);
        ul=pp[0].u + ll*(pp[1].u-pp[0].u);
        vl=pp[0].v + ll*(pp[1].v-pp[0].v);

        if(pp[2].y==pp[0].y)
        {
             continue;
        }else
        {
          lr=((float)y-pp[0].y)/(pp[2].y-pp[0].y);
        }

        xr=pp[0].x + lr*(pp[2].x-pp[0].x);
        ur=pp[0].u + lr*(pp[2].u-pp[0].u);
        vr=pp[0].v + lr*(pp[2].v-pp[0].v);

        float zl=pp[0].z + ll*(pp[1].z-pp[0].z);
        float zr=pp[0].z + lr*(pp[2].z-pp[0].z);

        Vertex AA, BB;
        AA.x =pp[0].N.x + ll*(pp[1].N.x-pp[0].N.x);
        AA.y =pp[0].N.y + ll*(pp[1].N.y-pp[0].N.y);
        AA.z =pp[0].N.z + ll*(pp[1].N.z-pp[0].N.z);

        BB.x =pp[0].N.x + lr*(pp[2].N.x-pp[0].N.x);
        BB.y =pp[0].N.y + lr*(pp[2].N.y-pp[0].N.y);
        BB.z =pp[0].N.z + lr*(pp[2].N.z-pp[0].N.z);

        draw_line2(xl,xr,y,ul,vl,ur,vr,AA,BB,zl,zr);
    }

    for(int y=(int)pp[1].y;y<(int)pp[2].y;y++)
    {

        if(pp[2].y==pp[1].y)
        {
             continue;
        }else
        {
             ll=((float)y-pp[1].y)/(pp[2].y-pp[1].y);
        }

        xl=pp[1].x + ll*(pp[2].x-pp[1].x);
        ul=pp[1].u + ll*(pp[2].u-pp[1].u);
        vl=pp[1].v + ll*(pp[2].v-pp[1].v);

        if(pp[2].y==pp[0].y)
        {
             continue;
        }else
        {
             lr=((float)y-pp[0].y)/(pp[2].y-pp[0].y);
        }

        xr=pp[0].x + lr*(pp[2].x-pp[0].x);
        ur=pp[0].u + lr*(pp[2].u-pp[0].u);
        vr=pp[0].v + lr*(pp[2].v-pp[0].v);

        float zl=pp[1].z + ll*(pp[2].z-pp[1].z);
        float zr=pp[0].z + lr*(pp[2].z-pp[0].z);

        Vertex AA, BB;
        AA.x =pp[1].N.x + ll*(pp[2].N.x-pp[1].N.x);
        AA.y =pp[1].N.y + ll*(pp[2].N.y-pp[1].N.y);
        AA.z =pp[1].N.z + ll*(pp[2].N.z-pp[1].N.z);

        BB.x =pp[0].N.x + lr*(pp[2].N.x-pp[0].N.x);
        BB.y =pp[0].N.y + lr*(pp[2].N.y-pp[0].N.y);
        BB.z =pp[0].N.z + lr*(pp[2].N.z-pp[0].N.z);

        draw_line2(xl,xr,y,ul,vl,ur,vr,AA,BB,zl,zr);
    }
}

void Okno::draw_line2(float xl, float xr, float y, float ul, float vl, float ur, float vr,Vertex L, Vertex R,float zl,float zr)
{
    if(xl>xr)
    {
        std::swap(xl,xr);
        std::swap(zl,zr);
        std::swap(L,R);
    }

    for(int x=(int)xl;x<(int)xr;x++)
    {
        int r,g,b;


        float l= (x-xl)/(xr-xl);
        float u = ul + l*(ur-ul);
        float v = vl + l*(vr-vl);
        float z = zl + l*(zr-zl);

        Vertex N;

        N.x = L.x + l*(R.x-L.x);
        N.y = L.y + l*(R.y-L.y);
        N.z = L.z + l*(R.z-L.z);

        Point p;

        p.x=x;
        p.y=y;
        p.z=z;

        float cso = cos_norm_light3( p, N);
        float cso2 = cos_odbite_view2(p, N,cso);

        if(u>=0 && u<im2.width() && v>=0 && v<im2.height())
        {
          //czy wlaczyc z-buffering
          if(isZbuff)
          {
              if(x<im.width() && x>=0 && y<im.height() && y>=0 && abs(z)<zbuffor[(int)y][(int)x])
              {
                   uchar *buf= im2.scanLine((int)v);

                   b=buf[4*(int)u];
                   g=buf[4*(int)u+1];
                   r=buf[4*(int)u+2];
                   //czy oswietlenie plaskie czy phonga
                   if(is_oswietlenie1)
                   {
                      b=b*std::max((float)0,cs);
                      g=g*std::max((float)0,cs);
                      r=r*std::max((float)0,cs);
                   }
                   else if(is_oswietlenie2)
                   {
                      b=b+b*std::max((float)0,cso)+0.5*b*(float)pow(std::max((float)0,cso2),5);
                      g=g+g*std::max((float)0,cso)+0.5*g*(float)pow(std::max((float)0,cso2),5);
                      r=r+r*std::max((float)0,cso)+0.5*r*(float)pow(std::max((float)0,cso2),5);
                   }

                   if(r>255){r=255;}
                   if(g>255){g=255;}
                   if(b>255){b=255;}

                   drawDot(x,y,r,g,b);
                   zbuffor[(int)y][(int)x]=(int)z;
              }
           }else
           {
               uchar *buf= im2.scanLine((int)v);

               b=buf[4*(int)u];
               g=buf[4*(int)u+1];
               r=buf[4*(int)u+2];
               //czy oswietlenie plaskie czy phonga
               if(is_oswietlenie1)
               {
                  b=b*std::max((float)0,cs);
                  g=g*std::max((float)0,cs);
                  r=r*std::max((float)0,cs);
               }
               else if(is_oswietlenie2)
               {
                   b=b*std::max((float)0,cso)+0.5*b*(float)pow(std::max((float)0,cso2),5);
                   g=g*std::max((float)0,cso)+0.5*g*(float)pow(std::max((float)0,cso2),5);
                   r=r*std::max((float)0,cso)+0.5*r*(float)pow(std::max((float)0,cso2),5);
               }
               if(r>255){r=255;}
               if(g>255){g=255;}
               if(b>255){b=255;}

               drawDot(x,y,r,g,b);
           }
        }
    }
}
//TEXTUROWANIE I CIENIOWANIE KONIEC

//POCZATEK SLOTOW
void Okno::changeTX(int e)
{
    TX=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeTY(int e)
{
    TY=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeTZ(int e)
{
    TZ=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRX(int e)
{
    RX=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRY(int e)
{
    RY=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRZ(int e)
{
    RZ=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeSX(int e)
{
    SX=(float)e/100.;
    rysuj_w_perspektywie();
}

void Okno::changeSY(int e)
{
    SY=(float)e/100.;
    rysuj_w_perspektywie();
}

void Okno::changeSZ(int e)
{
    SZ=(float)e/100.;
    rysuj_w_perspektywie();
}

void Okno::if_szkielet(bool if_s)
{

    if_sz = if_s;
}

void Okno::if_texturowanie(bool if_t)
{
    if_text = if_t;
}

void Okno::if_backface(bool if_b)
{
    is_backface=if_b;
}

void Okno::if_obr(bool e)
{
    obracanie = e;
}

void Okno::if_z_buff(bool e)
{
    isZbuff = e;
}

void Okno::if_brakOsw(bool e)
{

        is_oswietlenie1 = false;
        is_oswietlenie2 = false;


}

void Okno::if_oswietlenie1(bool e)
{
    is_oswietlenie1 = e;
    is_oswietlenie2 = false;
}

void Okno::changeS1X(int e)
{
    S1.x = e;
    rysuj_swiatlo();
}

void Okno::changeS1Y(int e)
{
    S1.y = e;
    rysuj_swiatlo();
}

void Okno::changeS1Z(int e)
{
    S1.z = e;
    rysuj_swiatlo();
}

void Okno::change_to_1(bool e)
{
    wczytajPlik("a.obj");
    rysuj_w_perspektywie();
}

void Okno::change_to_3(bool e)
{
    wczytajPlik("pikachu.obj");
    rysuj_w_perspektywie();
}

void Okno::change_to_4(bool e)
{
    wczytajPlik("bulbasaur.stl.obj");
    rysuj_w_perspektywie();
}

void Okno::change_to_5(bool e)
{
    wczytajPlik(file);
    rysuj_w_perspektywie();
}

void Okno::change_text(QString str)
{

    file = str.toLocal8Bit().constData();
    if(file.length() < 4 || file[file.length()-4]!='.' || file[file.length()-3]!='o' || file[file.length()-2]!='b' || file[file.length()-1]!='j')
    {
        file = file +".obj";
    }

}

void Okno::if_oswietlenie2(bool e)
{
    is_oswietlenie2 = e;
    is_oswietlenie1 = false;
}
//KONIEC SLOTOW
