#include "rectangleitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>


RectangleItem::RectangleItem(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    this->dragging = false;
    this->resizing = false;
    this->resizingVertex = -1;

    setPen(QPen(Qt::blue, 2));  // 设置矩形框的边框颜色
    setBrush(QBrush(QColor(0, 0, 255, 50)));  // 设置矩形框的填充颜色（半透明）
}

void RectangleItem::setRect(const QRectF &rect)     // 刷新
{
    QGraphicsRectItem::setRect(rect);
    update();  // 更新视图
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 绘制矩形框
    QGraphicsRectItem::paint(painter, option, widget);

    // 绘制四个顶点
    painter->setBrush(Qt::red);
    for (int i = 0; i < 4; ++i) {
        painter->drawEllipse(getVertexRect(i));  // 绘制每个顶点
    }
}

QRectF RectangleItem::getVertexRect(int vertexIndex) {
    // 四个顶点的矩形区域（可以修改顶点大小）
    switch (vertexIndex) {
        case 0: return QRectF(rect().topLeft() - QPointF(5, 5), QSizeF(10, 10));  // 左上角
        case 1: return QRectF(rect().topRight() - QPointF(5, 5), QSizeF(10, 10)); // 右上角
        case 2: return QRectF(rect().bottomLeft() - QPointF(5, 5), QSizeF(10, 10)); // 左下角
        case 3: return QRectF(rect().bottomRight() - QPointF(5, 5), QSizeF(10, 10)); // 右下角
        default: return QRectF();
    }
}

void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dragging = true;
    lastPos = event->pos();  // 记录点击的鼠标位置
    QGraphicsRectItem::mousePressEvent(event);

//    // 检查鼠标是否在四个顶点附近
//    for (int i = 0; i < 4; ++i) {
//        if (getVertexRect(i).contains(event->pos())) {
//            resizing = true;
//            resizingVertex = i;
////            setCursor(Qt::SizeAllCursor);
//            qDebug() << "aa";
//            return;
//        }
//    }
//    // 否则，进行矩形框的拖动
//    dragging = true;
//    lastPos = event->pos();
////    setCursor(Qt::OpenHandCursor);
//    QGraphicsRectItem::mousePressEvent(event);
}

void RectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "WTFFFFF";
    resizing = false;
    dragging = false;
//    setCursor(Qt::ArrowCursor);  // 恢复光标为箭头
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void RectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        QPointF delta = event->pos() - lastPos;
        moveBy(delta.x(), delta.y());  // 拖动矩形框
        lastPos = event->pos();
    }
    QGraphicsRectItem::mouseMoveEvent(event);

//    if (dragging) {
//        QPointF delta = event->pos() - lastPos;
//        moveBy(delta.x(), delta.y());  // 拖动矩形框
//        lastPos = event->pos();
//    } else if (resizing) {
//        // 处理矩形框的大小调整
//        QPointF newPos = event->pos();
//        QRectF newRect = rect();

//        // 根据所选的顶点调整矩形的大小
//        switch (resizingVertex) {
//        case 0: newRect.setTopLeft(newPos); break; // 左上角
//        case 1: newRect.setTopRight(newPos); break; // 右上角
//        case 2: newRect.setBottomLeft(newPos); break; // 左下角
//        case 3: newRect.setBottomRight(newPos); break; // 右下角
//        }
////        setRect(newRect);  // 更新矩形框
//    } else {
////        updateCursor(event);  // 更新鼠标光标
//    }

//    QGraphicsRectItem::mouseMoveEvent(event);
}

void RectangleItem::updateCursor(QGraphicsSceneMouseEvent *event)
{
    bool overVertex = false;
    for (int i = 0; i < 4; ++i) {
        if (getVertexRect(i).contains(event->pos())) {
            overVertex = true;
            break;
        }
    }
    if (overVertex) {
//        setCursor(Qt::SizeAllCursor);  // 鼠标在矩形框顶点上时
    } else {
//        setCursor(Qt::ArrowCursor);   // 鼠标在其他区域时
    }
}
