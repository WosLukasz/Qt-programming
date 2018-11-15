#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <vector>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = NULL);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:

/*
    void dylatacja();
    void erozja();
    void wypelniaj();
    void otwarcie();
    void zamkniecie();
*/
    void convert();

    void changeH(int x);
    void changeS(int x);
    void changeV(int x);

    void rysujR(QString s);
    void rysujG(QString s);
    void rysujB(QString s);


private:
    QImage im;
    QImage im2;
    float x,y;
    int opcja;

    struct Point
        {
            float x,y;
        };

    int rr,gg,bb;
    double RR,GG,BB;

    std::vector<Point> p;
    std::vector<Point> tablica;

    double przesunH;
    double przesunS;
    double przesunV;

    struct RGB
    {
        double  r;
        double  g;
        double  b;

    };

    struct HSV
    {
        double  h;
        double  s;
        double  v;

    };

    RGB converttoRGB(HSV hsv);
    HSV converttoHSV(double  r, double  g, double  b);
    void drawDot(int x, int y, int r, int g, int b);
    void scan_line(std::vector<Point> p, int r, int g, int b);
    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    void fill(float x1, float x2, int r1, int g1, int b1,int r, int g, int b );
    bool kernel(int x, int y);
    bool kernel2(int x, int y);
    //void drawDot2(int x, int y);
    void drawDot2(int x, int y, int r, int g, int b);
};

#endif // OKNO_H
