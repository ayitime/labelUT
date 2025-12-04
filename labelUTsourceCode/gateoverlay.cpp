#include "GateOverlay.h"
#include <QPainter>

GateOverlay::GateOverlay(const QRectF& rect, qreal imageTop, qreal imageBottom, QGraphicsScene* scene, QGraphicsItem* parent)
    : QGraphicsRectItem(rect, parent),
      dragMode(None),
      imageTopBoundary(imageTop),
      imageBottomBoundary(imageBottom)
{
    if (scene) {
        scene->addItem(this);
    }

    setAcceptHoverEvents(true);  // 接收鼠标悬停事件
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}

void GateOverlay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF r = rect();
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->setBrush(QColor(0, 255, 0, 50));  // 半透明绿色
    painter->drawRect(r);
}

bool GateOverlay::isNearTopEdge(const QPointF& pos) const
{
    return std::abs(pos.y() - rect().top()) <= edgeTolerance;
}

bool GateOverlay::isNearBottomEdge(const QPointF& pos) const
{
    return std::abs(pos.y() - rect().bottom()) <= edgeTolerance;
}

void GateOverlay::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QPointF pos = event->pos();
    if (isNearTopEdge(pos) || isNearBottomEdge(pos)) {
//        setCursor(Qt::SizeVerCursor);
        scene()->views().first()->setCursor(Qt::SizeVerCursor);
    } else if (rect().contains(pos)) {
//        setCursor(Qt::OpenHandCursor);
        scene()->views().first()->setCursor(Qt::OpenHandCursor);
    }
    else {
//        unsetCursor();
        scene()->views().first()->unsetCursor();
    }
    QGraphicsRectItem::hoverMoveEvent(event);
}

void GateOverlay::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF pos = event->pos();
    if (isNearTopEdge(pos)) {
        dragMode = TopEdge;
        event->accept();
    } else if (isNearBottomEdge(pos)) {
        dragMode = BottomEdge;
        event->accept();
    } else if (rect().contains(pos)) {
        dragMode = MoveWhole;
//        setCursor(Qt::ClosedHandCursor);
        scene()->views().first()->setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        dragMode = None;
        event->ignore();
    }
    lastMousePos = event->scenePos();
}

void GateOverlay::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (dragMode == None) {
        event->ignore();
        return;
    }

    QPointF delta = event->scenePos() - lastMousePos;
    QRectF r = rect();

    if (dragMode == TopEdge) {
        qreal newTop = r.top() + delta.y();
        newTop = qMax(newTop, imageTopBoundary);      // 不能超过图像顶部
        newTop = qMin(newTop, r.bottom() - 1);        // 保持最小1像素高度
        r.setTop(newTop);
    } else if (dragMode == BottomEdge) {
        qreal newBottom = r.bottom() + delta.y();
        newBottom = qMin(newBottom, imageBottomBoundary); // 不能超过图像底部
        newBottom = qMax(newBottom, r.top() + 1);         // 保持最小1像素高度
        r.setBottom(newBottom);
    } else if (dragMode == MoveWhole) {
        qreal desiredDeltaY = delta.y();

        qreal newTop = r.top() + desiredDeltaY;
        qreal newBottom = r.bottom() + desiredDeltaY;

        if (newTop < imageTopBoundary) {
            desiredDeltaY = imageTopBoundary - r.top();
        } else if (newBottom > imageBottomBoundary) {
            desiredDeltaY = imageBottomBoundary - r.bottom();
        }

        r.translate(0, desiredDeltaY);
    }

    setRect(r);
    lastMousePos = event->scenePos();

     event->accept();
     update();
}

void GateOverlay::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    dragMode = None;
//    unsetCursor();
    scene()->views().first()->unsetCursor();
    event->accept();
}

void GateOverlay::setTopBoundary(int y) {
    QRectF r = rect();
    y = qBound(imageTopBoundary, static_cast<qreal>(y), r.bottom() - 1); // 限制合法范围
    r.setTop(y);
    setRect(r);
    update();
}

void GateOverlay::setBottomBoundary(int y)
{
    QRectF r = rect();
    y = qBound(r.top() + 1, static_cast<qreal>(y), imageBottomBoundary); // 限制合法范围
//    y = qBound(r.top() + 1, y, static_cast<int>(imageBottomBoundary));
    r.setBottom(y);
    setRect(r);
    update();
}
