set(CMAKE_AUTOMOC ON)

enable_testing()

include(GoogleTest)

# 正常不应该这样手动生成，但我没有找到好的解决方法
qt6_generate_moc(
        ${CORE_INCLUDE_DIR}/gameboard.h
        ${CMAKE_CURRENT_BINARY_DIR}/moc_gameboard.cpp
)
function(add_test_executable TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    target_include_directories(${TARGET_NAME} PRIVATE

            ${CORE_INCLUDE_DIR}
            ${UTILS_INCLUDE_DIR}
#            ${Qt6Core_INCLUDE_DIRS}

    )
    target_link_libraries(${TARGET_NAME} PRIVATE
            Qt::Core
            GTest::gtest_main

    )

    gtest_discover_tests(${TARGET_NAME})
endfunction()


add_test_executable(mineunit_test
        core/mineunit_test.cpp
        ${CORE_SOURCES_DIR}/mineunit.cpp)

add_test_executable(gameboard_test

        core/gameboard_test.cpp
        ${CORE_SOURCES_DIR}/mineunit.cpp
        ${CORE_SOURCES_DIR}/gameboard.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/moc_gameboard.cpp

)



add_executable(resouseloader utils/resouceloader_test.cpp)
