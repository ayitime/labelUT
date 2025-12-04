#include "DraggableHLineItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

DraggableHLineItem::DraggableHLineItem(qreal yPos, qreal width, qreal height, QGraphicsScene* scene, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_y(yPos), m_width(width), m_height(height)
{
    if (scene) {
        scene->addItem(this);
    }

    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    m_pen.setColor(Qt::blue);
    m_pen.setWidth(4);
    m_pen.setStyle(Qt::CustomDashLine);
    m_dashPattern = {1, 2}; // 默认虚线样式
    m_pen.setDashPattern(m_dashPattern);
    m_pen.setCosmetic(true);
}

void DraggableHLineItem::setPen(const QPen& pen)
{
    m_pen = pen;
    update();
}

void DraggableHLineItem::setDashPattern(const QVector<qreal>& pattern)
{
    m_dashPattern = pattern;
    m_pen.setDashPattern(m_dashPattern);
    update();
}

void DraggableHLineItem::setYPos(int y) {
    m_y = y;
    prepareGeometryChange();
//    update();
}

/// 拾取区域设置
QRectF DraggableHLineItem::boundingRect() const
{
    return QRectF(0, m_y - 5, m_width, 10);
}

void DraggableHLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    m_pen.setDashPattern(m_dashPattern);
    painter->setPen(m_pen);
    painter->drawLine(0, m_y, m_width, m_y);
}

void DraggableHLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    const QPointF pos = event->pos();
    const QRectF pickRect(0, m_y - 5, m_width, 10);  // shape 区域
    if (pickRect.contains(pos)) {
        scene()->views().first()->setCursor(Qt::SizeVerCursor);
    } else {
        scene()->views().first()->unsetCursor();
    }

    QGraphicsItem::hoverMoveEvent(event);
}

void DraggableHLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_dragging = true;
    m_lastMousePos = event->scenePos();
    event->accept();
}

void DraggableHLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_dragging) {
        event->ignore();
        return;
    }

    QPointF currentPos = event->scenePos();
    qreal dy = currentPos.y() - m_lastMousePos.y();
    m_y += dy;

    if (m_y < 0)
        m_y = 0;
    else if (m_y >= m_height)
        m_y = m_height;

    m_lastMousePos = currentPos;
    prepareGeometryChange();
    update();
    event->accept();
}

void DraggableHLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    m_dragging = false;
    event->accept();
}
