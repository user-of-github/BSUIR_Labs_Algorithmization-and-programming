#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include "statestructure.h"
#include "analyzeTweetsFile.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QThread>

using std::min;
using std::max;


class Qpaintwidget : public QWidget
{
    Q_OBJECT
public:
    Qpaintwidget(const QVector <State> &, const QVector <Tweet> &);

    void MakePolygonStates();

    void DrawPolygonStates();

    void DrawUsersPoints();

    void paintEvent(QPaintEvent *);

private:
    QVector <State> data_;
    const QColor background_color_ = QColor::fromRgb(44, 62, 80),
            outline_color_ = QColor::fromRgb(44, 62, 80),
            start_fill_color_ = QColor::fromRgb(44, 44, 84),
            tweet_dot_color_ = QColor::fromRgb(241, 196, 15),
            neutral_state_color_ = QColor::fromRgb(247, 241, 227);

    size_t tweet_dot_radius_ = 1;
    size_t window_width_ = 1500,
            window_height_ = 600;

    const size_t outline_width_ = 3;

    double full_original_map_width_,
            full_original_map_height_,
            full_map_width,
            full_map_height;

    double offset_y_,
            offset_x,
            margin_left_,
            margin_top_;

    double zoom_level_;
    const double kAdditionalYZoom = 1.3;

    // rgb(192, 57, 43)
    const size_t kNegativeRed = 192,
            kNegativeGreen = 57,
            kNegativeBlue = 43,
            kNegativeMaxDelta = 255 - max(max(kNegativeRed, kNegativeRed), kNegativeBlue);

    // rgb(41, 128, 185)
    const size_t kPositiveRed = 41,
            kPositiveGreen = 128,
            kPositiveBlue = 185,
            kPositiveMaxDelta = 255 - max(max(kPositiveRed, kPositiveGreen), kPositiveBlue);

    double positiveScaleRatio,
            negativeScaleRatio;

    double positiveMaxCharacteristic, negativeMaxCharactaristic;
    QVector <QPolygon> polygons_list_;
    QVector <Tweet> users_tweets_;

    void TransformCoordinates1();

    void CalculateOriginalFullWidthAndHeight();

    void CalculateZoomLevel();

    void TransformCoordinates2();

    void TransformUserTweetsCoordinates();

    void CalculateOffsets();

    void LinkTweetsAndStates();

    void CountBackgroundRatio();
};

#endif // QPAINTWIDGET_H
