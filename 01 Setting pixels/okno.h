#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

private:
    int x,y;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
    void setX(int);
    void setY(int);

};

#endif // OKNO_H
