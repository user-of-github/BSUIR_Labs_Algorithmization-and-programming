#include "getSentimentsFromJSON.h"
#include <QDebug>

QMap<QString, double> MakeSentimentsTree(const QString &url)
{
    QFile file(url);
    auto response = QMap<QString, double>();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return response;

    while (!file.atEnd())
    {
       auto pair = QString(file.readLine()).trimmed().split(',');
       auto key = pair.first().trimmed();
       auto value = pair.last().trimmed().remove('\n').toDouble();

       response.insert(key, value);
    }

    return response;
}
