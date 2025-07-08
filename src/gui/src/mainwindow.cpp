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
    this->_timer = new QTimer(this);
    ui->sceneWidget->setGameboard(this->_gameBoard);

    _gameBoard->setDifficulty(MineSweeperTouHou::Difficulty::EASY);
    resizeWindow();
    ui->sceneWidget->update();


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

    connect(ui->actionRestart, &QAction::triggered,this, &MainWindow::on_restartButton_clicked);
    connect(ui->actionPause, &QAction::triggered,this, &MainWindow::on_GamePaused);
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
    connect(_gameBoard, &MineSweeperTouHou::GameBoard::firstClicked, this, &MainWindow::on_FirstClicked);
    connect(_timer, &QTimer::timeout, this, [this]() {
        this->elapsedTime++;
        // this->elapsedTime += this->_timer->interval();
        ui->timeValueLabel->setText(QString::number(this->elapsedTime));

    });


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

    // 开始的时候剩余旗帜数量等于雷数量
    ui->MineRemainLabel->setText(QString::number(_gameBoard->getRemainFlags()));
    ui->timeValueLabel->setText(QString::number(0));
    if (this->_timer->isActive()) {
        this->_timer->stop();
    }
    this->elapsedTime = 0;
    qDebug() << "fitness w: " << fitnessW;
    qDebug() << "fitness h: " << fitnessH;
    qDebug() << "rows: " << rows;
    qDebug() << "cols: " << cols;
}


void MainWindow::on_restartButton_clicked()
{
    _gameBoard->restart();
    ui->sceneWidget->update();
    ui->MineRemainLabel->setText(QString::number(_gameBoard->getRemainFlags()));
    ui->timeValueLabel->setText(QString::number(0));
    if (this->_timer->isActive()) {
        this->_timer->stop();
    }
    this->elapsedTime = 0;
    qDebug() << "Restart";
}

void MainWindow::on_GameWon()
{

    WinDialog *winDialog = new WinDialog(this->elapsedTime, this);
    connect(winDialog, &WinDialog::restartRequested, this, &MainWindow::on_restartButton_clicked);
    winDialog->exec(); // 使用 exec() 运行模态对话框
    winDialog->deleteLater(); // 确保堆上对象销毁
}

void MainWindow::on_GameLost()
{
    LostDialog *lostDialog = new LostDialog(this);
    connect(lostDialog, &LostDialog::restartRequested, this, &MainWindow::on_restartButton_clicked);
    connect(lostDialog, &LostDialog::exitGameRequested, this, &MainWindow::close);
    lostDialog->exec();
    lostDialog->deleteLater();
}

void MainWindow::on_FlagsChanged(int flags)
{
    qDebug() << "Remainflags: " << flags;
    ui->MineRemainLabel->setText(QString::number(flags));
}

void MainWindow::on_StatusChanged(MineSweeperTouHou::GameStatus newStatus)
{
    // TODO 将游戏胜利\失败\暂停\放入此处处理
    qDebug() << "GameStatus changed: " ;
    switch (newStatus) {
        case MineSweeperTouHou::GameStatus::FAILURE:
            qDebug() << "FAILURE";
            // TODO
            this->_timer->stop();
            break;
        case MineSweeperTouHou::GameStatus::SUCCESS:
            qDebug() << "SUCCESS";
            // TODO
            this->_timer->stop();
            break;
        case MineSweeperTouHou::GameStatus::PAUSED:
            qDebug() << "PAUSED";

            this->_timer->stop();
            break;
        case MineSweeperTouHou::GameStatus::PLAYING:
            qDebug() << "PLAYING";
            if (!this->_timer->isActive()) {

                this->_timer->start(MineSweeperTouHou::TIME_INTERVAL);
            }
            break;

    }
}

void MainWindow::on_FirstClicked() {
    this->_timer->start(MineSweeperTouHou::TIME_INTERVAL);
}

void MainWindow::on_GamePaused() {
    _gameBoard->pause();



}


void MainWindow::init()
{
    this->createActions();
    this->createConnections();
    this->setWindowTitle(tr("MineSweeperTouhou"));

}
