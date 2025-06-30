//
// Created by 杨博元 on 25-6-30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LostDialog.h" resolved

#include "lostdialog.h"

#include <ui_MainWindow.h>

#include "gameboard.h"
#include "ui_LostDialog.h"


LostDialog::LostDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LostDialog) {
    qDebug() << "Creating LostDialog";
    ui->setupUi(this);
    setWindowTitle(tr("踩到琪露诺了！"));
    ui->lostMessageLabel->setText(QString("铸币吧，怎么这么菜啊"));
    connect(ui->restartButton, &QPushButton::clicked, this, [=]() {
        emit restartRequested();
        accept();
    });
    connect(ui->exitGameButton, &QPushButton::clicked, this, [=]() {
        emit exitGameRequested();
        accept();
    });
}

LostDialog::~LostDialog() {
    delete ui;
    qDebug() << "LostDialog destroyed";
}
