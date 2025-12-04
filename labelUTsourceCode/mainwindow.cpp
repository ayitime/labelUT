#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);  // 开启鼠标追踪
//    enableMouseTrackingForChildren(this); // 递归开启鼠标追踪

    this->sceneB = new QGraphicsScene(this);
    this->sceneC = new QGraphicsScene(this);

    this->miniWindow = new classWidget;
    this->listWidgetB = nullptr;

    this->numOfPair = -1;
    this->imgId = -1;
    this->objectId = 0;
    this->classId = 0;
    this->imageB = new QImage;
    this->imageC = new QImage;

    this->isLoadImg = false;
    this->isDrawingRect = false;
    this->isRealStart = false;

    this->isDragging = false;
    this->draggedBox = nullptr;

    this->isResizing = false;
    this->draggedVertex = -1;

    this->selectBox = -1;

    this->alignedBtoC = false;
    this->alignedCtoB = false;
    this->lineB = nullptr;
    this->lineC = nullptr;

    this->gate = nullptr;
    this->hLine = nullptr;
    this->isShowGateLine = false;

    this->ui->graphicsView_Bscan->viewport()->installEventFilter(this);
    this->ui->graphicsView_Cscan->viewport()->installEventFilter(this);
    this->ui->graphicsView_Bscan->viewport()->setMouseTracking(true);
    this->ui->graphicsView_Cscan->viewport()->setMouseTracking(true);

    this->ui->graphicsView_Bscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->ui->graphicsView_Bscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    this->ui->graphicsView_Bscan->setInteractive(true);
    this->ui->graphicsView_Cscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->ui->graphicsView_Cscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    this->ui->graphicsView_Cscan->setInteractive(true);

//    // StatusBar底部状态栏
    this->mousePosLabel = new QLabel(this);
    ui->statusbar->addWidget(mousePosLabel);  // 固定在左下角

    connect(ui->fileListWidgetB, &QListWidget::itemDoubleClicked, this, &MainWindow::onImagePathItemDoubleClicked);
    connect(ui->fileListWidgetC, &QListWidget::itemDoubleClicked, this, &MainWindow::onImagePathItemDoubleClicked);

    // MenuBar-action
    connect(ui->actionOpen_Dir, &QAction::triggered, this, &MainWindow::on_toolButton_OpenDir_clicked);
    connect(ui->actionChange_Save_Dir, &QAction::triggered, this, &MainWindow::on_toolButton_ChangeSaveDir_clicked);
    connect(ui->actionQuit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionCreate_Box, &QAction::triggered, this, &MainWindow::on_toolButton_DrawRect_clicked);
    connect(ui->actionDelete_Box, &QAction::triggered, this, &MainWindow::on_toolButton_DeleteBox_clicked);
    connect(ui->actionabout_labelUT, &QAction::triggered, this, &MainWindow::onAboutLabelUT);


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {           // 通过定时器时刻更新图像的尺寸
        if(isLoadImg) {
            this->imageWidth = imageB->width();
            this->imageHeight = imageB->height();
            this->imageWidthC = imageC->width();
            this->imageHeightC = imageC->height();
        }

        const QString redSheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:red";
        const QString greenSheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:springgreen";

        if(isLoadImg)
            this->ui->imgLight_1->setStyleSheet(greenSheetStyle);
        else
            this->ui->imgLight_1->setStyleSheet(redSheetStyle);

        if(!labelPath.isEmpty())
            this->ui->txtLight_2->setStyleSheet(greenSheetStyle);
        else
            this->ui->txtLight_2->setStyleSheet(redSheetStyle);
    });
    timer->start(1000);

    // miniBox 输入类别的获取
    connect(miniWindow, &classWidget::rocketLaunch, [this](QString classStr){
        qDebug() << "(mainwindow.cpp) receive from miniwindow:" << classStr;
        if(classStr.isEmpty()) {       // 用户没有输入类别
            sceneB->removeItem(this->currentBox);
            sceneC->removeItem(this->currentBox);
            delete this->currentBox;
            this->currentBox = nullptr;
            return;
        }
        else if(classMap3.find(classStr)==classMap3.end()) {       // 新类别
            if(miniWindow->flag=="B") {
                this->classMap1[objectId] = classId;
                this->classMap2[objectId] = classStr;
            }
            else if(miniWindow->flag=="C") {
                this->classMap5[objectIdC] = classId;
                this->classMap6[objectIdC] = classStr;
            }
            this->classMap3[classStr] = classId;
            this->classMap4[classId] = classStr;

//            this->classesSet.insert(classStr);
            this->classesSet.append(classStr);
            this->classesCnt[classStr] = 1;
            classId++;
            qDebug() << classId;
        }
        else {          // 已有类别
            int tmp_classId = classMap3[classStr];
            if(miniWindow->flag=="B") {
                this->classMap1[objectId] = tmp_classId;
                this->classMap2[objectId] = classStr;
            }
            else if(miniWindow->flag=="C") {
                this->classMap5[objectIdC] = tmp_classId;
                this->classMap6[objectIdC] = classStr;
            }
            this->classMap3[classStr] = tmp_classId;
            this->classMap4[tmp_classId] = classStr;

            this->classesCnt[classStr]++;
        }

        if(miniWindow->flag=="B") {
            this->boxListBscan[objectId] = currentBox;
            this->objectId++;
        }
        else if(miniWindow->flag=="C") {
            this->boxListCscan[objectIdC] = currentBox;
            this->objectIdC++;
        }
        this->updateListInfo();     // 更新右侧class栏、更新miniWindow中下方候选的class列表
    });

    connect(miniWindow, &classWidget::rocketFall, [this](){
        qDebug() << "cancel draw box";
        if(miniWindow->flag=="B")
            sceneB->removeItem(this->currentBox);
        else if(miniWindow->flag=="C")
            sceneC->removeItem(this->currentBox);

        delete this->currentBox;
        this->currentBox = nullptr;
        return;
    });

    connect(ui->toolButton_DrawGate, &QPushButton::toggled, [this](bool checked){
        if(checked) {        // 按下
            if(this->isLoadImg) {
                this->isShowGateLine = true;
                this->loadJsonLabel();
            }
        }
        else {            // 抬起
            this->isShowGateLine = false;
            this->clearOldGates();
        }
    });

    addAdditionalInfo(ui->scrollArea_B);
    addAdditionalInfo(ui->scrollArea_C);
}

