cmake_minimum_required(VERSION 3.30)
project(MyUI)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找 SDL2 库
find_package(SDL2 REQUIRED)

# 定义 hal 库
add_library(hal STATIC
        core/src/hal/simulator/simulator.cpp
)

# 设置 hal 库的包含目录
target_include_directories(hal
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/src/hal>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${SDL2_INCLUDE_DIRS}
)

# 链接 SDL2 库到 hal 库
target_link_libraries(hal
        PRIVATE
        ${SDL2_LIBRARIES}
)

# 添加可执行文件
add_executable(MyUI main.cpp)

# 链接 hal 库到 MyUI 可执行文件
target_link_libraries(MyUI
        PRIVATE
        hal
        ${SDL2_LIBRARIES}
)

# 设置 MyUI 可执行文件的包含目录
target_include_directories(MyUI
        PRIVATE
        ${SDL2_INCLUDE_DIRS}
)