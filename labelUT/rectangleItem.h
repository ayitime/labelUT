#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QGraphicsRectItem>
//#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QDebug>

//#include <QObject>


//QT_BEGIN_NAMESPACE
//namespace Ui { class RectangleItem; }
//QT_END_NAMESPACE


class RectangleItem : public QGraphicsRectItem//, public QObject
{
//    Q_OBJECT      // 罪大恶极！给去去掉！

public:
    RectangleItem(QGraphicsItem *parent = nullptr);
    void setRect(const QRectF &rect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    bool resizing;
    int resizingVertex;
    bool dragging;  // 判断矩形框是否正在拖动
    QPointF lastPos; // 上一个鼠标位置

    QRectF getVertexRect(int vertexIndex);
    void updateCursor(QGraphicsSceneMouseEvent *event);

};

#endif // RECTANGLEITEM_H
