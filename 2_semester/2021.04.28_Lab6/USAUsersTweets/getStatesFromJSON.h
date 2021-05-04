#ifndef GETSTATESFROMJSON_H
#define GETSTATESFROMJSON_H

#include "statestructure.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


QString ReadJSONFromFile(const QString &);

QJsonObject ConvertToJsonObject(const QString &);

ClosedLoop CreateCloseLoop(const QJsonArray &);

QVector<ClosedLoop> CreateAllCloseLoopsForCurrentState(const QJsonArray &);

State CreateState(const QString &, const QJsonObject &);

QVector<State> GetStates(const QString &);

#endif	// GETSTATESFROMJSON_H
