#include "qpaintwidget.h"

#include <QApplication>
#include <QDateTime>

#include "statestructure.h"
#include "getStatesFromJSON.h"
#include "analyzeTweetsFile.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto start_time = QTime::currentTime();
    const QString states_coordinates_file_url = "states.json",
                  sentiments_file_url = "sentiments.csv",
                  tweets_file_url = "very_small_tweets.txt";

    auto USA_map = GetStates(states_coordinates_file_url);
    auto tweets = GetTweetsCharacteristics(tweets_file_url, sentiments_file_url);


    Qpaintwidget canvas(USA_map, tweets);

    qDebug() << (start_time.msecsTo(QTime::currentTime())) / 1000 << " seconds";
    canvas.show();


    return app.exec();
}