/// 鼠标状态捕捉
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if(!this->isLoadImg || this->labelPath.isEmpty())
        return false;       // false对应不拦截，继续传递

    // ================================== B-scan ==================================
    if (event->type() == QEvent::MouseButtonPress && obj == ui->graphicsView_Bscan->viewport()) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF curPos = ui->graphicsView_Bscan->mapToScene(mouseEvent->pos());  // 获取图像B区域的坐标

        // 交互1: 检查鼠标按下时，是否点击在某个矩形框内部
        bool isPressInsideBox = false;
        int i = 0;
        for (RectangleItem *box : boxListBscan.values()) {
            QRectF miniBox = box->rect().adjusted(3, 3, -3, -3);
            if (miniBox.contains(curPos)) {
                qDebug() << "[B-scan] box dragging";
                this->isDragging = true;
                this->draggedBox = box;
                this->lastMousePos = curPos;  // 记录起始拖动位置

                this->selectBox = i;
                for (RectangleItem *otherBox : boxListBscan)      // 取消其他box选中状态
                    otherBox->setSelected(false);
                box->setSelected(true);     // 选中当前 box
                isPressInsideBox = true;

                break;
            }
            i++;
        }
        if(!isPressInsideBox) {         // 点击其他地方则取消box选中
            qDebug() << "[B-scan] press is outside the box";
            for (RectangleItem *box : boxListBscan)
                box->setSelected(false);

            this->selectBox = -1;
        }
        // 更新 listWidget 的选中状态
        updateRightListSelection();

        // 交互2: 检查鼠标按下时，是否点击在某个矩形框的红点周围         isDragging 和 isResizing 切记不能同时为true
        if(!isDragging) {
            for (RectangleItem *box : boxListBscan.values()) {
                int vertexIndex = box->getHoveredVertex(curPos);
                if (vertexIndex != -1) {
                    this->isResizing = true;
                    this->draggedBox = box;
                    this->draggedVertex = vertexIndex;
                    this->lastMousePos = curPos;
                    break;
                }
            }
        }

        // 交互0: 绘制Box
        if (isDrawingRect) {
            qDebug() << "[B-scan] begin draw box";
            this->isRealStart = true;
            startPos = curPos;                                // 创建矩形框并设置起始点
            this->currentBox = new RectangleItem();
            currentBox->setZValue(1);
            sceneB->addItem(currentBox);                       // 添加矩形框到场景中
            currentBox->setRect(QRectF(startPos, startPos));   // 初始矩形为点
        }
        return false;
    }
    else if (event->type() == QEvent::MouseMove && obj == ui->graphicsView_Bscan->viewport()) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF curPos = ui->graphicsView_Bscan->mapToScene(mouseEvent->pos());

        // statusBar显示坐标
        this->mousePosLabel->setText(QString("[B-scan] x: %1, y: %2")
                               .arg(curPos.x(), 0, 'f', 1)
                               .arg(curPos.y(), 0, 'f', 1));

        // 交互0: 绘制Box
        if (isDrawingRect && isRealStart) {
            currentBox->setRect(QRectF(startPos, curPos));                 // 更新矩形框的大小
            return false;
        }

        // 交互1: 位于box内部光标切换
        bool cursorSetD = false;
        if (!isResizing) {
            bool isInsideBox = false;
            for (RectangleItem *box : boxListBscan.values()) {
                QRectF miniBox = box->rect().adjusted(3, 3, -3, -3);
                if (miniBox.contains(curPos)) {
                    ui->graphicsView_Bscan->setCursor(Qt::SizeAllCursor); // Dragging修改光标, 十字可拖动
                    cursorSetD = true;
                    isInsideBox = true;
                    break;
                }
            }
            if (!cursorSetD)
                ui->graphicsView_Bscan->unsetCursor(); // 恢复默认光标
        }

        if(!cursorSetD && !isDragging) {
            bool cursorSetR = false;
            for (RectangleItem *box: boxListBscan.values()) {        // 是否位于红点周围
                int vertexIndex = box->getHoveredVertex(curPos);
                if (vertexIndex != -1) {
                    ui->graphicsView_Bscan->setCursor(Qt::OpenHandCursor);
                    cursorSetR = true;
                    break;
                }
            }
            if (!cursorSetR)
                ui->graphicsView_Bscan->unsetCursor();
        }

        if (isDragging) {
            QPointF delta = curPos - lastMousePos;                  // 计算鼠标移动偏移量
            QRectF newRect = draggedBox->rect().translated(delta);  // 计算新位置

            // 限制矩形框不超出图像边界
            QRectF imageBounds(0, 0, imageWidth, imageHeight);
            if (imageBounds.contains(newRect)) {
                draggedBox->setRect(newRect);
                lastMousePos = curPos; // 更新鼠标位置
            }

            this->clearOldLines();      // 清理对齐交互的虚线
        }

        // 交互2: Resizing
        if (!isDragging){           // 交互1/2分离
            if (isResizing) {     // 处理拖动红点
                ui->graphicsView_Bscan->setCursor(Qt::ClosedHandCursor); // 改变光标形状
                QPointF delta = curPos - lastMousePos;
                lastMousePos = curPos;
                QRectF newRect = draggedBox->getAdjustedRect(draggedVertex, delta, imageWidth, imageHeight);

                // 交互代码
                int posX = getAlignedXfromCscan(curPos.x(), 1, 10);        // 10pix 以内启用吸附效果
                if (posX!=-1) {
                    if (draggedVertex == 0 || draggedVertex == 2) {
                        newRect.setLeft(posX);
                    } else {
                        newRect.setRight(posX);
                    }
                    this->drawAlignedVerticalLine(posX);
                    QPoint globalAlignedPos = ui->graphicsView_Bscan->mapToGlobal(QPoint(posX, curPos.y()));
//                    QCursor::setPos(globalAlignedPos);      // 瞬移!

                    qDebug() << "Catch!!";
                }
                else {
                    this->clearOldLines();
                    qDebug() << "not Catch";
                }

                draggedBox->setRect(newRect);
            }
        }
        return false;
    }
    else if (event->type() == QEvent::MouseButtonRelease && obj == ui->graphicsView_Bscan->viewport()) {
        if (isDragging) {
            qDebug() << "[B-scan] box stop dragging";
            isDragging = false;
            draggedBox = nullptr;
        }
        if (isResizing) {
            qDebug() << "[B-scan] box stop resizing";
            isResizing = false;
            draggedBox = nullptr;
            draggedVertex = -1;
        }
        if (isDrawingRect) {
            qDebug() << "[B-scan] drawing finish";
            this->isRealStart = false;
            this->isDrawingRect = false;  // 结束绘制矩形模式
            this->miniWindow->flag = "B";
            this->miniWindow->show();        // miniWindow获取box的class
        }
        return false;
    }

    // ================================== C-scan ==================================
    else if (event->type() == QEvent::MouseButtonPress && obj == ui->graphicsView_Cscan->viewport()) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF curPos = ui->graphicsView_Cscan->mapToScene(mouseEvent->pos());

        // 交互1: 检查鼠标按下时，是否点击在某个矩形框内部
        bool isPressInsideBox = false;
        int i = 0;
        for (RectangleItem *box : boxListCscan.values()) {
            QRectF miniBox = box->rect().adjusted(3, 3, -3, -3);
            if (miniBox.contains(curPos)) {
                qDebug() << "[C-scan] box dragging";
                this->isDragging = true;
                this->draggedBox = box;
                this->lastMousePos = curPos;

                this->selectBoxC = i;
                for (RectangleItem *otherBox : boxListCscan)
                    otherBox->setSelected(false);
                box->setSelected(true);
                isPressInsideBox = true;

                break;
            }
            i++;
        }
        if(!isPressInsideBox) {
            qDebug() << "[C-scan] press is outside the box";
            for (RectangleItem *box : boxListCscan)
                box->setSelected(false);

            this->selectBoxC = -1;
        }
        // 更新 listWidget 的选中状态
        updateRightListSelection();

        // 交互2: 检查鼠标按下时，是否点击在某个矩形框的红点周围         isDragging 和 isResizing 切记不能同时为true
        if(!isDragging) {
            for (RectangleItem *box : boxListCscan.values()) {
                int vertexIndex = box->getHoveredVertex(curPos);
                if (vertexIndex != -1) {
                    this->isResizing = true;
                    this->draggedBox = box;
                    this->draggedVertex = vertexIndex;
                    this->lastMousePos = curPos;
                    break;
                }
            }
        }

        // 交互0: 绘制Box
        if (isDrawingRect) {
            qDebug() << "[C-scan] begin draw box";
            this->isRealStart = true;
            startPos = curPos;
            this->currentBox = new RectangleItem();
            sceneC->addItem(currentBox);
            currentBox->setRect(QRectF(startPos, startPos));
        }
        return false;
    }
    else if (event->type() == QEvent::MouseMove && obj == ui->graphicsView_Cscan->viewport()) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF curPos = ui->graphicsView_Cscan->mapToScene(mouseEvent->pos());

        // statusBar显示坐标
        this->mousePosLabel->setText(QString("[C-scan] x: %1, y: %2")
                               .arg(curPos.x(), 0, 'f', 1)
                               .arg(curPos.y(), 0, 'f', 1));

        // 交互0: 绘制Box
        if (isDrawingRect && isRealStart) {
            currentBox->setRect(QRectF(startPos, curPos));
            return false;
        }

        // 交互1: 位于box内部光标切换
        bool cursorSetD = false;
        if (!isResizing) {
            bool isInsideBox = false;
            for (RectangleItem *box : boxListCscan.values()) {
                QRectF miniBox = box->rect().adjusted(3, 3, -3, -3);
                if (miniBox.contains(curPos)) {
                    ui->graphicsView_Cscan->setCursor(Qt::SizeAllCursor);
                    cursorSetD = true;
                    isInsideBox = true;
                    break;
                }
            }
            if (!cursorSetD)
                ui->graphicsView_Cscan->unsetCursor();
        }

        if(!cursorSetD && !isDragging) {

            bool cursorSetR = false;
            for (RectangleItem *box: boxListCscan.values()) {
                int vertexIndex = box->getHoveredVertex(curPos);
                if (vertexIndex != -1) {
                    ui->graphicsView_Cscan->setCursor(Qt::OpenHandCursor);
                    cursorSetR = true;
                    break;
                }
            }
            if (!cursorSetR)
                ui->graphicsView_Cscan->unsetCursor();
        }

        if (isDragging) {
            QPointF delta = curPos - lastMousePos;                  // 计算鼠标移动偏移量
            QRectF newRect = draggedBox->rect().translated(delta);  // 计算新位置

            // 限制矩形框不超出图像边界
            QRectF imageBounds(0, 0, imageWidthC, imageHeightC);
            if (imageBounds.contains(newRect)) {
                draggedBox->setRect(newRect);
                lastMousePos = curPos;
            }
            this->clearOldLines();      // 清理对齐交互的虚线
        }

        // 交互2: Resizing
        if (!isDragging){           // 交互1/2分离
            if (isResizing) {     // 处理拖动红点
                ui->graphicsView_Cscan->setCursor(Qt::ClosedHandCursor); // 改变光标形状
                QPointF delta = curPos - lastMousePos;
                lastMousePos = curPos;
                QRectF newRect = draggedBox->getAdjustedRect(draggedVertex, delta, imageWidth, imageHeight);

                // 添加代码
                int posX = getAlignedXfromCscan(curPos.x(), 0, 10);        // 10pix 以内启用吸附效果
                if (posX!=-1) {
                    if (draggedVertex == 0 || draggedVertex == 2) {
                        newRect.setLeft(posX);
                    } else {
                        newRect.setRight(posX);
                    }
                    this->drawAlignedVerticalLine(posX);
                    QPoint globalAlignedPos = ui->graphicsView_Cscan->mapToGlobal(QPoint(posX, curPos.y()));
                }
                else {
                    this->clearOldLines();
                }

                draggedBox->setRect(newRect);
            }
        }
        return false;
    }
    else if (event->type() == QEvent::MouseButtonRelease && obj == ui->graphicsView_Cscan->viewport()) {
        if (isDragging) {
            qDebug() << "[C-scan] box stop dragging";
            isDragging = false;
            draggedBox = nullptr;
        }
        if (isResizing) {
            qDebug() << "[C-scan] box stop resizing";
            isResizing = false;
            draggedBox = nullptr;
            draggedVertex = -1;
        }
        if (isDrawingRect) {
            qDebug() << "[C-scan] drawing finish";
            this->isRealStart = false;
            this->isDrawingRect = false;  // 结束绘制矩形模式
            this->miniWindow->flag = "C";
            this->miniWindow->show();        // miniWindow获取box的class
        }
        return false;
    }
