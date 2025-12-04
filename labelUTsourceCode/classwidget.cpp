#include "classwidget.h"
#include "ui_classwidget.h"

classWidget::classWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::classWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);        // 隐藏叉键
    connect(ui->listWidget, &QListWidget::itemClicked, [this](QListWidgetItem *item){
        if (item) {
            ui->lineEdit->setText(item->text());  // 将选中的类别填充到 lineEdit 中
        }
    });
}

classWidget::~classWidget()
{
    delete ui;
}

void classWidget::updateMiniListInfo(const QMap<QString, int>& map3) {
    for(QString cls: map3.keys()) {
        if(sets.find(cls) == sets.end()) {     // 新类别
            sets.insert(cls);
            classList.append(cls);
        }
    }

    // 将 classList 的元素填入 listWidget
    ui->listWidget->clear();  // 先清空原来的内容
    for (const QString& cls : classList) {
        QListWidgetItem* item = new QListWidgetItem(cls);
        ui->listWidget->addItem(item);
    }
}


void classWidget::on_yesButton_clicked()
{
    QString text = ui->lineEdit->text();
    emit rocketLaunch(text);
    close();
}

void classWidget::on_cancelButton_clicked()
{
    this->flag.clear();
    emit rocketFall();
    close();
}
