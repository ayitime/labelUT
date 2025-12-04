#ifndef DRAGGABLEHLINEITEM_H
#define DRAGGABLEHLINEITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

class DraggableHLineItem : public QGraphicsItem
{
public:
    DraggableHLineItem(qreal yPos, qreal width, qreal height, QGraphicsScene* scene, QGraphicsItem* parent = nullptr);

    void setPen(const QPen& pen);
    void setDashPattern(const QVector<qreal>& pattern);

    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    qreal getPosY() const { return m_y;}
    void setYPos(int y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    qreal m_width;      // 线条长度
    qreal m_height;     // 最大y
    qreal m_y;          // 当前y

    bool m_dragging = false;
    QPointF m_lastMousePos;

    QPen m_pen;
    QVector<qreal> m_dashPattern;
};

#endif // DRAGGABLEHLINEITEM_H
