//
// Created by Boran on 25-6-1.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QDebug>

#include "mineunit.h"
#include "constants.h"

namespace MineSweeperTouHou {
    typedef QVector<QVector<MineUnit>> MineMap;

    enum class GameStatus
    {
        PLAYING,
        PAUSED,
        FAILURE,
        SUCCESS
    };


    class GameBoard : public QObject{
        Q_OBJECT
    private:
        MineMap mineMap;
        int rows{}, cols{};
        int mineInitCount{}, flags{};
        MineSweeperTouHou::Difficulty difficulty;
        GameStatus gameStatus;
        bool firstClick;
        QTimer *timer;
        int elapsedTime;
        QList<QPoint> minesLocations;
    private:
        void placeMines(int firstRow, int firstCol);

        void calculateNumbers();
        /**
         * 递归地揭开周围的方块
         * @param row 行
         * @param col 列
         *
         */
        void revealMinesRecursive(int row, int col);

        bool isWin() const;
    signals:
        void gameWon(int time);
        void gameLost();
        void statusChanged(GameStatus newStatus);
        void stateChanged();
        void flagsChanged(int flags);
    public:
        GameBoard(int rows , int cols, int mines , QObject *parent = nullptr);
        explicit GameBoard(QObject *parent = nullptr);
        ~GameBoard() override;

    public:
        void reset(int rows, int cols, int mines);
        void setDifficulty(MineSweeperTouHou::Difficulty difficulty);
        void pause();
        void unpause();
        void revealMines(int row, int col);
        void toggleFlags(int row, int col);
        void restart();
        [[nodiscard]] const MineUnit& getUnitAt(int row, int col) const;

        [[nodiscard]] int getRows() const;
        [[nodiscard]] Difficulty getCurrentDifficulty() const;

        [[nodiscard]] int getCols() const;

        [[nodiscard]] int getRemainFlags() const;
    };
}

#endif //GAMEBOARD_H
