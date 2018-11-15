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

    void sxchange(int);
    void sychange(int);
    void txchange(int);
    void tychange(int);
    void rrchange(int);


private:
    QImage im;
    QImage im2;
    float x,y;
    int xx,yy;
    int opcja;
    int TX,TY,SX,SY;
    float R;
    struct Point
        {
            float x,y;
        };

    struct Vectorr
        {
            Point a,b;
        };



    std::vector<Point> p;
    std::vector<Point> stable;
    std::vector<Vectorr> vectors;


    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    void wykonaj_operacje();

};

#endif // OKNO_H
