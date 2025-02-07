#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);  // 开启鼠标追踪

    this->numOfPair = -1;
    this->imgId = -1;
    this->imageB = new QImage;
    this->imageC = new QImage;

    this->isDrawingRect = false;

    this->ui->graphicsView_Bscan->viewport()->installEventFilter(this);
    this->ui->graphicsView_Cscan->viewport()->installEventFilter(this);
//    this->ui->graphicsView_Bscan->viewport()->setMouseTracking(true);

    this->ui->graphicsView_Bscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->ui->graphicsView_Bscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    this->ui->graphicsView_Bscan->setInteractive(true);
//    this->ui->graphicsView_Cscan->setInteractive(true);
    this->ui->graphicsView_Cscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->ui->graphicsView_Cscan->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    connect(ui->fileListWidgetB, &QListWidget::itemDoubleClicked, this, &MainWindow::onImagePathItemDoubleClicked);
    connect(ui->fileListWidgetC, &QListWidget::itemDoubleClicked, this, &MainWindow::onImagePathItemDoubleClicked);
//    connect(currentRect, &RectangleItem::signalSetCursor, [this](){
//        setCursor(Qt::SizeAllCursor);
//    });


    // 右上角
    int flag = 1;
    QStringList categories1 = {"Bubble"};
    addCategoryCheckBoxes(ui->scrollArea_B, categories1);
    flag = 2;
    QStringList categories2 = {"Bubble", "Bubble", "Bubble"};
    addCategoryCheckBoxes(ui->scrollArea_C, categories2);

    addAdditionalInfo(ui->scrollArea_B);
    addAdditionalInfo(ui->scrollArea_C);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)       // 在这里面重新写按下的逻辑
{
    if(event->type() == QEvent::MouseButtonPress && obj == ui->graphicsView_Bscan->viewport()) {
        if (isDrawingRect) {
            qDebug() << "按下";
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            QPointF scenePos = ui->graphicsView_Bscan->mapToScene(mouseEvent->pos());  // 获取图像B区域的坐标
            startPos = scenePos;                                // 创建矩形框并设置起始点

            currentRect = new RectangleItem();
            sceneB->addItem(currentRect);                       // 添加矩形框到场景中
            currentRect->setRect(QRectF(startPos, startPos));   // 初始矩形为点
        }
        return true;
    }
    else if(event->type() == QEvent::MouseButtonPress && obj == ui->graphicsView_Cscan->viewport()) {
        if (isDrawingRect) {
            qDebug() << "按下";
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            QPointF scenePos = ui->graphicsView_Cscan->mapToScene(mouseEvent->pos());  // 获取图像B区域的坐标
            startPos = scenePos;                                // 创建矩形框并设置起始点

            currentRect = new RectangleItem();
            sceneC->addItem(currentRect);                       // 添加矩形框到场景中
            currentRect->setRect(QRectF(startPos, startPos));   // 初始矩形为点
        }
        return true;
    }
    else if (event->type() == QEvent::MouseMove && obj == ui->graphicsView_Bscan->viewport()) {
        if (isDrawingRect) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            QPointF endPos = ui->graphicsView_Bscan->mapToScene(mouseEvent->pos());
            QRectF rect(startPos, endPos);
            currentRect->setRect(rect);                 // 更新矩形框的大小

//            qDebug() << endPos;
        }
        return true;
    }
    else if (event->type() == QEvent::MouseMove && obj == ui->graphicsView_Cscan->viewport()) {
        if (isDrawingRect) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            QPointF endPos = ui->graphicsView_Cscan->mapToScene(mouseEvent->pos());
            QRectF rect(startPos, endPos);
            currentRect->setRect(rect);                 // 更新矩形框的大小

//            qDebug() << endPos;
        }
        return true;
    }

    else if(event->type() == QEvent::MouseButtonRelease && obj == ui->graphicsView_Bscan->viewport()) {

        if (isDrawingRect) {
            isDrawingRect = false;  // 结束绘制矩形模式
            qDebug() << "松开";
        }
        return true;
    }
    else if(event->type() == QEvent::MouseButtonRelease && obj == ui->graphicsView_Cscan->viewport()) {

        if (isDrawingRect) {
            isDrawingRect = false;  // 结束绘制矩形模式
            qDebug() << "松开";
        }
        return true;
    }

//    return QMainWindow::eventFilter(obj, event);
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onImagePathItemDoubleClicked(QListWidgetItem *item) {
    if(numOfPair != -1) {
        int indexB = ui->fileListWidgetB->row(item);
        int indexC = ui->fileListWidgetC->row(item);

        if(indexB==-1)         // 点的是C的列表
            imgId = indexC;
        else
            imgId = indexB;

        qDebug() << "click ImgID is: (" << imgId+1 << "/" << numOfPair << ")";
        this->updateImg();
    }
}

bool MainWindow::loadImage() {
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
        QMessageBox::warning(this, "warning", "Number of B/C Images is not equal");
        this->imgListC.clear();
        this->imgListB.clear();
        return false;
    }

    if(this->imgListB.size()==0) {
        QMessageBox::warning(this, "warning", "No B/C Image is found");
        return false;
    }
    this->numOfPair = imgListB.size();

    return true;
}

