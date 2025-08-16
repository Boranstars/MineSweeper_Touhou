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

    void printBoardState() {
        std::cout << "\nCurrent Board State:\n";
        for (int r = 0; r < board->getRows(); ++r) {
            for (int c = 0; c < board->getCols(); ++c) {
                const MineUnit& unit = getUnit(r, c);
                char display = '.';

                if (!unit.isCovered()) {
                    if (unit.getUnitType() == UnitType::MINE) {
                        display = unit.isTouched() ? 'X' : '*';
                    } else {
                        display = '0' + unit.getNumber();
                    }
                } else if (unit.isMarked()) {
                    display = 'F';
                }
                std::cout << display << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "Status: "
                  << static_cast<int>(board->getGameStatus())
                  << " | Flags left: " << board->getRemainFlags()
                  << "\n\n";
    }
    // 新增：获取雷位置列表
    QList<QPoint> getMinePositions() {
        QList<QPoint> mines;
        for (int r = 0; r < board->getRows(); ++r) {
            for (int c = 0; c < board->getCols(); ++c) {
                if (getUnit(r, c).getUnitType() == UnitType::MINE) {
                    mines.append(QPoint(r, c));
                }
            }
        }
        return mines;
    }
    // 新增：安全首次点击（确保不踩雷）
    void safeFirstClick() {
        // 找到第一个非雷位置点击
        for (int r = 0; r < board->getRows(); ++r) {
            for (int c = 0; c < board->getCols(); ++c) {
                if (getUnit(r, c).getUnitType() != UnitType::MINE) {
                    reveal(r, c);
                    return;
                }
            }
        }
        FAIL() << "No safe tile found for first click!";
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

// 第一次点击不应该触发雷
TEST_F(GameBoardTest, FirstClickNeverTriggersMine) {
    const int testRuns = 10;
    for (int i = 0; i < testRuns; ++i) {
        board->reset(3, 3, 1);
        reveal(1, 1); // 中心点击
        // 验证点击位置不是雷
        ASSERT_NE(getUnit(1, 1).getUnitType(), UnitType::MINE)
            << "First click triggered mine at attempt " << i;

        printBoardState();
    }
}

// 测试点击空白格后的展开逻辑
TEST_F(GameBoardTest, RevealEmptyTile_ExpandsCorrectly) {
    board->reset(3, 3, 1);

    // 首次点击（触发雷生成）
    safeFirstClick();
    printBoardState(); // 调试用

    // 现在可以获取雷的位置
    QList<QPoint> mines = getMinePositions();
    ASSERT_EQ(mines.size(), 1) << "雷应在首次点击后生成";

    // 找到另一个安全位置测试展开逻辑
    QPoint testPos;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (!mines.contains(QPoint(r,c)) && getUnit(r,c).isCovered()) {
                testPos = QPoint(r, c);
                break;
            }
        }
    }

    // 点击测试位置
    reveal(testPos.x(), testPos.y());
    printBoardState();

    // 验证展开效果
    int revealedCount = countRevealedCells();
    EXPECT_GT(revealedCount, 1) << "应展开多个格子";
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

// // 点击雷触发失败
// TEST_F(GameBoardTest, ClickOnMine_SetsGameToFailure) {
//     board->reset(3, 3, 1); // 1 个雷
//     board->revealMines(0, 0); // 生成雷
//     board->toggleFlags(0, 0); // 去掉标记以触发失败
//
//     board->revealMines(0, 0); // 点击雷格
//
//     EXPECT_EQ(board->getGameStatus(), GameStatus::FAILURE);
//     EXPECT_EQ(getUnit(0, 0).isTouched(), true);
// }

TEST_F(GameBoardTest, ClickOnMineAfterInitialization) {
    const int safeSize = 4;
    const int mineCount = 1;
    board->reset(safeSize, safeSize, mineCount);

    // 首次安全点击
    board->revealMines(1, 1);
    printBoardState();

    // 检查游戏状态
    GameStatus statusAfterFirstClick = board->getGameStatus();

    if (statusAfterFirstClick == GameStatus::SUCCESS) {
        // 首次点击已经导致胜利 - 这是有效情况，跳过后续测试
        GTEST_SKIP() << "First click resulted in victory. Skipping mine click test.";
    } else {
        // 确保游戏仍在进行中
        ASSERT_EQ(statusAfterFirstClick, GameStatus::PLAYING)
            << "Game should be playing after first click";

        // 查找雷的位置
        QPoint minePos(-1, -1);
        for (int r = 0; r < safeSize; ++r) {
            for (int c = 0; c < safeSize; ++c) {
                if (getUnit(r, c).getUnitType() == UnitType::MINE) {
                    minePos = QPoint(r, c);
                    break;
                }
            }
            if (minePos.x() != -1) break;
        }
        ASSERT_NE(minePos.x(), -1) << "No mine generated after first click";

        // 确保雷的位置不是首次点击位置
        ASSERT_FALSE(minePos.x() == 1 && minePos.y() == 1)
            << "Mine should not be at first click position";

        // 点击雷
        board->revealMines(minePos.x(), minePos.y());
        printBoardState();

        // 验证状态
        EXPECT_EQ(board->getGameStatus(), GameStatus::FAILURE);
        EXPECT_TRUE(getUnit(minePos.x(), minePos.y()).isTouched());

        // 验证所有雷都被揭示
        bool allMinesRevealed = true;
        for (int r = 0; r < safeSize; ++r) {
            for (int c = 0; c < safeSize; ++c) {
                const MineUnit& unit = getUnit(r, c);
                if (unit.getUnitType() == UnitType::MINE && unit.isCovered()) {
                    allMinesRevealed = false;
                }
            }
        }
        EXPECT_TRUE(allMinesRevealed);
    }
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
