#include "alignindicatorline.h"
#include <QGraphicsScene>

AlignIndicatorLine::AlignIndicatorLine(double x, double height, QGraphicsScene* scene, QObject* parent)
    : QObject(parent), QGraphicsLineItem(), m_opacity(1.0), m_dashOffset(0.0), m_direction(-1), m_hue(0)
{
    setLine(QLineF(x, 0, x, height));
    if (scene) {
        scene->addItem(this);
    }

    // 初始化虚线颜色样式
//    m_pen.setColor(QColor(0, 180, 255, static_cast<int>(m_opacity * 255))); // 炫蓝色 + 初始透明度

    QColor color = QColor::fromHsv(m_hue, 255, 255, static_cast<int>(m_opacity * 255));
    m_pen.setColor(color);
    m_pen.setWidth(2);
    m_pen.setStyle(Qt::DashLine);
    m_pen.setDashPattern({5, 5}); // dash pattern 更紧凑
    setPen(m_pen);
    setZValue(1000); // 确保绘制在最顶层

    // 启动动画定时器
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AlignIndicatorLine::updateEffect);
    m_timer->start(25); // per 50ms 刷新一次动画
}

AlignIndicatorLine::~AlignIndicatorLine() {
    if (scene()) {
        scene()->removeItem(this);
    }
}

void AlignIndicatorLine::updateEffect() {
    // 呼吸动画：透明度在 [0.5, 1.0] 之间循环变化
    m_opacity += 0.05 * m_direction;
    if (m_opacity <= 0.5) {
        m_opacity = 0.5;
        m_direction = 1;
    } else if (m_opacity >= 1.0) {
        m_opacity = 1.0;
        m_direction = -1;
    }

    // 游动动画：dash offset 在 [0, 10] 区间内循环
    m_dashOffset += 1.2;
    if (m_dashOffset > 10) {
        m_dashOffset = 0;
    }

//    QColor color = m_pen.color();
//    color.setAlphaF(m_opacity);

    // 彩色循环动画（HSV 色相轮）
    m_hue = (m_hue + 5) % 360;
    QColor color = QColor::fromHsv(m_hue, 255, 255, static_cast<int>(m_opacity * 255));

    m_pen.setColor(color);
    m_pen.setDashOffset(m_dashOffset);
    setPen(m_pen);
}
