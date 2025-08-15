//
// Created by Boran on 25-6-1.
//

#include "mineunit.h"

namespace MineSweeperTouHou {
    UnitType MineUnit::getUnitType() const
    {
        return type;
    }

    void MineUnit::setUnitType(const UnitType type)
    {
        this->type = type;
    }

    int MineUnit::getNumber() const
    {
        return number;
    }

    void MineUnit::setNumber(const int number)
    {
        this->type = UnitType::NUMBER;
        this->number = number;
    }

    bool MineUnit::isCovered() const
    {
        return covered;
    }

    void MineUnit::setCovered(const bool covered)
    {
        this->covered = covered;
    }

    bool MineUnit::isMarked() const
    {

        return marked;
    }

    void MineUnit::setMarked(const bool marked)
    {
        this->marked = marked;
    }



    bool MineUnit::isMistaken() const
    {
        return mistaken;
    }

    void MineUnit::setMistaken(const bool mistaken)
    {
        this->mistaken = mistaken;
    }

    bool MineUnit::isTouched() const
    {
        return touched;
    }

    void MineUnit::setTouched()
    {
        this->touched = true;
    }



    void MineUnit::addNumber()
    {
        // 如果原来为UnitType::EMPTY，则更新状态，这样无论如何都为数字
        this->type = UnitType::NUMBER;
        this->number++;
    }

    void MineUnit::setAsMineUnit()
    {
        this->type = UnitType::MINE;
    }

    void MineUnit::reset()
    {
        this->type = UnitType::EMPTY;
        this->number = 0;
        this->covered = true;
        this->marked = false;
        this->mistaken = false;
        this->touched = false;

    }
}