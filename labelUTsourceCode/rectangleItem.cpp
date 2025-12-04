#include "rectangleitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>


RectangleItem::RectangleItem(QGraphicsItem *parent): QGraphicsRectItem(parent)      // 构造函数，可以设置box的边框颜色属性
{
    this->dragging = false;
    this->resizing = false;
    this->resizingVertex = -1;

    setPen(QPen(Qt::blue, 2));  // 设置矩形框的边框颜色
    setBrush(QBrush(QColor(0, 0, 255, 50)));  // 设置矩形框的填充颜色（半透明）
}

void RectangleItem::setRect(const QRectF &rect)     // 刷新
{
    prepareGeometryChange();  // 通知 Qt 该项的几何信息即将改变（提高刷新效率）
    QGraphicsRectItem::setRect(rect);
    if (scene()) {
        scene()->update();  // 让整个场景重绘，清除残留的红色点Bug
    }
}

// **获取四个红点的区域**
QRectF RectangleItem::getVertexRect(int vertexIndex, bool drawOrPick) {
    qreal radius = vertexRadius;
    if(!drawOrPick)
        radius = radius * 1;    // *2为了降低红点的拾取难度

    switch (vertexIndex) {
        case 0: return QRectF(rect().topLeft() - QPointF(radius, radius), QSizeF(radius * 2, radius * 2));
        case 1: return QRectF(rect().topRight() - QPointF(radius, radius), QSizeF(radius * 2, radius * 2));
        case 2: return QRectF(rect().bottomLeft() - QPointF(radius, radius), QSizeF(radius * 2, radius * 2));
        case 3: return QRectF(rect().bottomRight() - QPointF(radius, radius), QSizeF(radius * 2, radius * 2));
        default: return QRectF();
    }
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 绘制矩形框
    QGraphicsRectItem::paint(painter, option, widget);

    // 绘制四个圆形顶点
    painter->setBrush(Qt::red);
    for (int i = 0; i < 4; ++i) {
        painter->drawEllipse(getVertexRect(i));  // 绘制每个红色圆形顶点
    }
}


// **获取鼠标靠近的红点索引**
int RectangleItem::getHoveredVertex(const QPointF& scenePos) {
    for (int i = 0; i < 4; ++i) {
        bool isPick = false;
        if (getVertexRect(i, isPick).contains(scenePos)) {
            return i;
        }
    }
    return -1;
}

// **获取调整后的矩形**
QRectF RectangleItem::getAdjustedRect(int vertexIndex, const QPointF& delta, qreal imageWidth, qreal imageHeight) {
    QRectF newRect = rect();

    switch (vertexIndex) {
        case 0:  // 左上角
            newRect.setTopLeft(newRect.topLeft() + delta);
            break;
        case 1:  // 右上角
            newRect.setTopRight(newRect.topRight() + delta);
            break;
        case 2:  // 左下角
            newRect.setBottomLeft(newRect.bottomLeft() + delta);
            break;
        case 3:  // 右下角
            newRect.setBottomRight(newRect.bottomRight() + delta);
            break;
    }

    // **限制矩形大小**
    if (newRect.width() < minSize) {
        newRect.setWidth(minSize);
    }
    if (newRect.height() < minSize) {
        newRect.setHeight(minSize);
    }

    // **限制矩形不超出图像范围**
    QRectF imageBounds(0, 0, imageWidth, imageHeight);
    if (!imageBounds.contains(newRect)) {
        newRect = newRect.intersected(imageBounds);
    }

    return newRect;
}

void RectangleItem::setSelected(bool selected) {
    this->selected = selected;
    if (selected) {
        setPen(QPen(Qt::red, 3));  // 选中时红色加粗边框
        setBrush(QBrush(QColor(255, 0, 0, 80))); // 选中时更深的填充色
    } else {
        setPen(QPen(Qt::blue, 2));  // 未选中时蓝色细边框
        setBrush(QBrush(QColor(0, 0, 255, 50))); // 未选中时浅蓝填充
    }
    update();  // 触发重绘
}

