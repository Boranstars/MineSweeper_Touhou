//
// Created by 杨博元 on 2025/8/15.
//
#include <gtest/gtest.h>
#include "resourceloader.h"
#include <QBuffer>
#include <QSignalSpy>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QGuiApplication>

class ResourceLoaderTest : public ::testing::Test {
protected:

};
int main(int argc, char** argv) {
    // 创建 Qt GUI 应用程序实例
    QGuiApplication app(argc, argv);

    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行测试
    int result = RUN_ALL_TESTS();

    // 注意：这里不调用 app.exec()，因为我们不需要事件循环
    return result;
}


TEST_F(ResourceLoaderTest,NothingToTestYet) {
    EXPECT_EQ(0, 0) << "此测试必须通过";
}