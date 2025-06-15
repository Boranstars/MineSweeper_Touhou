//
// Created by Boran on 25-6-1.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H



namespace MineSweeperTouHou
{
    constexpr int TIME_INTERVAL = 1000;
    enum class Difficulty
    {
        EASY,
        NORMAL,
        HARD,
        CUSTOM
    };

    struct GameLevel
    {
        static constexpr int ROWS = 0;
        static constexpr int COLS = 0;
        static constexpr int MINES_COUNT = 0;

    };

    struct LevelEasy
    {
        static constexpr int ROWS = 10;
        static constexpr int COLS = 10;
        static constexpr int MINES_COUNT = 10;
    };

    struct LevelNormal
    {
        static constexpr int ROWS = 15;
        static constexpr int COLS = 15;
        static constexpr int MINES_COUNT = 30;
    };

    struct LevelHard
    {
        static constexpr int ROWS = 30;
        static constexpr int COLS = 20;
        static constexpr int MINES_COUNT = 100;
    };

    struct LevelCustom
    {
        int ROWS;
        int COLS;
        int MINES_COUNT;
        LevelCustom(int ROWS, int COLS, int MINES_COUNT) : ROWS(ROWS), COLS(COLS), MINES_COUNT(MINES_COUNT)
        {
            if (ROWS < 0 || COLS < 0 || MINES_COUNT < 0)
            {
                throw std::invalid_argument("Invalid arguments");
            }
            if (ROWS * COLS < MINES_COUNT)
            {
                throw std::invalid_argument("Too many mines for the board size");
            }
        }

    };

    struct GameObjectProperties
    {
        struct SceneProperties
        {
            static constexpr int MARGIN = 30;
        };

        struct MineUnitProperties
        {
            static constexpr int SIZE = 26;
        };
    };

    struct GameWindowProperties {
        static constexpr int MARGIN_X = 10;
        static constexpr int MARGIN_Y = 70;
    };
}


#endif //CONSTANTS_H
