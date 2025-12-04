#ifndef GATEOVERLAY_H
#define GATEOVERLAY_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCursor>
#include <QPen>
#include <QBrush>

class GateOverlay : public QGraphicsRectItem
{
public:
    enum DragMode {
        None,
        TopEdge,
        BottomEdge,
        MoveWhole
    };

    GateOverlay(const QRectF& rect, qreal imageTop, qreal imageBottom, QGraphicsScene* scene, QGraphicsItem* parent = nullptr);
    qreal topBoundary() const { return rect().top(); }
    qreal bottomBoundary() const { return rect().bottom(); }
    void setTopBoundary(int y);
    void setBottomBoundary(int y);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    DragMode dragMode;
    QPointF lastMousePos;
    const qreal edgeTolerance = 10.0;

    qreal imageTopBoundary;
    qreal imageBottomBoundary;

    bool isNearTopEdge(const QPointF& pos) const;
    bool isNearBottomEdge(const QPointF& pos) const;
};

#endif // GATEOVERLAY_H
