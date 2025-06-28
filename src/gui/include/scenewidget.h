//
// Created by Boran on 25-6-1.
//

#ifndef SCENCEWIDGET_H
#define SCENCEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "resourceloader.h"
#include "gameboard.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SceneWidget; }
QT_END_NAMESPACE

class SceneWidget : public QWidget {
Q_OBJECT

public:
    explicit SceneWidget(QWidget *parent = nullptr);
    ~SceneWidget() override;

public:


protected:
void paintEvent(QPaintEvent* event) override;
void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::SceneWidget *ui;
    MineSweeperTouHou::GameBoard *gameboard = nullptr;

public:
    void setGameboard(MineSweeperTouHou::GameBoard *gameboard);
};


#endif //SCENCEWIDGET_H
