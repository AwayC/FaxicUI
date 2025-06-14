cmake_minimum_required(VERSION 3.30)
project(FaxicUI)

# 基础配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找依赖库
find_package(SDL2 REQUIRED)

# HAL 库配置
add_library(hal STATIC
        core/src/hal/simulator/simulator.cpp
        core/src/hal/halDisplay.cpp
)
target_include_directories(hal PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src/hal
        ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(hal PRIVATE ${SDL2_LIBRARIES})

# Drawer 图形库配置
add_library(drawer STATIC
        core/src/drawer/drawer.cpp
        core/src/drawer/drawer.h
        core/src/drawer/drawBase.cpp
        core/src/drawer/drawBase.h
        core/src/drawer/component/drawLine.cpp
        core/src/drawer/component/drawLine.h
        core/src/drawer/draw_buff.h
)
target_include_directories(drawer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src/drawer
)
target_link_libraries(drawer PRIVATE hal)

# 主程序
add_executable(MyUI
        main.cpp
)
target_link_libraries(MyUI PRIVATE hal drawer ${SDL2_LIBRARIES})
target_include_directories(MyUI PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src
)

add_subdirectory(test)
