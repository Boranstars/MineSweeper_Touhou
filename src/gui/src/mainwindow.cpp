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
    ui->sceneWidget->setGameboard(this->_gameBoard);

    connect(_gameBoard, &MineSweeperTouHou::GameBoard::stateChanged, ui->sceneWidget, [=] ()
    {
        ui->sceneWidget->update();
    });


}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::createActions()
{
    // TODO 确认是否直接使用UPDATE
    connect(ui->actionCustom, &QAction::triggered,this, &MainWindow::setCustomLevel);
    connect(ui->actionLevelEasy, &QAction::triggered,this, [this] {
        _gameBoard->setDifficulty(MineSweeperTouHou::Difficulty::EASY);
        resizeWindow();
        ui->sceneWidget->update();
    });

    connect(ui->actionLevelNormal, &QAction::triggered,this, [this] {
        _gameBoard->setDifficulty(MineSweeperTouHou::Difficulty::NORMAL);
        ui->sceneWidget->update();
        resizeWindow();

    });
    connect(ui->actionLevelHard, &QAction::triggered,this, [this] {
        _gameBoard->setDifficulty(MineSweeperTouHou::Difficulty::HARD);
        resizeWindow();
        ui->sceneWidget->update();
    });
}

void MainWindow::setCustomLevel()
{
    if (_customDialog->exec() == QDialog::Accepted)
    {
        qDebug() << "set custom level";


    }
}

void MainWindow::resizeWindow() {
    int rows = _gameBoard->getRows();
    int cols = _gameBoard->getCols();

    fitnessW = MineSweeperTouHou::GameWindowProperties::MARGIN_X * 2 +
        rows * MineSweeperTouHou::GameObjectProperties::MineUnitProperties::SIZE;

    fitnessH = MineSweeperTouHou::GameWindowProperties::MARGIN_X + MineSweeperTouHou::GameWindowProperties::MARGIN_Y +
        cols * MineSweeperTouHou::GameObjectProperties::MineUnitProperties::SIZE;
        setFixedSize(fitnessW, fitnessH);
        setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    QGuiApplication::primaryScreen()->geometry()));

    qDebug() << "fitness w: " << fitnessW;
    qDebug() << "fitness h: " << fitnessH;
    qDebug() << "rows: " << rows;
    qDebug() << "cols: " << cols;
}


void MainWindow::on_restartButton_clicked()
{
    qDebug() << "Restart";
}

void MainWindow::init()
{
    this->createActions();
}
