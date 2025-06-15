//
// Created by Boran on 25-6-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->_customDialog = new CustomDialog(this);
    this->_gameBoard = new MineSweeperTouHou::GameBoard(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createActions()
{
    connect(ui->actionCustom, &QAction::triggered,this, &MainWindow::setCustomLevel);
}

void MainWindow::setCustomLevel()
{
    if (_customDialog->exec() == QDialog::Accepted)
    {
        qDebug() << "set custom level";


    }
}

void MainWindow::on_restartButton_clicked()
{
    qDebug() << "Restart";
}

void MainWindow::init()
{
    this->createActions();
}