void MainWindow::updateImg() {
    sceneB = new QGraphicsScene();     // 能否复用？
    sceneC = new QGraphicsScene();
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

void MainWindow::resizeEvent(QResizeEvent* event)
{
    int padding = this->width() - ui->scrollAreaNavigator->width() - ui->fileListWidgetC->width() - 4*9;
    if(numOfPair != -1) {
    // 获取图像的宽度和高度
        int widthB = imageB->width();
        int heightB = imageB->height();
        int widthC = imageC->width();
        int heightC = imageC->height();

        // 如果宽度差异小于1个像素，统一宽度，否则使用最大宽度
        int width = qMax(widthB, widthC);  // 默认选择最大宽度

        // 设置 QGraphicsView 的大小，保持高度一致
        ui->graphicsView_Bscan->resize(padding, heightB+4);  // B扫区域
        ui->graphicsView_Cscan->resize(padding, heightC+4);  // C扫区域

    //    // 调整视图以适应新的大小，保持比例
    //    ui->graphicsView_Bscan->fitInView(sceneB->sceneRect(), Qt::KeepAspectRatio);
    //    ui->graphicsView_Cscan->fitInView(sceneC->sceneRect(), Qt::KeepAspectRatio);
        ui->graphicsView_Bscan->setRenderHint(QPainter::Antialiasing, true);
        ui->graphicsView_Bscan->centerOn(sceneB->itemsBoundingRect().center());  // 使图像水平居中
    }
}

void MainWindow::on_toolButton_OpenDir_clicked()
{
    this->imgPathB = QFileDialog::getExistingDirectory(this,
                                                     tr("select B-scan Image Dir"),
                                                     "../../dataset/Classes/bubbles",
                                                     QFileDialog::ShowDirsOnly);
    this->imgPathC = QFileDialog::getExistingDirectory(this,
                                                     tr("select C-scan Image Dir"),
                                                     "../../dataset/Classes/bubbles",
                                                     QFileDialog::ShowDirsOnly);
    if(imgPathB.isEmpty() || imgPathC.isEmpty()) {
        QMessageBox::warning(this, "warning", "B/C Path is Not selected, please try later");
        return;
    }

    // 加载图像路径
    bool flag = this->loadImage();

    // 显示图像
    if(flag) {
        this->imgId = 0;
        this->updateImg();
        qDebug() << "6666";

        for (const QString &path : imgListB) {
          this->ui->fileListWidgetB->addItem(path);  // 将路径添加到文件列表中
        }
        for (const QString &path : imgListC) {
          this->ui->fileListWidgetC->addItem(path);  // 将路径添加到文件列表中
        }
    }
}

void MainWindow::on_toolButton_13_clicked() {
    if(numOfPair == -1) {
        qDebug() << "Image is not loaded";
        return;
    }
    this->imgId++;
    if(imgId==numOfPair) {
        imgId--;
        return;
    }
    qDebug() << "ImgID: (" << imgId+1 << "/" << numOfPair << ")";
    this->updateImg();
    this->ui->fileListWidgetB->setCurrentRow(imgId);
    this->ui->fileListWidgetC->setCurrentRow(imgId);
}

void MainWindow::on_toolButton_10_clicked() {
    if(numOfPair == -1) {
        qDebug() << "Image is not loaded";
        return;
    }
    this->imgId--;
    if(imgId==-1) {
        imgId++;
        return;
    }
    qDebug() << "ImgID: (" << imgId+1 << "/" << numOfPair << ")";
    this->updateImg();
    this->ui->fileListWidgetB->setCurrentRow(imgId);
    this->ui->fileListWidgetC->setCurrentRow(imgId);
}

void MainWindow::on_toolButton_DrawRect_clicked() {       // 点击矩形按钮，进入绘制矩形模式
    this->isDrawingRect = true;  // 标记为绘制矩形模式
    this->startPos = QPointF();  // 清空起始位置

    qDebug() << "777";
}

void MainWindow::addCategoryCheckBoxes(QScrollArea *scrollArea, QStringList categories) {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 创建 QListWidget
    QListWidget *listWidget = new QListWidget();
    // 将类别信息添加到列表中，并设置为带有复选框的项
    for (const auto &category : categories) {
        QListWidgetItem *item = new QListWidgetItem(category);
        item->setCheckState(Qt::Unchecked);  // 默认为未选中状态
        listWidget->addItem(item);  // 添加到列表
    }

    // 将 QListWidget 添加到布局中
    layout->addWidget(listWidget);

    // ----------------------------------
    int len = categories.size();
    if(len==1) {
        QHBoxLayout *gateLayout1 = new QHBoxLayout();

        QLabel *gateLabel = new QLabel("gate-top:");
        gateLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        gateLayout1->addWidget(gateLabel);
        QLineEdit *gateHeight = new QLineEdit("197");  // 示例高度值
        gateHeight->setReadOnly(true);  // 只读
        gateHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        gateHeight->setFixedWidth(60);
        gateLayout1->addWidget(gateHeight);
        layout->addLayout(gateLayout1);

        QHBoxLayout *gateLayout2 = new QHBoxLayout();
        QLabel *gateBottomLabel = new QLabel("gate-bottom:");
        gateBottomLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        gateLayout2->addWidget(gateBottomLabel);
        QLineEdit *gateBottomHeight = new QLineEdit("240");  // 示例高度值
        gateBottomHeight->setReadOnly(true);  // 设置为只读
        gateBottomHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        gateBottomHeight->setFixedWidth(60);
        gateLayout2->addWidget(gateBottomHeight);
        layout->addLayout(gateLayout2);
    }
    else {
        QHBoxLayout *gateLayout1 = new QHBoxLayout();

        QLabel *gateLabel = new QLabel("axis-C:");
        gateLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        gateLayout1->addWidget(gateLabel);
        QLineEdit *gateHeight = new QLineEdit("143");  // 示例高度值
        gateHeight->setReadOnly(true);  // 只读
        gateHeight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        gateHeight->setFixedWidth(60);
        gateLayout1->addWidget(gateHeight);
        layout->addLayout(gateLayout1);
    }
    // ----------------------------------

    // 将布局设置为 QScrollArea 的内容
    scrollArea->setWidget(widget);
}

void MainWindow::addAdditionalInfo(QScrollArea *scrollArea) {

}

