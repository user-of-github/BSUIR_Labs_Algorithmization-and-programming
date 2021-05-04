#include "qpaintwidget.h"
#include <QDebug>

Qpaintwidget::Qpaintwidget(const QVector<State> &data, const QVector<Tweet> &tweets)
{
    this->setWindowTitle("✅ USA USERS' TWEETS ANALYSIS   📊   Copyright  © 2021.  All rights reserved.  Slutski Nikita 📈");
    this->data_ = data;
    this->users_tweets_ = tweets;
    this->TransformCoordinates1();
    this->CalculateOriginalFullWidthAndHeight();
    this->CalculateZoomLevel();
    this->TransformCoordinates2();
    this->CalculateOffsets();
    this->MakePolygonStates();
    this->TransformUserTweetsCoordinates();
    this->LinkTweetsAndStates();
    this->CountBackgroundRatio();
    this->setFixedSize(QSize(this->window_width_, this->window_height_));
}

void Qpaintwidget::MakePolygonStates()
{    
    for (auto &state : this->data_)
        for (const auto &loop : state.closed_loops)
        {
            auto polygon = QPolygon();

            for (const auto &point : loop.coordinates)
                polygon << QPoint(point.x + this->margin_left_ + this->offset_x, point.y + this->margin_top_ + this->offset_y_);

            state.polygon.push_back(polygon);
        }


}

void Qpaintwidget::DrawPolygonStates()
{
    QPainter canvas(this);
    canvas.setPen(this->outline_color_);
    canvas.setBrush(this->start_fill_color_);
    auto outline = QPen();
    outline.setColor(this->outline_color_);
    outline.setWidth(this->outline_width_);
    canvas.setPen(outline);

    for (const auto &state : this->data_)
    {
        double red = (state.positive_characteristic > 0
                      ? this->kPositiveRed : this->kNegativeRed),
                green = (state.positive_characteristic > 0
                         ? this->kPositiveGreen : this->kNegativeGreen),
                blue = (state.positive_characteristic > 0
                        ? this->kPositiveBlue : this->kNegativeBlue);

        double deltaForEvery = state.positive_characteristic > 0
                ? (this->positiveMaxCharacteristic - state.positive_characteristic) * this->positiveScaleRatio
                : (state.positive_characteristic - this->negativeMaxCharactaristic) * this->negativeScaleRatio;


        red += deltaForEvery;
        green += deltaForEvery;
        blue += deltaForEvery;

        canvas.setBrush(QColor::fromRgb(red, green, blue));

        if (state.positive_characteristic == 0)
            canvas.setBrush(this->neutral_state_color_);

        for (const auto &polygon : state.polygon)
            canvas.drawPolygon(polygon);
    }
}

void Qpaintwidget::DrawUsersPoints()
{
    QPainter canvas(this);
    canvas.setPen(this->tweet_dot_color_);
    canvas.setBrush(this->tweet_dot_color_);

    for (const auto &tweet : this->users_tweets_)
        canvas.drawEllipse(QPoint(tweet.coord.x, tweet.coord.y), this->tweet_dot_radius_, this->tweet_dot_radius_);
}


void Qpaintwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    srand(time(NULL));
    QPainter canvas(this);
    canvas.fillRect(0, 0, width(), height(), this->background_color_);

    this->DrawPolygonStates();
    //this->DrawUsersPoints();
}

void Qpaintwidget::TransformCoordinates1()
{
    double min_x = 0,
            min_y = 0;

    for (const auto &state : this->data_)
        for (const auto &close_loop : state.closed_loops)
            for (const auto &point : close_loop.coordinates)
            {
                min_x = min(min_x, point.x);
                min_y = min(min_y, point.y);
            }

    min_x = min_x < 0 ? min_x * (-1) : 0;
    min_y = min_y < 0 ? min_y * (-1) : 0;

    for (auto &state : this->data_)
        for (auto &close_loop : state.closed_loops)
            for (auto &point : close_loop.coordinates)
            {
                point.x += min_x;
                point.y += min_y;
            }

    for (auto &tweet : this->users_tweets_)
    {
        tweet.coord.x += min_x;
        tweet.coord.y += min_y;
    }

}

