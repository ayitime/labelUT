#ifndef ALIGNINDICATORLINE_H
#define ALIGNINDICATORLINE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QPen>
#include <QTimer>

/**
 * @brief 垂直对齐虚线类，支持呼吸透明度动画和 dash offset 游动动画。
 */
class AlignIndicatorLine : public QObject, public QGraphicsLineItem {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param x 对齐线的 x 坐标
     * @param height 当前视图的高度
     * @param scene 所属 QGraphicsScene
     * @param parent Qt 父对象指针
     */
    AlignIndicatorLine(double x, double height, QGraphicsScene* scene, QObject* parent = nullptr);
    ~AlignIndicatorLine();

private slots:
    /// 用于刷新动画特效
    void updateEffect();

private:
    QTimer* m_timer;
    QPen m_pen;
    qreal m_opacity;     ///< 当前透明度
    qreal m_dashOffset;  ///< 当前 dash offset 偏移
    int m_direction;     ///< 呼吸动画方向标记
    int m_hue;           ///< 当前颜色的 HSV 色相值（用于动态彩色）
};

#endif // ALIGNINDICATORLINE_H
