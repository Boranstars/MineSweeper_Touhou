//
// Created by Boran on 25-6-30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WinDialog.h" resolved

#include "windialog.h"
#include "ui_WinDialog.h"


WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::WinDialog) {
    ui->setupUi(this);
}

WinDialog::WinDialog(int elapsedTime, QWidget* parent): QDialog(parent), ui(new Ui::WinDialog)
{
    ui->setupUi(this);
    setWindowTitle("游戏胜利！");
    ui->winMessageLabel->setText(QString("你赢了！只用了%1秒就取得了胜利！").arg(elapsedTime));
    connect(ui->restartButton, &QPushButton::clicked, this, [=]()
    {
        emit restartRequested();
        accept();
    });

    connect(ui->gotoRankButton, &QPushButton::clicked, this, [=]()
    {
        qDebug() << "trying to enter Ranks..But now write yet!";
    });


}

WinDialog::~WinDialog() {
    delete ui;
    qDebug() << "WinDialog destroyed";
}
