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

    void dylatacja();
    void erozja();
    void wypelniaj();
    void otwarcie();
    void zamkniecie();

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

    std::vector<Point> p;
    std::vector<Point> tablica;



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
