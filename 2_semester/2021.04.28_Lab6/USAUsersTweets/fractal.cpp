#include "fractal.h"
#include "widget.h"
#include <math.h>
#include <QThread>
#include <QColor>
#include <QKeyEvent>

Fractal::Fractal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Fractal::~Fractal()
{
    delete ui;
}

static int check = 0;
static double borderL = -2;
static double borderR = 2;
static double borderU = 2;
static double borderD = -2;
static int exat = 50;
static int upper = 40;
/*static*/ double step = (borderR - borderL) / 800;

void Fractal::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter qp(this);
    DrawFractal(&qp);
}

void Fractal::keyPressEvent(QKeyEvent *event)
{
    /*
    int key=event->key();
    if(event->key() == Qt::Key_A)
    {

    }
    */
    //QWidget::keyPressEvent(event);
    //int key=event->key();

    switch (event->key())
    {
        case Qt::Key_Plus:
        borderL += step * 50;
        borderR -= step * 50;
        borderU -= step * 50;
        borderD += step * 50;
        update();
            break;
        case Qt::Key_Minus:
        borderL -= step * 50;
        borderR += step * 50;
        borderU += step * 50;
        borderD -= step * 50;
        update();
            break;
        case Qt::Key_Left:
        borderL -= step * 20;
        borderR -= step * 20;
        update();
            break;
        case Qt::Key_Right:
        borderL += step * 20;
        borderR += step * 20;
        update();
            break;
        case Qt::Key_Down:
        borderU -= step * 20;
        borderD -= step * 20;
        update();
            break;
        case Qt::Key_Up:
        borderU += step * 20;
        borderD += step * 20;
        update();
            break;
        case Qt::Key_9:
        exat -= 10;
        update();
            break;
        case Qt::Key_0:
        exat += 10;
        update();
            break;
         default:
             QWidget::keyPressEvent(event);
     }

}

void Fractal::DrawFractal(QPainter *qp)
{
    //step
    //double step = (borderR - borderL) / 800;
    step = (borderR - borderL) / 800;
    double z1 = 0;
    double z2 = 0;
    double hz2 = 0;
    double c1 = 0;
    double c2 = 0;
    QPen pen(Qt::black, 1);
    qp->setPen(pen);
    bool flag = true;
    bool find = false;
    QColor c;
    int pi = 0;
    //int pj = 400;
    static int line = 400;
    for (int j = 800; j > 0; j--)
    {
        for (int i = 0; i < 800; i++)
        {
            c1 = borderL + step * i;
            c2 = borderD + step * (800 - j);
            z1 = 0;
            z2 = 0;
            int k = 0;
            while (k < exat)
            {
                hz2 = z2;
                z2 = 2 * z1 * z2 + c2;
                z1 = z1 * z1 + c1 - (hz2 * hz2);
                if (sqrt(z1 * z1 + z2 *z2) >= 2)
                {
                    if (j == line && i > 10 && pi == i - 1)
                    {
                        find = true;
                    }
                    flag = false;
                    /*c.setRgb(((int)(sqrt(z1 * z1 + z2 *z2) * 1000000)) % 150 + 103, (int)(z2 / z2) % 255, 50, 255);*/
                    c.setRgb((k % 2) * 32 + 128, (k % 4) * 64, (k % 2) * 16 + 128, 255);
                    qp->setPen(c);
                    qp->drawPoint(i, j);
                    break;
                }
                k++;
            }
            if (flag == true)
            {
                if (j == line && find == false && i > 10)
                {
                    pi = i;
                }
                /*c.setRgb((int)(z1 / z1) % 255, ((int)(sqrt(z1 * z1 + z2 *z2) * 100000)) % 50 + 75, 160, 255);*/
                c.setRgb((k % 2) * 32 + 128, (k % 4) * 64, (k % 2) * 16 + 128, 255);
                qp->setPen(c);
                qp->drawPoint(i, j);
            }
            flag = true;
            if (j < line && find == false)
            {
                line += 1;
            }
        }
    }
    if (find == true && check < 100000)
    {
        /*
        if (check > upper)
        {
            exat += 5;
            upper += 7;
        }
        */
        /*
        if (check == 80)//
        {
            line += 50;
            double amendment = 50 * step;//
            borderU = borderU - amendment;//
            borderD = borderD + amendment;//
        }
        if (check == 200)//
        {
            line += 50;
            double amendment = 50 * step;//
            borderU = borderU - amendment;//
            borderD = borderD + amendment;//
        }
        */
        int one = 32;
        int two = one * 2;
        if (pi > 440)
        {
            double amendment = (800 - pi) * step;
            borderL = borderL + amendment / one;
            borderU = borderU - amendment / two;
            borderD = borderD + amendment / two;
            //borderR = borderR - amendment / 128;
            //QThread::msleep(25);
            update();
            check++;
        }
        else if (pi < 440)
        {
            double amendment = pi * step;
            borderR = borderR - amendment / one;
            borderU = borderU - amendment / two;
            borderD = borderD + amendment / two;
            //borderL = borderL - amendment / 128;
            //QThread::msleep(25);
            update();
            check++;
        }/*
        else if (pi < 360 && pj > 440)
        {
            double amendment = pi * step;
            //borderL = borderL + amendment / 128;
            borderR = borderR - amendment / 128;
            borderU = borderU - amendment / 128;
            //borderD = borderD + amendment / 128;
            //QThread::msleep(25);
            update();
            check++;
        }
        else if (pi < 360 && pj < 360)
        {
            double amendment = pi * step;
            //borderL = borderL + amendment / 128;
            borderR = borderR - amendment / 128;
            //borderU = borderU - amendment / 128;
            borderD = borderD + amendment / 128;
            //QThread::msleep(25);
            update();
            check++;
        }*/
        else
        {
            double amendment = pi * step;
            borderL = borderL + amendment / one;
            //borderR = borderR - amendment / 128;
            borderU = borderU - amendment / two;
            borderD = borderD + amendment / two;
            //QThread::msleep(25);
            update();
            check++;
        }
    }
    else
    {
        for (int j = 100; j > 10; j--)
        {
            for (int i = 0; i < 10; i++)
            {
                qp->drawPoint(i, j);
            }
        }
    }
}
