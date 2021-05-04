#ifndef FRACTAL_H
#define FRACTAL_H

#include <QWidget>
#include <QPainter>
//#include <QPropertyAnimation>
//#include <QEasingCurve>

namespace Ui {
class Fractal;
}

class Fractal : public QWidget
{
    Q_OBJECT

public:
    explicit Fractal(QWidget *parent = nullptr);
    ~Fractal();

protected:
    void paintEvent(QPaintEvent *event);
    void DrawFractal(QPainter *qp);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Fractal *ui;
};


#endif // FRACTAL_H
