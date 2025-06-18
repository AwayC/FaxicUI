//
// Created by AWAY on 25-6-15.
//
#include "../../core/src/drawer/drawer.h"
#include "../../core/src/drawer/drawBase.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "halDisplay.h"
#include "Displayers.h"
#include "../../core/src/drawer/drawComponents.h"

#include <chrono>
#include <thread>

using namespace Faxic;
const int WIDTH = 256, HEIGHT = 256;
Simulator *sim; // 全局变量
Drawer *drawer; // 全局变量

std::vector<LineStyle> LineStyVec;


void msleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void LineStyInit() {
    LineStyVec.clear();

    LineStyle sty1(RGB_t(0, 0, 0));
    sty1.setWidth(15);
    sty1.setStRound(true);
    sty1.setEdRound(true);
    LineStyVec.push_back(sty1);

    // 红色虚线（宽度2，虚线模式）
    LineStyle sty2(RGB_t(255, 0, 0));
    sty2.setWidth(5);
    sty2.setDash(5, 5);  // 5像素实线 + 5像素间隔
    LineStyVec.push_back(sty2);

    // 蓝色点划线（宽度1，小圆点）
    LineStyle sty3(RGB_t(0, 0, 255));
    sty3.setWidth(5);
    sty3.setDash(2, 3);  // 2像素实线 + 3像素间隔
    LineStyVec.push_back(sty3);

    std::cout << "line style initialized" << std::endl;
    std::cout << "line num: " << LineStyVec.size() << std::endl;
}

void init() {
    LineStyInit();
    sim = new Simulator(WIDTH, HEIGHT);
    sim->init();
    drawer = new Drawer(sim);
    std::cout << "Inited" << std::endl;
}

void deinit() {
    delete drawer;
    std::cout << "Deinited" << std::endl;
}

void testVerLine() {
    for(int i = 0;i < LineStyVec.size();i ++) {
        DrawLine line(Point(i * 10 + 3, 0),
                     Point(i * 10 + 3, 60),
                     &LineStyVec[i]);
        drawer->drawComponent(&line);
    }
}

void testHorLine() {
    for(int i = 0;i < LineStyVec.size();i ++) {
        DrawLine line(Point(60, i * 10),
                     Point(100, i * 10),
                     &LineStyVec[i]);
        drawer->drawComponent(&line);
    }
}

void testSkewLine() {
#if 1
    static float k[5] = {
        0.5, 1, 1.5, -1.5, -1,
    };
    const int cirX = 100, cirY = 100;
    for (int i = 0;i < 5;i ++)
    {
        Point p1(cirX, cirY), p2(cirX + 100, cirY + int(100 * k[i]));
        DrawLine line(p1, p2, &LineStyVec[(i) % LineStyVec.size()]);
        drawer->drawComponent(&line);
    }
#endif
}

void testDrawLine() {
    testVerLine();
    testHorLine();
    testSkewLine();
}

void test() {
    drawer->clear();

    testDrawLine(); // 测试直线绘制

    drawer->flush();
}

int main() {
    init();
    while(sim->checkEvent()) {
        test();
        SDL_Delay(16);
        std::cout << sim->getTick() << std::endl;
    }

    deinit();

    return 0;
}