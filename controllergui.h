#ifndef CONTROLLERGUI_H
#define CONTROLLERGUI_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QBrush>

#include "gamepadserver.h"
#include "bardrawer.h"

class ControllerGUI : public QOpenGLWidget
{
    Q_OBJECT
public:
    ControllerGUI(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected slots:
    void catchControllerState(const GamepadState & gps, const int & player);

private:
    QMargins m_margins;
    GamepadState m_gps;

    void drawDirectionPad(QPainter & painter);
    void drawButtonPad(QPainter & painter);
    void drawStartBack(QPainter & painter);
    void drawShoulders(QPainter & painter);
    void drawJoySticks(QPainter & painter);

    void drawDirectionButton(QPainter & painter, const bool & btn, const QRect & rect);
    void drawPlayerButton(QPainter & painter, const bool & btn, const QRect & rect);
    void setPressedButtonBrush(QPainter & painter, const bool & btn);

    void drawTrigger(QPainter & painter, const QRect & rect, const uint8_t trigger);
    void drawBar(QPainter & painter, const QPoint & centerPoint, const QSize & size, const double & filled, const double & rotation);
    void drawBar(QPainter &painter, const QRect & rect, const double &filled, const double &rotation);

    QBrush m_backgroundBrush = QBrush(QColor(85, 93, 108), Qt::SolidPattern);
    QBrush m_buttonBrush_noPress = QBrush(QColor(201, 215, 237), Qt::SolidPattern);
    QBrush m_buttonBrush_Pressed = QBrush(QColor(45, 226, 151), Qt::SolidPattern);
};

#endif // CONTROLLERGUI_H
