#ifndef ANALYZETWEETSFILE_H
#define ANALYZETWEETSFILE_H

#include "QFile"
#include <QVector>
#include <QString>
#include "statestructure.h"
#include "getSentimentsFromJSON.h"

struct Tweet
{
    PointCoordinate coord;
    double positivity_characterization = 0;
};

QVector<QString> ReadTweetsFromFile(const QString &, const QMap<QString, double>);

double CountMessagePositivity(const QString &);

Tweet GetOneTweet(const QString &, const QMap<QString, double> &);

QVector<Tweet> GetTweetsCharacteristics(const QString &, const QString &);

#endif	// ANALYZETWEETSFILE_H