void Qpaintwidget::CalculateOriginalFullWidthAndHeight()
{
    double min_x = 0, max_x = 0,
            min_y = 0, max_y = 0;

    for (const auto &state : this->data_)
        for (const auto &close_loop : state.closed_loops)
            for (const auto &point : close_loop.coordinates)
            {
                min_x = min(min_x, point.x);
                max_x = max(max_x, point.x);

                min_y = min(min_y, point.y);
                max_y = max(max_y, point.y);
            }

    this->full_original_map_height_ = max_y - min_y;
    this->full_original_map_width_ = max_x - min_x;
}

void Qpaintwidget::CalculateZoomLevel()
{
    this->zoom_level_ = ((double)this->window_width_ / this->full_original_map_width_) * 3.1;
    this->full_map_width = this->window_width_;
    this->full_map_height = this->full_original_map_height_ * this->zoom_level_;


    this->window_height_ = full_map_height;
    this->window_width_ = full_map_width;
    this->resize(this->window_width_, this->window_height_);
}

void Qpaintwidget::TransformCoordinates2()
{
    for (auto &state : this->data_)
    {
        for (auto &close_loop : state.closed_loops)
            for (auto &point : close_loop.coordinates)
            {
                point.x *= (this->zoom_level_);
                point.y *= (this->zoom_level_) * this->kAdditionalYZoom;

                point.y = this->full_map_height - point.y;
            }

    }

    for (auto &tweet : this->users_tweets_)
    {
        tweet.coord.x *= this->zoom_level_;
        tweet.coord.y *= this->zoom_level_ * this->kAdditionalYZoom;
        tweet.coord.y = this->full_map_height - tweet.coord.y;
    }
}

void Qpaintwidget::TransformUserTweetsCoordinates()
{
    for (auto &tweet : this->users_tweets_)
    {
         tweet.coord.x += this->margin_left_ + this->offset_x;
         tweet.coord.y += this->margin_top_ + this->offset_y_;
    }
}

void Qpaintwidget::CalculateOffsets()
{
    double min_x = 0, max_x = 0,
            min_y = 0, max_y = 0;

    for (const auto &state : this->data_)
        for (const auto &close_loop : state.closed_loops)
            for (const auto &point : close_loop.coordinates)
            {
                min_x = min(min_x, point.x);
                max_x = max(max_x, point.x);

                min_y = min(min_y, point.y);
                max_y = max(max_y, point.y);
            }

    this->margin_left_ = min_x < 0 ? (-1) * min_x : 0;
    this->margin_top_ = min_y < 0 ? (-1) * min_y : 0;

    this->offset_x = (this->window_width_ / 2) - (this->full_map_width / 2);
    this->offset_y_  = (this->window_height_ / 2) - (this->full_map_height / 2);
}


void Qpaintwidget::LinkTweetsAndStates()
{
    for (const auto &tweet : this->users_tweets_)
    {
        for (auto &state : this->data_)
            for (const auto &polygon : state.polygon)
                if (polygon.containsPoint(QPoint(tweet.coord.x, tweet.coord.y), Qt::FillRule::OddEvenFill) ||
                    polygon.containsPoint(QPoint(tweet.coord.x, tweet.coord.y), Qt::FillRule::WindingFill) ||
                    polygon.contains(QPoint(tweet.coord.x, tweet.coord.y)))
                {
                    state.positive_characteristic += tweet.positivity_characterization;
                    break;
                }
    }
}

void Qpaintwidget::CountBackgroundRatio()
{
    double negative_min = 0, negative_max = 0,
           positive_min = 0, positive_max = 0;

    for (const auto &state : this->data_)
    {
        if (state.positive_characteristic < 0)
        {
            negative_min = min(negative_min, state.positive_characteristic);
            negative_max = max(negative_max, state.positive_characteristic);
        }
        else
        {
            positive_min = min(positive_min, state.positive_characteristic);
            positive_max = max(positive_max, state.positive_characteristic);
        }
    }

    this->positiveScaleRatio =  this->kPositiveMaxDelta / (positive_max - positive_min);
    this->negativeScaleRatio =  this->kNegativeMaxDelta / (negative_max - negative_min);

   // qDebug() << this->positiveScaleRatio << ' ' << this->negativeScaleRatio << '\n';
    this->positiveMaxCharacteristic = positive_max;
    this->negativeMaxCharactaristic = negative_min;
}

