#ifndef GETSENTIMENTSFROMJSON_H
#define GETSENTIMENTSFROMJSON_H

#include <QFile>
#include <QMap>

QMap<QString, double> MakeSentimentsTree(const QString &);

#endif	// GETSENTIMENTSFROMJSON_H
