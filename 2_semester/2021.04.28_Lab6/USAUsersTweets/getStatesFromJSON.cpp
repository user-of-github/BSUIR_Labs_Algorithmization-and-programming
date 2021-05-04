#include "getStatesFromJSON.h"

QString ReadJSONFromFile(const QString &file_name)
{
    QString response;
    QFile file;
    file.setFileName(file_name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    response = file.readAll();
    file.close();

    return response;
}

QJsonObject ConvertToJsonObject(const QString &raw_string)
{
    return (QJsonDocument::fromJson(raw_string.toUtf8())).object();
}

ClosedLoop CreateCloseLoop(const QJsonArray &points_array)
{
    auto current_loop_in_the_state = ClosedLoop();

    for (const auto &point_array_pair : points_array)
    {
        auto x = point_array_pair.toArray().first().toDouble(),
             y = point_array_pair.toArray().last().toDouble();

        auto new_point = PointCoordinate();
        new_point.x = x;
        new_point.y = y;
        current_loop_in_the_state.coordinates.push_back(new_point);
    }

    return current_loop_in_the_state;
}

QVector<ClosedLoop> CreateAllCloseLoopsForCurrentState(const QJsonArray &loops_wrappers)
{
    auto all_loops_for_current_state = QVector<ClosedLoop>();
    for (const auto &loop_wrapper : loops_wrappers)
    {
        auto points_array = loop_wrapper.toArray().size() > 1
                ? loop_wrapper.toArray()
                : loop_wrapper.toArray().first().toArray();

        all_loops_for_current_state.push_back(CreateCloseLoop(points_array));
    }

    return all_loops_for_current_state;
}

State CreateState(const QString &key, const QJsonObject &json)
{
    auto NEW_STATE = State();
    NEW_STATE.name = key;

    auto loops_wrappers = json[key].toArray();


    NEW_STATE.closed_loops = CreateAllCloseLoopsForCurrentState(loops_wrappers);

    return NEW_STATE;
}







QVector<State> GetStates(const QString &url)
{
    auto raw_json = ConvertToJsonObject(ReadJSONFromFile(url));
    auto keys = raw_json.keys();

    auto states = QVector<State>();

    for (const auto &key : keys)
        states.push_back(CreateState(key, raw_json));

    return states;
}
