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

private:

    QImage im;
    float x,y;

    void putPixel(float x1, float y1, float x2, float y2, int r, int g, int b);
};

#endif // OKNO_H
