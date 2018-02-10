#include "bardrawer.h"

BarDrawer::BarDrawer()
{

}

void BarDrawer::draw(QPainter &painter) {

    int progressWidth = (int) ((double) m_mainRect.size().width() * m_percent_filled);
    QSize progressSize(progressWidth, m_mainRect.size().height());

    qreal xc = (m_mainRect.left() + m_mainRect.right()) * 0.5;
    qreal yc = (m_mainRect.top() + m_mainRect.bottom()) * 0.5;

    painter.translate(xc, yc);
    painter.rotate(m_rotation_deg);

    qreal rx = -(m_mainRect.size().width() * 0.5);
    qreal ry = -(m_mainRect.size().height() * 0.5);

    painter.setBrush(m_emptyBrush);
    painter.drawRect(QRect(QPoint(rx, ry), m_mainRect.size()));

    painter.setBrush(m_fullBrush);
    painter.drawRect(QRect(QPoint(rx, ry), progressSize));

    qreal myTop = ry;
    qreal myBot = m_mainRect.size().height() + ry;
    qreal markingLength = m_mainRect.size().height()*.25;
    qreal markingSpacing = m_mainRect.size().width() / (qreal) (m_totalMarkings);
    painter.setPen(QColor(0, 0, 0));
    for (size_t i = 0; i < m_totalMarkings; i++) {
        qreal x = rx + (qreal) i * markingSpacing;
        painter.drawLine(x, myTop, x, myTop+markingLength);
        painter.drawLine(x, myBot, x, myBot-markingLength);
    }

    painter.resetTransform();
}
