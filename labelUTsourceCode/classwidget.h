#ifndef CLASSWIDGET_H
#define CLASSWIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class classWidget;
}

class classWidget : public QWidget
{
    Q_OBJECT

public:
    explicit classWidget(QWidget *parent = nullptr);
    ~classWidget();

    void updateMiniListInfo(const QMap<QString, int>& map3);
    QString flag;

private slots:
    void on_yesButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::classWidget *ui;
    QVector<QString> classList;
    QSet<QString> sets;

signals:
    void rocketLaunch(QString input);
    void rocketFall();
};

#endif // CLASSWIDGET_H
