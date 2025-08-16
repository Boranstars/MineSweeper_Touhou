//
// Created by Boran on 25-6-1.
//

#include "gameboard.h"
namespace MineSweeperTouHou {


    void GameBoard::placeMines(int firstRow, int firstCol) {
        // 清空地雷位置
        minesLocations.clear();
        minesLocations.reserve(mineInitCount);

        // 创建索引列表，排除首次点击位置
        QList<int> flattenIndices;
        int firstIndex = firstRow * cols + firstCol; // 计算首次点击的索引
        for (int i = 0; i < rows * cols; ++i) {
            // TODO 让周围3x3的都没有雷
            if (i != firstIndex) { // 排除首次点击
                flattenIndices.append(i);
            }
        }

        // 随机洗牌
        QRandomGenerator rng(QTime::currentTime().msec()); // 使用时间种子
        for (int i = flattenIndices.size() - 1; i > 0; --i) {
            int j = rng.bounded(i + 1); // [0, i]
            qSwap(flattenIndices[i], flattenIndices[j]);
        }

        // 放置地雷
        for (int i = 0; i < mineInitCount && i < flattenIndices.size(); ++i) {
            int index = flattenIndices[i];
            int row = index / cols; // 行号
            int col = index % cols; // 列号
            mineMap[row][col].setAsMineUnit();
            minesLocations.append(QPoint(row, col));
        }
    }

    void GameBoard::revealMines(int row, int col)
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
        {
            return;
        }
        if (gameStatus != GameStatus::PLAYING) return;

        // 第一次点击的时候才生成雷，避免直接炸了
        if (firstClick)
        {
            placeMines(row, col);
            calculateNumbers();
            firstClick = false;
            emit firstClicked();
            this->timer->start(TIME_INTERVAL); // 1秒更新一次
        }

        if (mineMap[row][col].isCovered() && !mineMap[row][col].isMarked())
        {
            // 没有揭开并且不是被标记为旗帜的时候，揭开当前的格子
            // mineMap[row][col].setCovered(false);
            if (mineMap[row][col].getUnitType() == UnitType::MINE)
            {
                // 当前设置为触碰到雷
                mineMap[row][col].setTouched();

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (mineMap[i][j].getUnitType() == UnitType::MINE && !mineMap[i][j].isMarked()) {
                            mineMap[i][j].setCovered(false); // 展示所有地雷
                        } else if (mineMap[i][j].getUnitType() != UnitType::MINE && mineMap[i][j].isMarked()) {
                            mineMap[i][j].setMistaken(true); // 标记错误旗帜
                        }
                    }
                }

