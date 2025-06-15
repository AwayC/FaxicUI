//
// Created by AWAY on 25-6-14.
//
#include <iostream>
#include <SDL2/SDL.h>
#include "halDisplay.h"
#include "Displayers.h"

#include <chrono>
#include <thread>

using namespace Faxic;

const int WIDTH = 128, HEIGHT = 64;
Simulator *sim; // 全局变量
RGB_t colMap[] = {
    RGB_BLACK,
    RGB_WHITE,
    RGB_RED,
    RGB_GREEN,
    RGB_BLUE,
    RGB_YELLOW,
    RGB_CYAN,
    RGB_MAGENTA,
    RGB_ORANGE,
    RGB_PURPLE,
    RGB_PINK,
    RGB_NAVY,
    RGB_GRAY,
};

void msleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void init()
{
    sim = new Simulator(WIDTH, HEIGHT);
    sim->init();
}

void deinit()
{
    delete sim;
}

void testDrawPixel()
{

    for (int i = 0;i < 13;i ++)
    {
        for (int j = 0;j < 30;j ++)
        {
            sim->setColor(colMap[i]);
            sim->drawPixel(i * 2, j * 2);
        }
    }
}

void testDrawRect()
{
    int offset = 60;
    for (int i = 0;i < 13;i ++)
    {
        sim->setColor(colMap[i]);
        sim->drawRect(i * 4 + offset, 0, 4, 64);
    }
}

void tests()
{
    static uint8_t alpha = 255;
    alpha = (alpha + 255) % 256;
    sim->setA(alpha); // 设置透明度
    sim->setColor(RGB_WHITE);
    sim->clearCanvas();
    testDrawPixel();
    testDrawRect();
    sim->showCanvas();
    std::cout << sim->getTick() << std::endl;
}

int main()
{
    init();
    while (sim->checkEvent())
    {
        tests();
        msleep(100);
    }
    deinit();
    return 0;
}
