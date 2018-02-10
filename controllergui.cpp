#include "controllergui.h"

#include <QTimer>

ControllerGUI::ControllerGUI(QWidget *parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f)
{
    connect(&GamepadServer::instance(), SIGNAL(stateUpdate(GamepadState,int)),
            this, SLOT(catchControllerState(GamepadState,int)));

    QTimer * updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(60);

    setMinimumSize(QSize(480, 300));
    setMaximumSize(QSize(480, 300));
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_margins = QMargins(30, 30, 30, 30);
}

void ControllerGUI::initializeGL()
{

}

void ControllerGUI::paintGL()
{
    QPainter painter(this);

    // Establish the background
    painter.setBrush(m_backgroundBrush);
    painter.drawRect(rect());

    drawDirectionPad(painter);
    drawButtonPad(painter);
    drawStartBack(painter);
    drawShoulders(painter);
    drawJoySticks(painter);
}

void ControllerGUI::resizeGL(int w, int h)
{

}

void ControllerGUI::catchControllerState(const GamepadState & gps, const int & player)
{
    m_gps = gps;
//    if (player == 0) {
//        m_gps = gps;
//    }
}

void ControllerGUI::drawDirectionPad(QPainter & painter)
{
    QSize dirBtnSize(30,20);
    int boxSize = dirBtnSize.width()*2 + dirBtnSize.height();
    QSize dirPadSize(boxSize,boxSize);
    QRect dirPadPlacement(QPoint(0,0), dirPadSize);
    dirPadPlacement.translate(m_margins.left(), ((height()-boxSize)/2));

    QRect leftButton(dirPadPlacement.topLeft(), dirBtnSize);
    leftButton.translate(0, dirBtnSize.width());
    drawDirectionButton(painter, m_gps.m_pad_left, leftButton);

    QRect rightButton(leftButton.topLeft(), dirBtnSize);
    rightButton.translate(dirBtnSize.width() + dirBtnSize.height(), 0);
    drawDirectionButton(painter, m_gps.m_pad_right, rightButton);

    QRect upButton(dirPadPlacement.topLeft(), dirBtnSize.transposed());
    upButton.translate(dirBtnSize.width(), 0);
    drawDirectionButton(painter, m_gps.m_pad_up, upButton);

    QRect downButton(upButton.topLeft(), dirBtnSize.transposed());
    downButton.translate(0, dirBtnSize.width() + dirBtnSize.height());
    drawDirectionButton(painter, m_gps.m_pad_down, downButton);
}

void ControllerGUI::drawButtonPad(QPainter & painter)
{
    QSize playerBtnSize(20,20);
    int boxSize = playerBtnSize.width()*2 + playerBtnSize.height();
    QSize playerPadSize(boxSize,boxSize);
    QRect playerPadPlacement(QPoint(0,0), playerPadSize);
    playerPadPlacement.translate(
                width() - (boxSize + m_margins.right()),
                ((height()-boxSize)/2));

    QRect xButton(playerPadPlacement.topLeft(), playerBtnSize);
    xButton.translate(0, playerBtnSize.width());
    drawPlayerButton(painter, m_gps.m_pad_x, xButton);

    QRect bButton(xButton.topLeft(), playerBtnSize);
    bButton.translate(playerBtnSize.width() + playerBtnSize.height(), 0);
    drawPlayerButton(painter, m_gps.m_pad_b, bButton);

    QRect yButton(playerPadPlacement.topLeft(), playerBtnSize.transposed());
    yButton.translate(playerBtnSize.width(), 0);
    drawPlayerButton(painter, m_gps.m_pad_y, yButton);

    QRect aButton(yButton.topLeft(), playerBtnSize.transposed());
    aButton.translate(0, playerBtnSize.width() + playerBtnSize.height());
    drawPlayerButton(painter, m_gps.m_pad_a, aButton);
}