                gameStatus = GameStatus::FAILURE;
                qDebug() << "Emitting gameLost";
                emit statusChanged(this->gameStatus);
                emit gameLost();
                return;



            }
            else if (1 || mineMap[row][col].getUnitType() == UnitType::EMPTY)
            {
                // 为空的话就递归的揭开周围格子
                revealMinesRecursive(row, col);
            }
            // 发送信号让sceneWidget重绘
            emit stateChanged();

            if (gameStatus == GameStatus::PLAYING && isWin())
            {
                gameStatus = GameStatus::SUCCESS;
                this->timer->stop();
                emit statusChanged(this->gameStatus);
                emit gameWon();

            }
        }



    }

    void GameBoard::restart()
    {
        this->reset(rows,cols,mineInitCount);

    }

    void GameBoard::calculateNumbers()
    {
        // 对每个地雷周围的3x3区域执行数字增加，dx ,dy { -1, 0, 1 }
        for (const QPoint &minePoint : minesLocations)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int _row = minePoint.x() + dx;
                    int _col = minePoint.y() + dy;

                    if (_row >= 0 && _row < rows && _col >= 0 && _col < cols &&
                        mineMap[_row][_col].getUnitType() != UnitType::MINE)
                    {
                        mineMap[_row][_col].addNumber();
                    }
                }
            }
        }
    }

    void GameBoard::revealMinesRecursive(int row, int col)
    {
        // 基线条件，越界 | 已经揭开 | 标记为旗帜 | 为雷（虽然我认为在这里不可能达到）
        if (row < 0 || col < 0 || row >= rows || col >= cols ||
            !mineMap[row][col].isCovered() || mineMap[row][col].isMarked()
            || mineMap[row][col].getUnitType() == UnitType::MINE)
        {
            return;
        }
        // 揭开当前格子
        mineMap[row][col].setCovered(false);
        qDebug() << "Revealing (" << row << "," << col << "): type=" << static_cast<int>(mineMap[row][col].getUnitType())
         << ", covered=" << mineMap[row][col].isCovered();
        // 递归检查周围八个格子
        if (mineMap[row][col].getUnitType() == UnitType::EMPTY)
        {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx != 0 || dy != 0) { // 排除自身
                        revealMinesRecursive(row + dx, col + dy);
                    }
                }
            }
        }
    }

    void GameBoard::toggleFlags(int row, int col)
    {
        if (gameStatus != GameStatus::PLAYING || row < 0 || row >= rows || col < 0 || col >= cols) return;

        if (mineMap[row][col].isCovered())
        {
            bool marked = !mineMap[row][col].isMarked();
            mineMap[row][col].setMarked(marked); // 更新标记状态
            flags += marked ? -1 : 1; // 更新旗帜数量

            // 通知界面重绘
            emit flagsChanged(flags);
            emit stateChanged();
        }
    }

    bool GameBoard::isWin() const
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                // 非雷方块仍然被覆盖 → 尚未获胜
                if (mineMap[row][col].getUnitType() != UnitType::MINE && mineMap[row][col].isCovered())
                {
                    // 还有雷没有揭开
                    return false;
                }

            }
        }
        return true;
    }

    GameBoard::GameBoard(
        int rows ,
        int cols ,
        int mines ,
        QObject* parent) :
        QObject(parent), rows(rows), cols(cols),mineInitCount(mines),flags(mines),difficulty(Difficulty::EASY),gameStatus(GameStatus::PLAYING),
        firstClick(true)
    {
        qDebug() << "GameBoard with params called";
        qDebug() << "rows: " << rows;
        qDebug() << "cols: " << cols;
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]()
        {
            elapsedTime++;
        } );
        reset(rows, cols, mines);

    }

    GameBoard::GameBoard(QObject* parent): GameBoard(LevelEasy::ROWS, LevelEasy::COLS, LevelEasy::MINES_COUNT, parent)
    {
        qDebug() << "GameBoard called";

    }

    GameBoard::~GameBoard()
    {
        delete timer;
        qDebug() << "GameBoard destroyed";
    }

    void GameBoard::reset(int rows, int cols, int mines)
    {
        this->rows = rows;
        this->cols = cols;
        this->mineInitCount = mines;
        this->flags = mines;
        this->gameStatus = GameStatus::PLAYING;
        this->firstClick = true;
        this->elapsedTime = 0;
        if (this->timer->isActive())
        {
            timer->stop();
        }

        this->mineMap.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            this->mineMap[i].resize(cols);
            for (int j = 0; j < cols; j++)
            {
                mineMap[i][j].reset();
            }
        }
        qDebug() << "GameBoard reseted";
        qDebug() << "rows: " << rows;
        qDebug() << "cols: " << cols;
        qDebug() << "mines: " << mines;
        qDebug() << "elapsedTime: " << elapsedTime;
        qDebug() << "firstClick: " << firstClick;
        qDebug() << "flags: " << flags;

    }

    void GameBoard::setDifficulty(Difficulty difficulty)
    {

        switch (difficulty)
        {
            case Difficulty::EASY:
                reset(LevelEasy::ROWS,LevelEasy::COLS,LevelEasy::MINES_COUNT);
                this->difficulty = Difficulty::EASY;
                break;
            case Difficulty::HARD:
                reset(LevelHard::ROWS,LevelHard::COLS,LevelHard::MINES_COUNT);
                this->difficulty = Difficulty::HARD;
                break;
            case Difficulty::NORMAL:
                reset(LevelNormal::ROWS,LevelNormal::COLS,LevelNormal::MINES_COUNT);
                this->difficulty = Difficulty::NORMAL;
                break;
            case Difficulty::CUSTOM:
                // TODO 结合CustomDialog的信息设置，暂时未实现信息传递
                this->difficulty = Difficulty::CUSTOM;
                break;
            default: ;
        }

    }

    void GameBoard::pause()
    {

        if (gameStatus == GameStatus::PLAYING) {
            gameStatus = GameStatus::PAUSED;
            timer->stop();
            qDebug() << "Paused";
        } else if (gameStatus == GameStatus::PAUSED) {
            gameStatus = GameStatus::PLAYING;
            timer->start(TIME_INTERVAL);
            qDebug() << "Unpaused";
        }
        emit statusChanged(this->gameStatus);
    }

    void GameBoard::unpause()
    {

        if (gameStatus == GameStatus::PAUSED) {
            gameStatus = GameStatus::PLAYING;
            timer->start(TIME_INTERVAL);
        }
    }

    const MineUnit& GameBoard::getUnitAt(const int row, const int col) const
    {
        return this->mineMap[row][col];
    }

    int GameBoard::getRows() const {
        return rows;
    }

    MineSweeperTouHou::Difficulty GameBoard::getCurrentDifficulty() const
    {
        return difficulty;
    }

    int GameBoard::getCols() const {
        return cols;
    }

    int GameBoard::getRemainFlags() const {
        return flags;
    }

    GameStatus GameBoard::getGameStatus() const {
        return gameStatus;
    }
}