//    return QMainWindow::eventFilter(obj, event);
    return false;
}

/// 窗口控件自适应调整
void MainWindow::resizeEvent(QResizeEvent* event)
{
    int padding = this->width() - ui->frameNavigator->width() - ui->fileListWidgetC->width() - 4*9;
    if(numOfPair != -1) {
        int fixedWidth = 500;

        // 获取图像的宽度和高度
        int widthB = imageB->width();
        int heightB = imageB->height();
        int widthC = imageC->width();
        int heightC = imageC->height();

        // 如果宽度差异小于1个像素，统一宽度，否则使用最大宽度
        int width = qMax(widthB, widthC);  // 默认选择最大宽度

        // 计算 B 扫和 C 扫的等比例缩放高度
        int scaledHeightB = (heightB * fixedWidth) / widthB;
        int scaledHeightC = (heightC * fixedWidth) / widthC;

        // 调整 QGraphicsView 的大小
        ui->graphicsView_Bscan->setFixedSize(fixedWidth, scaledHeightB + 10);
        ui->graphicsView_Cscan->setFixedSize(fixedWidth, scaledHeightC + 10);

        // 更新 scene 的大小，避免留白
        sceneB->setSceneRect(0, 0, width, heightB);
        sceneC->setSceneRect(0, 0, width, heightC);

        // 让图像适应 QGraphicsView
//        ui->graphicsView_Bscan->fitInView(sceneB->sceneRect(), Qt::KeepAspectRatio);
//        ui->graphicsView_Cscan->fitInView(sceneC->sceneRect(), Qt::KeepAspectRatio);

        // 手动触发布局刷新
//        if (ui->graphicsView_Bscan->parentWidget()->layout()) {
//            ui->graphicsView_Bscan->parentWidget()->layout()->update();
//            ui->graphicsView_Bscan->parentWidget()->layout()->activate();
//        }

        // 计算窗口的实际宽度
        int totalWidth = fixedWidth
                       + ui->frameNavigator->width()
                       + ui->fileListWidgetC->width()
                       + 4 * 9;  // 额外间距

        this->setFixedWidth(totalWidth);  // 固定宽度

        // 计算窗口的新高度 = B 扫 + C 扫 + 其他组件的高度
        int totalHeight = scaledHeightB + scaledHeightC
                + ui->label_3->height() + ui->label_4->height()
                + 60; // 额外的间距
    }
}

/// 键盘事件处理 (快捷键)
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_W)
        on_toolButton_DrawRect_clicked();

    else if (event->key() == Qt::Key_A)
        on_toolButton_BefImg_clicked();

    else if (event->key() == Qt::Key_D)
        on_toolButton_NextImg_clicked();

    else if (event->key() == Qt::Key_Delete)
        on_toolButton_DeleteBox_clicked();

    else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S)
        on_toolButton_Save_clicked();

    else
        QMainWindow::keyPressEvent(event);  // 默认处理
}

MainWindow::~MainWindow() {
    delete ui;
}

