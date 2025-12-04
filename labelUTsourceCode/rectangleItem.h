#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QGraphicsRectItem>
//#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPointF>
#include <QDebug>

//#include <QObject>


//QT_BEGIN_NAMESPACE
//namespace Ui { class RectangleItem; }
//QT_END_NAMESPACE


class RectangleItem : public QGraphicsRectItem//, public QObject
{
//    Q_OBJECT      // 罪大恶极！给我去掉！

public:
    RectangleItem(QGraphicsItem *parent = nullptr);
    void setRect(const QRectF &rect);
    int getHoveredVertex(const QPointF& scenePos);
    QRectF getAdjustedRect(int vertexIndex, const QPointF& delta, qreal imageWidth, qreal imageHeight);

    void setSelected(bool selected);
//    bool isSelected() const { return selected; }

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    bool resizing;
    int resizingVertex;
    bool dragging;  // 判断矩形框是否正在拖动
    QPointF lastPos; // 上一个鼠标位置

    QRectF getVertexRect(int vertexIndex, bool drawOrPick=true);
    const qreal vertexRadius = 5.0;  // 控制红点大小
    const qreal minSize = 20.0;     // 限制最小尺寸

    bool selected = false; // 选中状态
};

#endif // RECTANGLEITEM_H
