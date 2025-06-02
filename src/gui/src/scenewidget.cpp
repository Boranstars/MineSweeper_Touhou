//
// Created by Boran on 25-6-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SceneWidget.h" resolved

#include "scenewidget.h"

#include "constants.h"


SceneWidget::SceneWidget(QWidget *parent) :
    QWidget(parent)  {

}

SceneWidget::~SceneWidget() {

}

void SceneWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    // painter.drawRect(0,0,GameObjectProperties::MineUnitProperties::SIZE,GameObjectProperties::MineUnitProperties::SIZE);
}

