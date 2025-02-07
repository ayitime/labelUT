#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QScrollArea>
#include <QCheckBox>
#include <QDebug>
#include <QLineEdit>
#include "rectangleitem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadImage();
    void updateImg();
    void addCategoryCheckBoxes(QScrollArea *scrollArea, QStringList categories);        // 右上角静态装饰
    void addAdditionalInfo(QScrollArea *scrollArea);

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_toolButton_OpenDir_clicked();

    void on_toolButton_13_clicked();

    void on_toolButton_10_clicked();

    void onImagePathItemDoubleClicked(QListWidgetItem *item);

    void on_toolButton_DrawRect_clicked();  // 用于进入矩形绘制模式

protected:
    void resizeEvent(QResizeEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;


private:
    Ui::MainWindow *ui;

    QString imgPathB;
    QString imgPathC;
    QString labelPathB;
    QString labelPathC;

    int numOfPair;
    int imgId;

    QVector<QString> imgListB;
    QVector<QString> imgListC;

    QImage* imageB;
    QImage* imageC;

    QGraphicsScene* sceneB;
    QGraphicsScene* sceneC;

    QGraphicsPixmapItem* itemB;
    QGraphicsPixmapItem* itemC;

    bool isDrawingRect;
    QPointF startPos;
    RectangleItem *currentRect;  // 当前绘制的矩形

};
#endif // MAINWINDOW_H