/// 递归开启所有子控件的MouseTracking
void MainWindow::enableMouseTrackingForChildren(QWidget *parent) {
    parent->setMouseTracking(true);
    for (QObject *child : parent->children()) {
        QWidget *widgetChild = qobject_cast<QWidget*>(child);
        if (widgetChild) {
            enableMouseTrackingForChildren(widgetChild);
        }
    }
}

/// 双击图像路径 快速切换图像
void MainWindow::onImagePathItemDoubleClicked(QListWidgetItem *item) {
    if(numOfPair != -1) {
        this->on_toolButton_Save_clicked();     // 在imgId更新前自动保存

        int indexB = ui->fileListWidgetB->row(item);
        int indexC = ui->fileListWidgetC->row(item);

        if(indexB==-1)         // 点的是C的列表
            imgId = indexC;
        else
            imgId = indexB;

        qDebug() << "click ImgID is: (" << imgId+1 << "/" << numOfPair << ")";
        this->updateImg();
        this->ui->fileListWidgetB->setCurrentRow(imgId);
        this->ui->fileListWidgetC->setCurrentRow(imgId);

        this->clearInfo();
        this->loadTxtLabel();

        this->updataRightListInfo();
        if(isShowGateLine) {
            this->loadJsonLabel();
        }
    }
}

/// 加载图像路径
bool MainWindow::loadImagePath() {
    // B-scan
    QDir dirB(this->imgPathB);
    dirB.setFilter(QDir::Files | QDir::NoDotAndDotDot);          // 设置过滤器，过滤出文件并排除 "." 和 ".."

    QStringList filters;                                         // 设置名称过滤器，匹配常见图像文件格式
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp" << "*.gif" << "*.tif" << "*.tiff";

    dirB.setNameFilters(filters);
    QStringList fileList = dirB.entryList();                     // 获取符合条件的文件名列表

    for (const QString& file : fileList) {
        this->imgListB.append(dirB.absoluteFilePath(file));
    }

    // C-scan
    QDir dirC = (this->imgPathC);
    dirC.setFilter(QDir::Files | QDir::NoDotAndDotDot);          // 设置过滤器，过滤出文件并排除 "." 和 ".."
    dirC.setNameFilters(filters);
    fileList = dirC.entryList();                     // 获取符合条件的文件名列表

    for (const QString& file : fileList) {
        this->imgListC.append(dirC.absoluteFilePath(file));
    }

    if(this->imgListC.size() != this->imgListB.size()) {
        QMessageBox::warning(this, "warning", "Number of B/C-scans is not equal");
        this->imgListC.clear();
        this->imgListB.clear();
        return false;
    }

    if(this->imgListB.size()==0) {
        QMessageBox::warning(this, "warning", "No B/C-scan image is found");
        return false;
    }
    this->numOfPair = imgListB.size();

    return true;
}

/// 加载并更新图像
void MainWindow::updateImg() {
    this->clearSceneBC();
    sceneB = new QGraphicsScene();     // 能否复用？
    sceneC = new QGraphicsScene();
//    sceneB->clear();
//    sceneC->clear();
    this->imageB->load(imgListB[this->imgId]);
    this->imageC->load(imgListC[this->imgId]);
    sceneB->addPixmap(QPixmap::fromImage(*imageB));
    sceneC->addPixmap(QPixmap::fromImage(*imageC));
    ui->graphicsView_Bscan->setScene(sceneB);
    ui->graphicsView_Cscan->setScene(sceneC);

//    ui->graphicsView_Bscan->resize(imageB->width() + 10, imageB->height() + 10);
//    ui->graphicsView_Cscan->resize(imageC->width() + 10, imageC->height() + 10);

    // 禁用滚动条，确保图像尺寸与视图一致
    ui->graphicsView_Bscan->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_Bscan->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_Cscan->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_Cscan->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 手动触发一次 resizeEvent
    QResizeEvent *event = new QResizeEvent(this->size(), this->size());
    resizeEvent(event);
}

/// 加载图像弹窗提示，获取文件夹路径 & 加载
void MainWindow::on_toolButton_OpenDir_clicked() {
    QString imgPathB_memo = this->imgPathB;
    QString imgPathC_memo = this->imgPathC;
    this->imgPathB = QFileDialog::getExistingDirectory(this,
                                                     tr("Select B-scan image dir"),
                                                     "../../dataset/Classes/bubbles",
                                                     QFileDialog::ShowDirsOnly);
    this->imgPathC = QFileDialog::getExistingDirectory(this,
                                                     tr("Select C-scan image dir"),
                                                     "../../dataset/Classes/bubbles",
                                                     QFileDialog::ShowDirsOnly);
    if(imgPathB.isEmpty() || imgPathC.isEmpty()) {
        if(!isLoadImg) {
            QMessageBox::warning(this, "warning", "Paired B/C-scan image is not load");
            return;
        }
        else{                       // 防止用户误点切换路径，之前已经成功加载了图像对
            this->imgPathB = imgPathB_memo;
            this->imgPathC = imgPathC_memo;
            return;
        }
    }

    // 加载图像路径
    this->isLoadImg = this->loadImagePath();

    // 显示图像
    if(isLoadImg) {
        this->imgId = 0;
        this->updateImg();
        qDebug() << "image pair load success";

        for (const QString &path : imgListB)
            this->ui->fileListWidgetB->addItem(path);  // 将路径添加到文件列表中
        for (const QString &path : imgListC)
            this->ui->fileListWidgetC->addItem(path);  // 将路径添加到文件列表中
    }
}

/// 设置label路径
void MainWindow::on_toolButton_ChangeSaveDir_clicked()
{
    if(!isLoadImg) {
        QMessageBox::warning(this, "warnning", "Please load paired images first");
        return;
    }
    QString labelPath_memo = this->labelPath;
    this->labelPath = QFileDialog::getExistingDirectory(this,
                                                        tr("select label Dir"),
                                                        "../../dataset/Classes/labels",
                                                        QFileDialog::ShowDirsOnly);
    if(this->labelPath.isEmpty() && !labelPath_memo.isEmpty()) {        // 放置用户误点切换路径
        this->labelPath = labelPath_memo;
        return;
    }
    this->labelPathB = this->labelPath + "/Bscan";
    this->labelPathC = this->labelPath + "/Cscan";
    QDir dirLabelBscan(this->labelPathB);
    QDir dirLabelCscan(this->labelPathC);
    if (!dirLabelBscan.exists()) {
        dirLabelBscan.mkpath(".");
        qDebug () << "[B-scan] Establishing label folder:" << labelPathB;
    }
    if (!dirLabelCscan.exists()) {
        dirLabelCscan.mkpath(".");
        qDebug () <<  "[C-scan] Establishing label folder:" << labelPathC;
    }

    // 检查是否存在classes.txt, 没有则创建classes.txt
    QString classTxtPath = this->labelPath + "/classes.txt";
    QFile file(classTxtPath);
    if (!file.exists()) {
        qDebug() << "classes.txt is not exist:" << classTxtPath;
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "classes.txt can not be establish:" << file.errorString();
            return;
        }
        file.close();
    }
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {       // 读取
        qDebug() << "classes.txt can not be read:" << file.errorString();
        return;
    }

    // 将本地classes.txt加载到 classesSet, classesCnt, classMap3 和 classMap4 中
    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();  // 读取一行，并去掉首尾空格
        qDebug() << line;
        if (!line.isEmpty()) {          // 忽略空行
//            classesSet.insert(line);    // 插入到 QSet

            QStringList parts = line.split(' ', QString::SkipEmptyParts);
            QString cls = parts[0];
            int num = parts[1].toInt();
            classesSet.append(cls);
            classesCnt[cls] = num;

            classMap3[cls] = row;
            classMap4[row] = cls;
            row++;
        }
    }
    this->classId = row;
    file.close();
    qDebug() << "classes.txt loading success:" << classesSet;

    // 尝试读取本地txt label文件
    this->loadTxtLabel();
    this->updateListInfo();     // 两个函数打包: 更新mainwindow右侧list, 更新miniwindow中的候选list

    // 检查是否存在存储gate/intersection 的BC_info.json文件, 没有则创建json
    QString jsonBCPath = this->labelPath + "/BC_info.json";
    QFile file2(jsonBCPath);
    if (!file2.exists()) {
        qDebug() << "BC_info.json is not exist:" << jsonBCPath;
        if (!file2.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "jsonBCPath.json can not be establish:" << file2.errorString();
            return;
        }
        // 写入gate和hLine进行初始化
        QJsonObject itemObj;
        itemObj["gate_top"] = imageHeight / 10;
        itemObj["gate_bot"] = imageHeight / 5;
        itemObj["lineC"] = imageHeightC / 8;
        QJsonObject rootObj;
        QString pairName = QDir(imgListB[imgId]).dirName().split(".")[0];
        rootObj[pairName] = itemObj;
        QJsonDocument saveDoc(rootObj);
        file2.write(saveDoc.toJson(QJsonDocument::Indented));

        file2.close();
    } else
        qDebug() << "jsonBCPath.json is exist";
}

