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
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPushButton>

#include "rectangleitem.h"
#include "classwidget.h"
#include "alignindicatorline.h"
#include "gateoverlay.h"
#include "DraggableHLineItem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadImagePath();
    void updateImg();
    void clearSceneBC();
    void updataRightListInfo();

    void enableMouseTrackingForChildren(QWidget *parent);
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void updateListInfo();
    void updateRightListSelection();
    void clearInfo();
    void loadTxtLabel();
    void loadJsonLabel();
    void loadBox();

    void addAdditionalInfo(QScrollArea *scrollArea);

private slots:
    void on_toolButton_OpenDir_clicked();

    void on_toolButton_NextImg_clicked();

    void on_toolButton_BefImg_clicked();

    void onImagePathItemDoubleClicked(QListWidgetItem *item);

    void on_toolButton_DrawRect_clicked();  // 用于进入矩形绘制模式

    void on_toolButton_Save_clicked();

    void on_toolButton_ChangeSaveDir_clicked();

    void listItemToBox();       // listWidget 点击后 选中 box

    void on_toolButton_DeleteBox_clicked();

//    void on_toolButton_DrawGate_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    classWidget* miniWindow;
    QListWidget* listWidgetB;
    QListWidget* listWidgetC;

    QString imgPathB;
    QString imgPathC;
    QString labelPath;
    QString labelPathB;
    QString labelPathC;

    int numOfPair;              // 文件夹中配 图像对 数量
    int imgId;                  // 第 imgId 对

    QVector<QString> imgListB;
    QVector<QString> imgListC;

    QImage* imageB;
    QImage* imageC;

    QGraphicsScene* sceneB;
    QGraphicsScene* sceneC;

    QGraphicsPixmapItem* itemB;
    QGraphicsPixmapItem* itemC;

    int imageWidth;
    int imageHeight;
    int imageWidthC;
    int imageHeightC;

    bool isLoadImg;
    bool isDrawingRect;         // 左侧createRect按键被按下
    bool isRealStart;           // 开始绘制box

    bool isDragging;            // 是否拖动box
    RectangleItem *draggedBox;  // 当前拖动的box指针
    QPointF lastMousePos;       // 上一时刻鼠标位置

    bool isResizing;
    int draggedVertex;

    int selectBox;

    QPointF startPos;
    RectangleItem* currentBox;                    // 当前绘制的矩形

    QMap<int, RectangleItem*> boxListBscan;       // 仅保留当前图像中标注的box, objectId-box
    QMap<int, RectangleItem*> boxListCscan;

//    QSet<QString> classesSet;
    QList<QString> classesSet;
    QMap<QString, int> classesCnt;   // 配合classesSet计数用，若某一类别数量为0则剔除

    int classId;                     // 类别编号 递增
    int objectId;                    // 目标编号 递增
    QMap<int, int> classMap1;        // objectId-classId
    QMap<int, QString> classMap2;    // objectId-class(string)

    QMap<QString, int> classMap3;    // class(string)-classId       用于miniWindow下方的提示Class
    QMap<int, QString> classMap4;    // classId-class(string)

    // ------- C-scan -------
    int selectBoxC;
    int objectIdC;
    QMap<int, int> classMap5;        // 对应于classMap1
    QMap<int, QString> classMap6;    // 对应于classMap2

    // align
    bool alignedBtoC;
    bool alignedCtoB;
    AlignIndicatorLine* lineB;
    AlignIndicatorLine* lineC;
    int getAlignedXfromCscan(double posX, bool flag, int threshold);
    void drawAlignedVerticalLine(double alignedX);
    void clearOldLines();

    // gate
    GateOverlay* gate;
    DraggableHLineItem* hLine;
    bool isShowGateLine;
    void clearOldGates();

    void onAboutLabelUT();

    // statusbar
    QLabel* mousePosLabel = nullptr;
};
#endif // MAINWINDOW_H
