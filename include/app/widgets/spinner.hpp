#pragma once
#include <QWidget>
#include <QTimer>
#include <QPainter>

class Spinner : public QWidget
{
public:
    explicit Spinner(QWidget *parent = nullptr)
        : QWidget(parent), m_angle(0)
    {
        setFixedSize(40, 40);

        connect(&m_timer, &QTimer::timeout, this, [this]() {
            m_angle = (m_angle + 30) % 360;
            update();
        });

        m_timer.start(50);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        int width = qMin(this->width(), this->height());
        QRectF rect(5, 5, width - 10, width - 10);

        QPen pen(Qt::gray, 4);
        p.setPen(pen);
        p.drawArc(rect, m_angle * 16, 120 * 16);
    }

private:
    QTimer m_timer;
    int m_angle;
};