/// 图像翻页 >>
void MainWindow::on_toolButton_NextImg_clicked() {
    if(numOfPair == -1) {
        qDebug() << "Image is not loaded";
        return;
    }
    this->on_toolButton_Save_clicked();     // 自动保存即将离开的内容

    this->imgId++;
    if(imgId==numOfPair) {
        imgId--;
        return;
    }
    qDebug() << "ImgID: (" << imgId+1 << "/" << numOfPair << ")";
    this->updateImg();
    this->ui->fileListWidgetB->setCurrentRow(imgId);        // 背景选中
    this->ui->fileListWidgetC->setCurrentRow(imgId);

    this->clearInfo();
    this->loadTxtLabel();
    this->updataRightListInfo();

    if(isShowGateLine)
        this->loadJsonLabel();
}

/// 图像翻页 <<
void MainWindow::on_toolButton_BefImg_clicked() {
    if(numOfPair == -1) {
        qDebug() << "Image is not loaded";
        return;
    }
    this->on_toolButton_Save_clicked();     // 自动保存即将离开的内容

    this->imgId--;
    if(imgId==-1) {
        imgId++;
        return;
    }
    qDebug() << "ImgID: (" << imgId+1 << "/" << numOfPair << ")";
    this->updateImg();
    this->ui->fileListWidgetB->setCurrentRow(imgId);
    this->ui->fileListWidgetC->setCurrentRow(imgId);

    this->clearInfo();
    this->loadTxtLabel();
    this->updataRightListInfo();

    if(isShowGateLine)
        this->loadJsonLabel();      // 加载下一对图像的gate内容
}

/// 清理scene放置内存爆炸，后续应优化为可复用
void MainWindow::clearSceneBC() {
    if (gate && gate->scene())
        gate->scene()->removeItem(gate);

    if (hLine && hLine->scene())
        hLine->scene()->removeItem(hLine);

    if (sceneB) {
        delete sceneB;
        sceneB = nullptr;
    }
    if (sceneC) {
        delete sceneC;
        sceneC = nullptr;
    }
}

/// 标注Box按钮
void MainWindow::on_toolButton_DrawRect_clicked() {
    if(!isLoadImg) {
//        QMessageBox::warning(this, "warning", "Paired B/C-scan image is not load");
        return;
    }
    if(labelPath.isEmpty()) {
//        QMessageBox::warning(this, "warnning", "Label save dir is not set");
        return;
    }

    this->isDrawingRect = true;  // 标记为绘制矩形模式
    this->startPos = QPointF();  // 清空起始位置
}

/// 更新 mainW 右侧 item 列表，更新 miniW 下方 item 列表
void MainWindow::updateListInfo() {
    this->updataRightListInfo();                  // 更新mainwindow 右侧 item 列表
    this->miniWindow->updateMiniListInfo(classMap3);        // 更新miniWindow中候选 class 列表
}

/// 更新 mainW 右侧 item 列表信息
void MainWindow::updataRightListInfo() {
    bool isFirstTime = true;
    if (!(this->listWidgetB && this->listWidgetC)) {
        this->listWidgetB = new QListWidget(this);  // 仅在 `nullptr` 时 `new`
        this->listWidgetC = new QListWidget(this);
        qDebug() << "listWidgetB & C has created";
    }
    else {
        this->listWidgetB->clear();  // 清空旧数据
        this->listWidgetC->clear();
        isFirstTime = false;
    }

    // ========================== B-scan ==========================
    {
        qDebug() << "[B-scan] label txt is loading to listWidgetB";
        // 将类别信息添加到列表中，并设置为带有复选框的项
        for (const auto &category : classMap2.values()) {
            qDebug() << "[B-scan] content is:" << category;
            QListWidgetItem *item = new QListWidgetItem(category);
            item->setCheckState(Qt::Unchecked);     // 默认为未选中状态
            this->listWidgetB->addItem(item);       // 添加到列表
        }
        // 确保 scrollArea 只设置一次 widget
        if (isFirstTime) {
            QWidget *widget = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(widget);
            layout->addWidget(listWidgetB);         // 添加到 layout
            widget->setLayout(layout);
            ui->scrollArea_B->setWidget(listWidgetB);
            ui->scrollArea_B->setWidgetResizable(true);   // 让列表随窗口调整大小
        }

        // 右侧listWidget点击后，box高亮交互
        connect(listWidgetB, &QListWidget::itemSelectionChanged, this, &MainWindow::listItemToBox);
    }

    // ========================== C-scan ==========================
    {
        qDebug() << "[C-scan] label txt is loading to listWidgetC";
        for (const auto &category : classMap6.values()) {
            qDebug() << "[C-scan] content is:" << category;
            QListWidgetItem *item = new QListWidgetItem(category);
            item->setCheckState(Qt::Unchecked);
            this->listWidgetC->addItem(item);
        }
        if (isFirstTime) {
            QWidget *widget = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(widget);
            layout->addWidget(listWidgetC);
            widget->setLayout(layout);
            ui->scrollArea_C->setWidget(listWidgetC);
            ui->scrollArea_C->setWidgetResizable(true);
        }
        connect(listWidgetC, &QListWidget::itemSelectionChanged, this, &MainWindow::listItemToBox);
    }

    // 将 QListWidget 添加到布局中
//    layout->addWidget(listWidget);

//    // ----------------------------------
//    int len = categories.size();
//    if(len==1) {
//        QHBoxLayout *gateLayout1 = new QHBoxLayout();

//        QLabel *gateLabel = new QLabel("gate-top:");
//        gateLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//        gateLayout1->addWidget(gateLabel);
//        QLineEdit *gateHeight = new QLineEdit("197");  // 示例高度值
//        gateHeight->setReadOnly(true);  // 只读
//        gateHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        gateHeight->setFixedWidth(60);
//        gateLayout1->addWidget(gateHeight);
//        layout->addLayout(gateLayout1);

//        QHBoxLayout *gateLayout2 = new QHBoxLayout();
//        QLabel *gateBottomLabel = new QLabel("gate-bottom:");
//        gateBottomLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//        gateLayout2->addWidget(gateBottomLabel);
//        QLineEdit *gateBottomHeight = new QLineEdit("240");  // 示例高度值
//        gateBottomHeight->setReadOnly(true);  // 设置为只读
//        gateBottomHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        gateBottomHeight->setFixedWidth(60);
//        gateLayout2->addWidget(gateBottomHeight);
//        layout->addLayout(gateLayout2);
//    }
//    else {
//        QHBoxLayout *gateLayout1 = new QHBoxLayout();

//        QLabel *gateLabel = new QLabel("axis-C:");
//        gateLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//        gateLayout1->addWidget(gateLabel);
//        QLineEdit *gateHeight = new QLineEdit("143");  // 示例高度值
//        gateHeight->setReadOnly(true);  // 只读
//        gateHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        gateHeight->setFixedWidth(60);
//        gateLayout1->addWidget(gateHeight);
//        layout->addLayout(gateLayout1);
//    }
//    // ----------------------------------

    // 将布局设置为 QScrollArea 的内容
//    scrollArea->setWidget(widget);
}

