//
// Created by 杨博元 on 2025/8/15.
//
#include <gtest/gtest.h>
#include "mineunit.h"

using namespace MineSweeperTouHou;

class MineUnitTest : public ::testing::Test {
protected:
    MineUnit unit;
};

// 测试默认构造函数，确保所有初始状态都设置正确
TEST_F(MineUnitTest, DefaultConstruction_InitialStateCorrect) {
    EXPECT_EQ(unit.getUnitType(), UnitType::EMPTY);
    EXPECT_EQ(unit.getNumber(), 0);
    EXPECT_FALSE(unit.isCovered());       // 默认不是被覆盖的？
    EXPECT_FALSE(unit.isMarked());
    EXPECT_FALSE(unit.isMistaken());
    EXPECT_FALSE(unit.isTouched());
}

// 测试 UnitType 设置/获取是否正常
TEST_F(MineUnitTest, SetAndGetType) {
    unit.setUnitType(UnitType::MINE);
    EXPECT_EQ(unit.getUnitType(), UnitType::MINE);

    unit.setUnitType(UnitType::NUMBER);
    EXPECT_EQ(unit.getUnitType(), UnitType::NUMBER);

    unit.setUnitType(UnitType::EMPTY);
    EXPECT_EQ(unit.getUnitType(), UnitType::EMPTY);
}

// 测试是否为雷，设置为雷是否正常
TEST_F(MineUnitTest, SetAsMineUnitChangesTypeToMine) {
    unit.setAsMineUnit();
    EXPECT_EQ(unit.getUnitType(), UnitType::MINE);
}

// 测试设置数字是否自动设为 NUMBER 类型
TEST_F(MineUnitTest, SetNumberChangesTypeToNumber) {
    const int testNum = 5;
    unit.setNumber(testNum);
    EXPECT_EQ(unit.getNumber(), testNum);
    EXPECT_EQ(unit.getUnitType(), UnitType::NUMBER);
}

// 测试 addNumber 是否：
// - 更改类型为 NUMBER
// - 数值正确递增
TEST_F(MineUnitTest, AddNumberIncrementsAndSetsToNumber) {
    unit.addNumber();
    EXPECT_EQ(unit.getUnitType(), UnitType::NUMBER);
    EXPECT_EQ(unit.getNumber(), 1);

    unit.addNumber();
    EXPECT_EQ(unit.getNumber(), 2);
}

// 测试覆盖状态是否正确设置
TEST_F(MineUnitTest, SetCovered) {
    unit.setCovered(true);
    EXPECT_TRUE(unit.isCovered());

    unit.setCovered(false);
    EXPECT_FALSE(unit.isCovered());
}

// 测试标记状态是否设置正确
TEST_F(MineUnitTest, SetMarked) {
    unit.setMarked(true);
    EXPECT_TRUE(unit.isMarked());

    unit.setMarked(false);
    EXPECT_FALSE(unit.isMarked());
}

// 测试误标状态是否设置正确
TEST_F(MineUnitTest, SetMistaken) {
    unit.setMistaken(true);
    EXPECT_TRUE(unit.isMistaken());

    unit.setMistaken(false);
    EXPECT_FALSE(unit.isMistaken());
}

// 测试触碰状态是否设置正确
TEST_F(MineUnitTest, SetTouched) {
    unit.setTouched();
    EXPECT_TRUE(unit.isTouched());
}

// 测试 reset() 是否将所有状态恢复为默认值
TEST_F(MineUnitTest, ResetToDefaultState) {
    unit.setUnitType(UnitType::MINE);
    unit.setNumber(5);
    unit.setCovered(true);
    unit.setMarked(true);
    unit.setMistaken(true);
    unit.setTouched();

    unit.reset();

    EXPECT_EQ(unit.getUnitType(), UnitType::EMPTY);
    EXPECT_EQ(unit.getNumber(), 0);
    EXPECT_TRUE(unit.isCovered());        // 注意：reset 里 covered = true
    EXPECT_FALSE(unit.isMarked());
    EXPECT_FALSE(unit.isMistaken());
    EXPECT_FALSE(unit.isTouched());
}
