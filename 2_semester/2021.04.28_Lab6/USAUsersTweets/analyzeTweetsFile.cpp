#include "analyzeTweetsFile.h"
#include <QDebug>

QVector<QString> ReadTweetsFromFile(const QString &url)
{
    QFile file(url);
    auto response = QVector<QString>();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return response;

    while (!file.atEnd())
       response.push_back(QString(file.readLine()));

    return response;
}

double CountMessagePositivity(const QString &message, const QMap<QString, double> &sentiments)
{
   double response = 0;
   const QString oddSymbols = "@()| \\ / *\' \"#";

   foreach(auto &key, sentiments.keys())
       if (message.contains(key))
           response += sentiments[key];

   return response;
}

Tweet GetOneTweet(const QString &line, const QMap<QString, double> &sentiments)
{
    auto query = line.trimmed();
    auto coordinatesString = (query.left(query.indexOf(']')));
    coordinatesString = coordinatesString
            .right(coordinatesString.size() - coordinatesString.indexOf('[') - 1);

    const QString toMiss = "012345678 9_-:\t";
    auto index = query.indexOf(']') + 1;
    while(index < query.size() && toMiss.contains(query.at(index)))
        ++index;

    Tweet response;
    response.coord.y = coordinatesString.trimmed().split(',').first().trimmed().toDouble();
    response.coord.x = coordinatesString.trimmed().split(',').last().trimmed().toDouble();

    auto message = query.right(query.size() - index);
    response.positivity_characterization = CountMessagePositivity(message, sentiments);
    return response;
}

QVector<Tweet> GetTweetsCharacteristics(const QString &tweets_url, const QString &sentiments_url)
{
    auto readStrings = ReadTweetsFromFile(tweets_url);
    auto sentiments = MakeSentimentsTree(sentiments_url);

    QVector<Tweet> response;

    for (const auto &line : readStrings)
        response.push_back(GetOneTweet(line, sentiments));

    return response;
}
