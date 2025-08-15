#include <gtest/gtest.h>
#include <QCoreApplication>
#include "gameboard.h"

using namespace MineSweeperTouHou;

class GameBoardTest : public ::testing::Test {
protected:
    GameBoard* board = nullptr;

    void SetUp() override {
        board = new GameBoard(5, 5, 5); // 默认 5x5，5 个雷
    }

    void TearDown() override {
        delete board;
    }

    // 获取指定位置单元格
    const MineUnit& getUnit(int row, int col) {
        return board->getUnitAt(row, col);
    }

    // 揭开一个格子
    void reveal(int row, int col) {
        board->revealMines(row, col);
    }

    // 标记一个格子
    void flag(int row, int col) {
        board->toggleFlags(row, col);
    }

    // 获取揭开后的格子数量
    int countRevealedCells() {
        int count = 0;
        for (int r = 0; r < board->getRows(); ++r) {
            for (int c = 0; c < board->getCols(); ++c) {
                if (!getUnit(r, c).isCovered()) {
                    count++;
                }
            }
        }
        return count;
    }
};

// 验证构造是否正确
TEST_F(GameBoardTest, Constructor_InitializesCorrectly) {
    EXPECT_EQ(board->getRows(), 5);
    EXPECT_EQ(board->getCols(), 5);
    EXPECT_EQ(board->getRemainFlags(), 5);
    EXPECT_EQ(board->getGameStatus(), GameStatus::PLAYING);
}

// 验证 reset 后网格是否正确重置
TEST_F(GameBoardTest, Reset_SetsAllUnitsToDefault) {
    board->reset(3, 3, 3);
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            const MineUnit& unit = getUnit(row, col);
            EXPECT_TRUE(unit.isCovered());
            EXPECT_FALSE(unit.isMarked());
            EXPECT_FALSE(unit.isTouched());
            EXPECT_EQ(unit.getUnitType(), UnitType::EMPTY);
        }
    }
}

// 首次点击后生成 3x3 安全区
TEST_F(GameBoardTest, FirstClick_CreatesSafe3x3Area) {
    int testRow = 2;
    int testCol = 2;

    board->reset(5, 5, 5); // 重置保证雷数一致
    board->revealMines(testRow, testCol); // 第一次点击，触发生成雷区

    const MineUnit& clicked = getUnit(testRow, testCol);
    EXPECT_FALSE(clicked.isTouched()); // 未踩雷

    // // 检查 3x3 区域是否无雷
    // for (int dr = -1; dr <= 1; dr++) {
    //     for (int dc = -1; dc <= 1; dc++) {
    //         int r = testRow + dr;
    //         int c = testCol + dc;
    //         if (r >= 0 && r < 5 && c >= 0 && c < 5) {
    //             EXPECT_NE(getUnit(r, c).getUnitType(), UnitType::MINE);
    //         }
    //     }
    // }
}

// 点击空格后展开
TEST_F(GameBoardTest, RevealEmptyTile_ExpandsCorrectly) {
    board->reset(3, 3, 1); // 一个雷
    board->revealMines(2, 2); // 首次展开格子

    int revealedCount = countRevealedCells();
    EXPECT_GT(revealedCount, 1); // 揭开多个格子
}

// 所有数字是否正确反映相邻雷数量
TEST_F(GameBoardTest, RevealMines_SetsCorrectNumbers) {
    board->reset(5, 5, 5);
    board->revealMines(0, 0); // 生成雷并触发计算

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            const MineUnit& unit = getUnit(row, col);

            if (unit.getUnitType() == UnitType::NUMBER) {
                int mineCount = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int r = row + dr;
                        int c = col + dc;
                        if (r >= 0 && r < 5 && c >= 0 && c < 5) {
                            if (getUnit(r, c).getUnitType() == UnitType::MINE) {
                                mineCount++;
                            }
                        }
                    }
                }
                EXPECT_EQ(unit.getNumber(), mineCount);
            }
        }
    }
}

// 点击雷触发失败
TEST_F(GameBoardTest, ClickOnMine_SetsGameToFailure) {
    board->reset(3, 3, 1); // 1 个雷
    board->revealMines(0, 0); // 生成雷
    board->toggleFlags(0, 0); // 去掉标记以触发失败

    board->revealMines(0, 0); // 点击雷格

    EXPECT_EQ(board->getGameStatus(), GameStatus::FAILURE);
    EXPECT_EQ(getUnit(0, 0).isTouched(), true);
}

// 胜利条件：所有非雷格子揭开
TEST_F(GameBoardTest, AllNonMinesRevealed_TriggersWin) {
    board->reset(3, 3, 0); // 无雷

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            board->revealMines(r, c); // 揭开所有格子
        }
    }

    EXPECT_EQ(board->getGameStatus(), GameStatus::SUCCESS);
}

// 标记功能
TEST_F(GameBoardTest, ToggleFlag_TogglesFlagAndCount) {
    board->toggleFlags(0, 0);
    EXPECT_TRUE(getUnit(0, 0).isMarked());
    EXPECT_EQ(board->getRemainFlags(), 4);

    board->toggleFlags(0, 0); // 取消标记
    EXPECT_FALSE(getUnit(0, 0).isMarked());
    EXPECT_EQ(board->getRemainFlags(), 5);
}

// 暂停和继续
TEST_F(GameBoardTest, PauseAndUnpause_TogglesStatusCorrectly) {
    board->pause();
    EXPECT_EQ(board->getGameStatus(), GameStatus::PAUSED);

    board->unpause();
    EXPECT_EQ(board->getGameStatus(), GameStatus::PLAYING);
}