/// 更新 mainW 右侧 item 列表 的选中状态 (box交互效果)
void MainWindow::updateRightListSelection() {
    if (!(listWidgetB && listWidgetC)) return;

    listWidgetB->blockSignals(true);        // 临时禁用信号，防止 box点击 -> listItem选中-> 而触发 listItemToBox
    listWidgetC->blockSignals(true);

    for (int i=0; i<listWidgetB->count(); i++) {
        QListWidgetItem *item = listWidgetB->item(i);
        if (i == this->selectBox)
            item->setSelected(true);  // 选中 box 的 item
        else
            item->setSelected(false); // 取消 其他 item 选中
    }

    for (int i=0; i<listWidgetC->count(); i++) {
        QListWidgetItem *item = listWidgetC->item(i);
        if (i == this->selectBoxC)
            item->setSelected(true);  // 选中 box 的 item
        else
            item->setSelected(false); // 取消 其他 item 选中
    }

    listWidgetB->blockSignals(false);       // 重新启用信号
    listWidgetC->blockSignals(false);
}

/// item 列表 控制 box 的选中
void MainWindow::listItemToBox() {
    if (!(listWidgetB && listWidgetC)) return;

    QObject* obj = sender();  // 获取信号发送者
    if (obj == listWidgetB) {
        // ========================== B-scan ==========================
        QListWidgetItem *selectedItem = listWidgetB->currentItem();
        if (!selectedItem) {
            for (auto box : boxListBscan) {
                box->setSelected(false);
            }
            this->selectBox = -1;
            return;
        }

        int selectedIndex = listWidgetB->row(selectedItem);
        if (this->selectBox == selectedIndex) return;
        this->selectBox = selectedIndex;

        int i = 0;
        for (auto box : boxListBscan) {
            if (i == selectedIndex)
                box->setSelected(true);
            else
                box->setSelected(false);
            i++;
        }
    }
    else if (obj == listWidgetC) {
        // ========================== C-scan ==========================
        QListWidgetItem *selectedItem = listWidgetC->currentItem();
        if (!selectedItem) {
            // 如果没有选中的 item，取消所有 box 选中状态
            for (auto box : boxListCscan) {
                box->setSelected(false);
            }
            this->selectBox = -1;
            return;
        }

        // 获取选中的索引
        int selectedIndex = listWidgetC->row(selectedItem);
        if (this->selectBoxC == selectedIndex) return;
        this->selectBoxC = selectedIndex;

        // 更新 box 选中状态
        int i = 0;
        for (auto box : boxListCscan) {
            if (i == selectedIndex)
                box->setSelected(true);
            else
                box->setSelected(false);
            i++;
        }
    }
}

/// 保存标注信息
void MainWindow::on_toolButton_Save_clicked()
{
    if(imgPathB.isEmpty() || imgPathC.isEmpty()) {
        QMessageBox::warning(this, "warnning", "Paired B/C-scan image is not load");
        return;
    }
    if(labelPath.isEmpty()) {
        QMessageBox::warning(this, "warnning", "Label save dir is not set");
        return;
    }

    // ========================== B-scan ==========================
    {
        QString imgName = QDir(imgListB[imgId]).dirName().split(".")[0];      // 获取当前图像名称
        QString savePath = labelPathB + "/" + imgName + ".txt";
        qDebug() << "[B-scan] savePath is" << savePath;

        QFile file(savePath);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {  // 使用Truncate清空原文件
            qDebug() << "[B-scan] can't open file " << file.errorString();
            return;
        }
        QTextStream out(&file);

        // 保存为txt
        qDebug() << "[B-scan]";
        for(int key: classMap1.keys()) {
            int classLabel = classMap1[key];  // 获取类别
            QRectF rect = boxListBscan[key]->rect();  // 获取矩形框

            double x = rect.x();
            double y = rect.y();
            double w = rect.width();
            double h = rect.height();

            out << classLabel << " " << x << " " << y << " " << w << " " << h << "\n";

            qDebug() << "    Class:" << classLabel << "BBox:" << x << y << w << h;
        }
        file.close();
        qDebug() << "[B-scan] data save success:" << savePath;
    }

    // ========================== C-scan ==========================
    {
        QString imgName = QDir(imgListC[imgId]).dirName().split(".")[0];      // 获取当前图像名称
        QString savePath = labelPathC + "/" + imgName + ".txt";
        qDebug() << "[C-scan] savePath is" << savePath;

        QFile file(savePath);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {  // 使用Truncate清空原文件
            qDebug() << "[C-scan] can't open file " << file.errorString();
            return;
        }
        QTextStream out(&file);

        // 保存为txt
        qDebug() << "[C-scan]";
        for(int key: classMap5.keys()) {
            int classLabel = classMap5[key];  // 获取类别
            QRectF rect = boxListCscan[key]->rect();  // 获取矩形框

            double x = rect.x();
            double y = rect.y();
            double w = rect.width();
            double h = rect.height();

            out << classLabel << " " << x << " " << y << " " << w << " " << h << "\n";

            qDebug() << "    Class:" << classLabel << ", BBox:" << x << y << w << h;
        }
        file.close();
        qDebug() << "[C-scan] label txt data save success:" << savePath;
    }

    // 类别保存为classes.txt
    QString classTxtPath = this->labelPath + "/classes.txt";
    QFile file2(classTxtPath);

    if (!file2.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {  // 以覆盖写入模式打开
        qDebug() << "classes.txt can not be opened" << file2.errorString();
        return;
    }
    QTextStream out2(&file2);
    for (const QString &cls : classesSet) {
        out2 << cls << ' ' << classesCnt[cls] << "\n";  // 逐行写入类别
    }
//    file2.seek(0);
    qDebug() << "classes.txt write success";
    file2.close();


    // ========================== 保存闸门/交线信息 ==========================
    {
        if(!(gate && hLine)) {
            qDebug() << "Gate and intersection line is nullptr";
            return;
        }
        QString pairName = QDir(imgListB[imgId]).dirName().split(".")[0];

        //  B-scan
        int gateTop = gate->topBoundary();
        int gateBottom = gate->bottomBoundary();

        // C-scan
        int intersectionLine = hLine->getPosY();

        // 创建当前项的对象
        QJsonObject itemObj;
        itemObj["gate_top"] = gateTop;
        itemObj["gate_bot"] = gateBottom;
        itemObj["lineC"] = intersectionLine;

        // 如果 JSON 文件存在，则加载
        QString jsonBCPath = this->labelPath + "/BC_info.json";
        QJsonObject rootObj;
        QFile file(jsonBCPath);
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QByteArray data = file.readAll();
                file.close();

                QJsonParseError parseError;
                QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
                if (parseError.error == QJsonParseError::NoError && doc.isObject()) {
                    rootObj = doc.object();
                } else {
                    qDebug() << "Failed to parse JSON:" << parseError.errorString();
                }
            }
        }
        rootObj[pairName] = itemObj;

        QJsonDocument saveDoc(rootObj);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            file.write(saveDoc.toJson(QJsonDocument::Indented));
            file.close();
            qDebug() << "Saved JSON info for" << pairName;
        } else {
            qDebug() << "Failed to open file for writing:" << jsonBCPath;
        }
    }
}

