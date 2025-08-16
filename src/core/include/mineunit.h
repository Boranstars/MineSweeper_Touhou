//
// Created by Boran on 25-6-1.
//

#ifndef MINEUNIT_H
#define MINEUNIT_H

namespace MineSweeperTouHou {
    enum class UnitType
    {
        EMPTY,
        NUMBER,
        MINE,
    };

    class MineUnit {
    private:
        UnitType type = UnitType::EMPTY;
        int number = 0;
        bool covered = true;
        bool marked = false;
        bool mistaken = false;
        bool touched = false;

    public:
        [[nodiscard]] UnitType getUnitType() const;
        void setUnitType(UnitType type);
        [[nodiscard]] int getNumber() const;
        void setNumber(int number);
        [[nodiscard]] bool isCovered() const;
        void setCovered(bool covered);
        [[nodiscard]] bool isMarked() const;
        void setMarked(bool marked);
        [[nodiscard]] bool isMistaken() const;
        void setMistaken(bool mistaken);
        [[nodiscard]] bool isTouched() const;
        void setTouched();


        void addNumber();
        void setAsMineUnit();
        void reset();
        MineUnit() = default;

    };
}


#endif //MINEUNIT_H
