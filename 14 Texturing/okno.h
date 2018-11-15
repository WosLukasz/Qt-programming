#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <vector>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

    struct Point
        {
            float x,y;
            float u,v;
        };

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:

    void rysuj();
    void wypelniaj();

private:
    QImage im;
    QImage im2;
    int opcja;
    int i;



    int rr,gg,bb;

    std::vector<Point> p;
     std::vector<Point> uv;



    void drawDot(int x, int y, int r, int g, int b);
    void scan_line(std::vector<Point> p, int r, int g, int b);
    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    void fill(float x1, float x2, int r1, int g1, int b1,int r, int g, int b );
    void scan_line2( );
    draw_line2(float xl,float xr,float y,float ul,float vl,float ur,float vr);


};

#endif // OKNO_H
