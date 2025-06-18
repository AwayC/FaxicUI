cmake_minimum_required(VERSION 3.30)

project(tests)

add_executable(testHal
        hal/test.cpp
)
add_executable(testDrawer
        drawer/test.cpp
)
# 链接核心库和依赖项
target_link_libraries(testHal PRIVATE
        hal
        ${SDL2_LIBRARIES}
)

target_link_libraries(testDrawer PRIVATE
        drawer
        ${SDL2_LIBRARIES}
        hal
)

# 设置包含路径
target_include_directories(testHal PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/core/src/hal  # 核心头文件路径
        ${CMAKE_SOURCE_DIR}/core/src      # 附加基础路径
)

target_include_directories(testDrawer PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/core/src      # 附加基础路径
)