void ControllerGUI::drawStartBack(QPainter & painter)
{
    QSize btnSize(30, 20);
    int padding = 30;
    QSize startBackSize(btnSize.width()*2 + padding, btnSize.height());
    QRect startBackRect(rect().topLeft(), startBackSize);
    startBackRect.translate(
        (width()-startBackSize.width())/2,
        (rect().height() - (btnSize.height()+80))/2);

    QRect backBtn(startBackRect.topLeft(), btnSize);
    drawDirectionButton(painter, m_gps.m_pad_back, backBtn);

    QRect startBtn(startBackRect.topLeft(), btnSize);
    startBtn.translate(btnSize.width() + padding, 0);
    drawDirectionButton(painter, m_gps.m_pad_start, startBtn);
}

void ControllerGUI::drawShoulders(QPainter & painter)
{
    QSize shoulderBtnSize(30, 20);
    QSize triggerBtnSize(30, 30);
    int spacingY = 10;
    int spacingX = 100;

    QSize shoulderPadSize(shoulderBtnSize.width() + triggerBtnSize.height() + spacingX,
                        shoulderBtnSize.height() + triggerBtnSize.width() + spacingY);

    QRect shoulderPad(QPoint((width()-shoulderPadSize.width())*.5, m_margins.top()),
                      shoulderPadSize);

    QRect leftTrigger(shoulderPad.topLeft(), triggerBtnSize);
    drawTrigger(painter, leftTrigger, m_gps.m_lTrigger);
    QRect rightTrigger(
                QPoint(shoulderPad.left() + triggerBtnSize.height() + spacingX, shoulderPad.top()),
                triggerBtnSize);
    drawTrigger(painter, rightTrigger, m_gps.m_rTrigger);

    QRect leftShoulder(
                QPoint(shoulderPad.left(), shoulderPad.top() + triggerBtnSize.width() + spacingY),
                shoulderBtnSize);
    drawDirectionButton(painter, m_gps.m_lShoulder, leftShoulder);

    QRect rightShoulder(
                QPoint(shoulderPad.left() + triggerBtnSize.height() + spacingX,
                       shoulderPad.top() + triggerBtnSize.width() + spacingY),
                shoulderBtnSize);
    drawDirectionButton(painter, m_gps.m_rShoulder, rightShoulder);
}

void ControllerGUI::drawTrigger(QPainter & painter, const QRect & rect, const uint8_t trigger) {
    drawBar(painter, rect, (float) trigger / 255.0, -90);
}

void ControllerGUI::drawBar(QPainter & painter, const QPoint & centerPoint, const QSize & size, const double & filled, const double & rotation) {
    QRect barRect(centerPoint, size);
    drawBar(painter, barRect, filled, rotation);
}

void ControllerGUI::drawBar(QPainter &painter, const QRect & rect, const double &filled, const double &rotation) {
    BarDrawer bd;
    bd.setEmptyBrush(m_buttonBrush_noPress);
    bd.setFullBrush(m_buttonBrush_Pressed);
    bd.setMainRect(rect);
    bd.setFill(filled);
    bd.setRotationAngle(rotation);
    bd.setTotalMarkings(10);
    bd.draw(painter);
}

void ControllerGUI::drawJoySticks(QPainter & painter)
{

}

void ControllerGUI::drawDirectionButton(QPainter & painter, const bool & btn, const QRect & rect) {
    setPressedButtonBrush(painter, btn);
    painter.drawRect(rect);
}

void ControllerGUI::drawPlayerButton(QPainter & painter, const bool & btn, const QRect & rect) {
    setPressedButtonBrush(painter, btn);
    painter.drawEllipse(rect);
}

void ControllerGUI::setPressedButtonBrush(QPainter & painter, const bool & btn) {
    if (btn) {
        painter.setBrush(m_buttonBrush_Pressed);
    } else {
        painter.setBrush(m_buttonBrush_noPress);
    }
}


