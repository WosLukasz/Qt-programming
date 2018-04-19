#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <vector>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:

    void but1();
    void but2();
    void but3();


private:

    QImage im;
    int z;

    struct Point
    {
        float x,y;
    };
    int g;
    int opcja;

    std::vector<Point> tab;

    void putPixel(int x, int y,int r, int g, int b);

    void drawLine(float x1, float y1, float x2, float y2,int r, int g, int b);


    void drawBezier(Point a,Point b,Point c,Point d);


};

#endif // OKNO_H
