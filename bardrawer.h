#ifndef BARDRAWER_H
#define BARDRAWER_H

#include <QPainter>

class BarDrawer
{
public:
    BarDrawer();

    void draw(QPainter & painter);

    void setMainRect(const QRect & rect) { m_mainRect = rect; }
    void setFill(const double & percFilled) { m_percent_filled = percFilled; }
    void setEmptyBrush(const QBrush & brush) { m_emptyBrush = brush; }
    void setFullBrush(const QBrush & brush) { m_fullBrush = brush; }
    void setRotationAngle(const double & deg) { m_rotation_deg = deg; }
    void setTotalMarkings(const int & m) { m_totalMarkings = m; }

    const QRect & mainRect() const { return m_mainRect; }
    const QRect & progressRect() const { return m_progressRect; }
    const double & rotationDeg() const { return m_rotation_deg; }
    const QBrush & emptyBrush() const { return m_emptyBrush; }
    const QBrush & fullBrush() const { return m_fullBrush; }
    const double & percFilled() const { return m_percent_filled; }
    const int & totalMarkings() const { return m_totalMarkings; }

private:
    QRect m_mainRect;
    QRect m_progressRect;

    double m_rotation_deg = 0.0;

    QBrush m_emptyBrush;
    QBrush m_fullBrush;

    double m_percent_filled = 0;
    int m_totalMarkings = 0;
};

#endif // BARDRAWER_H