/// 翻页时清空缓存
void MainWindow::clearInfo() {
    this->boxListBscan.clear();
    this->classMap1.clear();
    this->classMap2.clear();
    this->objectId = 0;
    this->selectBox = -1;
    this->draggedVertex = -1;

    this->boxListCscan.clear();
    this->classMap5.clear();
    this->classMap6.clear();
    this->objectIdC = 0;
    this->selectBoxC = -1;

    this->isDrawingRect = false;
    this->isRealStart = false;
    this->isDragging = false;
    this->isResizing = false;

    this->updataRightListInfo();      // 清空右侧列表中 item
}

/// 将label(txt)中的box加载到classMap1和classMap2中，并绘制box
void MainWindow::loadTxtLabel() {
    if(!isLoadImg)
        return;

    // ========================== B-scan ==========================
    {
        QString imgName = QDir(imgListB[imgId]).dirName().split(".")[0];      // 获取当前图像名称
        QString txtPath = labelPathB + "/" + imgName + ".txt";

        QFile file(txtPath);
        if(!file.exists()) {
            qDebug() << "[B-scan] label txt not exist:" << txtPath;
            return;
        }
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "[B-scan] label txt can not open:" << txtPath;
            return ;
        }
        qDebug() << "[B-scan] label txt is open success:" << txtPath;

        // 加载txt标签
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();     // 读取一行并去除首尾空格
            if (line.isEmpty()) continue;               // 跳过空行
            QStringList parts = line.split(QRegExp("\\s+"));  // 按空格或制表符分割
            if (parts.size() != 5) {
                qDebug() << "[B-scan] label txt Format erros" << line;
                continue;
            }

            int cls = parts[0].toInt();
            QVector<double> box;
            for (int i = 1; i < 5; ++i) {
                box.append(parts[i].toDouble());
            }

            qDebug() << "[B-scan] label txt content is:" << cls << box;
            classMap1[objectId] = cls;
            classMap2[objectId] = classMap4[cls];
            // 创建新的 RectangleItem 并添加到 boxListBscan
            RectangleItem *newBox = new RectangleItem();
            newBox->setRect(QRectF(box[0], box[1], box[2], box[3]));

    //        newBox->setPen(QPen(Qt::red, 2));  // 红色边框
    //        newBox->setBrush(QBrush(QColor(255, 0, 0, 50)));  // 半透明红色填充
            boxListBscan[objectId] = newBox;
            sceneB->addItem(newBox);  // 添加到场景中

            boxListBscan[objectId] = newBox;

            objectId++;
        }
        file.close();
    }

    // ========================== C-scan ==========================
    {
        QString imgName = QDir(imgListC[imgId]).dirName().split(".")[0];      // 获取当前图像名称
        QString txtPath = labelPathC + "/" + imgName + ".txt";

        QFile fileC(txtPath);
        if(!fileC.exists()) {
            qDebug() << "[C-scan] label txt not exist:" << txtPath;
            return;
        }
        if (!fileC.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "[C-scan] label txt can not open:" << txtPath;
            return ;
        }
        qDebug() << "[C-scan] label txt is open success:" << txtPath;

        // 加载txt标签
        QTextStream inC(&fileC);
        int row = 0;
        while (!inC.atEnd()) {
            QString line = inC.readLine().trimmed();     // 读取一行并去除首尾空格
            if (line.isEmpty()) continue;               // 跳过空行
            QStringList parts = line.split(QRegExp("\\s+"));  // 按空格或制表符分割
            if (parts.size() != 5) {
                qDebug() << "[C-scan] label txt Format erros" << line;
                continue;
            }

            int cls = parts[0].toInt();
            QVector<double> box;
            for (int i = 1; i < 5; ++i) {
                box.append(parts[i].toDouble());
            }

            qDebug() << "[C-scan] label txt content is:" << cls << box;
            classMap5[objectIdC] = cls;
            classMap6[objectIdC] = classMap4[cls];

            RectangleItem *newBox = new RectangleItem();
            newBox->setRect(QRectF(box[0], box[1], box[2], box[3]));

            boxListCscan[objectIdC] = newBox;
            sceneC->addItem(newBox);  // 添加到场景中
            boxListCscan[objectIdC] = newBox;

            objectIdC++;
        }
        fileC.close();
    }
}

/// 删除box，更新缓存
void MainWindow::on_toolButton_DeleteBox_clicked()
{
    if(numOfPair == -1) {
        qDebug() << "Image is not loaded";
        return;
    }

    if(selectBox==-1 && selectBoxC==-1) {
        qDebug() << "no box is selected";
        return;
    }

    // ========================== B-scan ==========================
    if(selectBox!=-1)
    {
        QString cls = classMap2[selectBox];
        int num = classesCnt[cls];
        if(num == 1) {
//            classesSet.remove(cls);
            int index = classesSet.indexOf(cls);
            classesSet.removeAt(index);
            classesCnt.remove(cls);

            int cls_id = classMap3[cls];
            classMap3.remove(cls);
            classMap4.remove(cls_id);
        }
        else
            classesCnt[cls]--;

        this->classMap1.remove(selectBox);      // 修改
        this->classMap2.remove(selectBox);
    }
    else if(selectBoxC!=-1) {
        QString cls = classMap6[selectBoxC];
        int num = classesCnt[cls];
        if(num == 1) {
//            classesSet.remove(cls);
            int index = classesSet.indexOf(cls);
            classesSet.removeAt(index);
            classesCnt.remove(cls);

            int cls_id = classMap3[cls];
            classMap3.remove(cls);
            classMap4.remove(cls_id);
        }
        else
            classesCnt[cls]--;

        this->classMap5.remove(selectBoxC);      // 修改
        this->classMap6.remove(selectBoxC);
    }

    qDebug() << "-------------------";
    qDebug() << "    map3 is:" << classMap3;
    qDebug() << "    map4 is:" << classMap4;
    qDebug() << "    set is:" << classesSet;
    qDebug() << "    cnt is:" << classesCnt;
    qDebug() << "-------------------";

    this->on_toolButton_Save_clicked();     // 保存txt

    this->clearInfo();                      // 清空缓存
    this->updateImg();                      // 更新画面

    this->loadTxtLabel();                   // 重新加载txt
    this->loadJsonLabel();                  // 重新加载json (误杀)
    this->updateListInfo();                 // 更新右侧list和miniWindow的list
}

