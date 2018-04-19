#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

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

    void rysuj();
    void wypelniaj();

private:
    QImage im;
    float x,y;
    int opcja;

    struct Point
        {
            float x,y;
        };

    int rr,gg,bb;



    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    void fill(float x1, float x2, int r1, int g1, int b1,int r, int g, int b );
};

#endif // OKNO_H
