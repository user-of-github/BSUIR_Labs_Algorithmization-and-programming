#ifndef STATESTRUCTURE_H
#define STATESTRUCTURE_H

#include <QVector>
#include <QPolygon>

struct PointCoordinate
{
    double x, y;
};

struct ClosedLoop
{
    QVector <PointCoordinate> coordinates;
};

class State
{
public:
    QString name;

    State() : name(""){}

    QVector <ClosedLoop> closed_loops;
    QVector <QPolygon> polygon;
    double positive_characteristic = 0;
};

#endif // STATESTRUCTURE_H