/// 两模态间在横向的对齐感知判断
int MainWindow::getAlignedXfromCscan(double posX, bool flag, int threshold) {
    // flag is true -> B-scan, flag is false -> C-scan
    if(flag) {
        for (const RectangleItem* box : boxListCscan) {
            const QRectF rect = box->rect();
            double left = rect.left();
            double right = rect.right();

            if (qAbs(posX - left) < threshold)
                return static_cast<int>(left);
            if (qAbs(posX - right) < threshold)
                return static_cast<int>(right);
        }
        return -1;
    }
    else {
        for (const RectangleItem* box : boxListBscan) {
            const QRectF rect = box->rect();
            double left = rect.left();
            double right = rect.right();

            if (qAbs(posX - left) < threshold)
                return static_cast<int>(left);
            if (qAbs(posX - right) < threshold)
                return static_cast<int>(right);
        }
        return -1;
    }
}

/// 对齐感知——画虚线条
void MainWindow::drawAlignedVerticalLine(double alignedX) {
    clearOldLines();        // 清理上一帧的线

    lineB = new AlignIndicatorLine(alignedX, sceneB->sceneRect().height(), sceneB, this);
    lineC = new AlignIndicatorLine(alignedX, sceneC->sceneRect().height(), sceneC, this);
}

/// 对齐感知——清除线条
void MainWindow::clearOldLines() {
    if (lineB) {
        sceneB->removeItem(lineB);
        delete lineB;
        lineB = nullptr;
    }
    if (lineC) {
        sceneC->removeItem(lineC);
        delete lineC;
        lineC = nullptr;
    }
}

///// 绘制闸门/交线信息
//void MainWindow::on_toolButton_DrawGate_clicked()
//{
//    if(!isLoadImg) {
////        QMessageBox::warning(this, "warning", "Paired B/C-scan image is not load");
//        return;
//    }
//    if(labelPath.isEmpty()) {
////        QMessageBox::warning(this, "warnning", "Label save dir is not set");
//        return;
//    }

//    // ========================== B-scan ==========================
//    int gateTop = imageHeight / 4;
//    int gateBottom = imageHeight / 2;

//    QRectF gateRect(0, gateTop, imageWidth, gateBottom - gateTop);

//    this->gate = new GateOverlay(gateRect, 0, imageHeight, sceneB);
//    gate->setZValue(0);  // 设置较低层级
//    this->sceneB->addItem(gate);

//    // ========================== C-scan ==========================
//    qreal initialY = imageHeightC / 5;
//    this->hLine = new DraggableHLineItem(initialY, imageWidthC, imageHeightC, sceneC);

//    QPen customPen(Qt::blue);
//    customPen.setWidth(4);
//    customPen.setStyle(Qt::CustomDashLine);
//    hLine->setPen(customPen);
//    hLine->setDashPattern({1, 2});

//    sceneC->addItem(hLine);
//}

/// 读取json文件至 gate 和 hLine 中，并绘制闸门和交线
void MainWindow::loadJsonLabel() {
    this->clearOldGates();        // 清理之前的闸门绘制

    QString jsonBCPath = this->labelPath + "/BC_info.json";
    QString pairName = QDir(imgListB[imgId]).dirName().split(".")[0];

    QFile file(jsonBCPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open JSON file:" << jsonBCPath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return;
    }

    int gateTop;
    int gateBot;
    int lineC_posY;
    QJsonObject rootObj = doc.object();
    if (!rootObj.contains(pairName)) {      // json中是否存在该key值
        qDebug() << "No label found for pair:" << pairName;
        // 初始化
        gateTop = imageHeight / 10;
        gateBot = imageHeight / 5;
        lineC_posY = imageHeightC / 8;
    }
    else {
        QJsonObject valueObj = rootObj.value(pairName).toObject();
        gateTop = valueObj.value("gate_top").toInt();
        gateBot = valueObj.value("gate_bot").toInt();
        lineC_posY = valueObj.value("lineC").toInt();
    }

    // ========================== 绘制 Gate ==========================
    QRectF gateRect(0, gateTop, imageWidth, gateBot - gateTop);
    this->gate = new GateOverlay(gateRect, 0, imageHeight, sceneB);

    // ======================== 绘制 HLine =======================
    this->hLine = new DraggableHLineItem(lineC_posY, imageWidthC, imageHeightC, sceneC);
    QPen customPen(Qt::blue);
    customPen.setWidth(4);
    customPen.setStyle(Qt::CustomDashLine);
    hLine->setPen(customPen);
    hLine->setDashPattern({1, 2});

    qDebug() << "Loaded gate and lineC for pair:" << pairName;
}

/// 清理闸门/交线
void MainWindow::clearOldGates() {
    if (gate) {
        delete gate;
        gate = nullptr;
    }
    if (hLine) {
        delete hLine;
        hLine = nullptr;
    }
}

/// 软件关于
void MainWindow::onAboutLabelUT() {
    QDialog aboutDialog(this);
    aboutDialog.setWindowTitle("About LabelUT");

//    aboutDialog.setFixedSize(400, 300);
    aboutDialog.setMinimumSize(400, 300);
    aboutDialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout* layout = new QVBoxLayout(&aboutDialog);
    layout->setSpacing(8); // 控件间距
    layout->setContentsMargins(15, 10, 15, 10); // 四周边距

    QLabel* titleLabel = new QLabel("<b>LabelUT - Ultrasonic Labeling Tool</b>");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Segoe UI", 11));

    // 信息文本 + GitHub链接（居中）
    QLabel* infoLabel = new QLabel(
        "Version: 1.0.0<br>"
        "Author: ayitime<br><br>"
        "This tool is designed for labeling phased array ultrasonic testing (PAUT) B-scan and C-scan images, "
        "supporting dual-view annotations and gate visualization.");

    infoLabel->setTextFormat(Qt::RichText);
    infoLabel->setWordWrap(true);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setFont(QFont("Segoe UI", 10));

    // GitHub LOGO
    QLabel* iconLabel = new QLabel;
    QPixmap iconPixmap(":/icons/github9775.png");  // 替换为你的资源路径
    iconLabel->setPixmap(iconPixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignCenter);

    QLabel* linkGithub = new QLabel("<a href='https://github.com/ayitime/labelUT'>GitHub Repository</a><br>");
    linkGithub->setTextFormat(Qt::RichText);
    linkGithub->setOpenExternalLinks(true);
    linkGithub->setWordWrap(true);
    linkGithub->setAlignment(Qt::AlignCenter);
    linkGithub->setFont(QFont("Segoe UI", 10));

    QPushButton* closeBtn = new QPushButton("Close");
    closeBtn->setFont(QFont("Segoe UI", 10));
    connect(closeBtn, &QPushButton::clicked, &aboutDialog, &QDialog::accept);

    layout->addWidget(titleLabel);
    layout->addWidget(infoLabel);
    layout->addWidget(iconLabel);
    layout->addWidget(linkGithub);

    layout->addStretch();
    layout->addWidget(closeBtn, 0, Qt::AlignCenter);

    aboutDialog.exec();  // 模态弹窗
}


///
void MainWindow::addAdditionalInfo(QScrollArea *scrollArea) {

}
