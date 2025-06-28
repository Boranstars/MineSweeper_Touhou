//
// Created by Boran on 25-6-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SceneWidget.h" resolved

#include "scenewidget.h"

#include "constants.h"

using namespace MineSweeperTouHou;
SceneWidget::SceneWidget(QWidget *parent) :
    QWidget(parent)  {

}

SceneWidget::~SceneWidget() {

}

void SceneWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    for (int i = 0; i < gameboard->getRows(); ++i) {
        for (int j = 0; j < gameboard->getCols(); ++j) {
            const MineUnit& unit =gameboard->getUnitAt(i, j);
            QPixmap pix;
            int x = GameObjectProperties::SceneProperties::MARGIN + GameObjectProperties::MineUnitProperties::SIZE * i;
            int y = GameObjectProperties::SceneProperties::MARGIN + GameObjectProperties::MineUnitProperties::SIZE * j;


            // TODO 使用槽函数结合GameBoard的信号来更新UI界面
            if (unit.getUnitType() == UnitType::EMPTY) {
                pix = ResourceLoader::getCoverImage();
                painter.drawPixmap(x, y, pix);
                continue;
            }


            if (unit.isCovered()) {
                pix = ResourceLoader::getCoverImage();
                painter.drawPixmap(x, y, pix);
                continue;
            }

            painter.drawPixmap(x, y, ResourceLoader::getUncoverImage());

            if (unit.getUnitType() == UnitType::NUMBER) {
                pix = ResourceLoader::getNumberImage(unit.getNumber());
                qDebug() << unit.getNumber();
            } else if (unit.getUnitType() == UnitType::MINE) {
                pix = ResourceLoader::getMineImage();
            }

            painter.drawPixmap(x, y, pix);




        }
    }
}

void SceneWidget::setGameboard(MineSweeperTouHou::GameBoard *gameboard) {
    this->gameboard = gameboard;
}

