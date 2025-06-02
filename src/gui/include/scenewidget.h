//
// Created by Boran on 25-6-1.
//

#ifndef SCENCEWIDGET_H
#define SCENCEWIDGET_H

#include <QWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class SceneWidget; }
QT_END_NAMESPACE

class SceneWidget : public QWidget {
Q_OBJECT

public:
    explicit SceneWidget(QWidget *parent = nullptr);
    ~SceneWidget() override;

protected:
void paintEvent(QPaintEvent* event) override;

private:
    Ui::SceneWidget *ui;
};


#endif //SCENCEWIDGET_H
