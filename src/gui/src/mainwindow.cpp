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




}

MainWindow::~MainWindow() {
    delete ui;
    delete _customDialog;
    delete _gameBoard;
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

void MainWindow::createConnections()
{
    connect(_gameBoard, &MineSweeperTouHou::GameBoard::stateChanged, ui->sceneWidget, [=] ()
    {
        ui->sceneWidget->update();
    });

    connect(_gameBoard, &MineSweeperTouHou::GameBoard::gameWon, this, &MainWindow::on_GameWon);
    connect(_gameBoard, &MineSweeperTouHou::GameBoard::gameLost, this, &MainWindow::on_GameLost);
    connect(_gameBoard, &MineSweeperTouHou::GameBoard::flagsChanged, this, &MainWindow::on_FlagsChanged);
    connect(_gameBoard, &MineSweeperTouHou::GameBoard::statusChanged, this, &MainWindow::on_StatusChanged);


}

void MainWindow::setCustomLevel()
{
    if (_customDialog->exec() == QDialog::Accepted)
    {
        _gameBoard->setDifficulty(MineSweeperTouHou::Difficulty::CUSTOM);
        int customRows = _customDialog->getCustomRows();
        int customCols = _customDialog->getCustomCols();
        int customMines = _customDialog->getCustomMines();
       _gameBoard->reset(customRows,customCols,customMines);
        resizeWindow();
        ui->sceneWidget->update();

        qDebug() << "set custom level";
        qDebug() << customRows << " " << customCols << " " << customMines;


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
    _gameBoard->restart();
    ui->sceneWidget->update();
    qDebug() << "Restart";
}

void MainWindow::on_GameWon(int elapsedTime)
{
    WinDialog *winDialog = new WinDialog(elapsedTime, this);
    connect(winDialog, &WinDialog::restartRequested, this, &MainWindow::on_restartButton_clicked);
    winDialog->exec(); // 使用 exec() 运行模态对话框
    winDialog->deleteLater(); // 确保堆上对象销毁
}

void MainWindow::on_GameLost()
{

}

void MainWindow::on_FlagsChanged(int flags)
{

}

void MainWindow::on_StatusChanged(MineSweeperTouHou::GameStatus newStatus)
{

}


void MainWindow::init()
{
    this->createActions();
    this->createConnections();
}
