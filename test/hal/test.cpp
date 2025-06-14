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


void msleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main()
{
    auto* sim = new Simulator(WIDTH, HEIGHT);
    sim->init();
    while (sim->checkEvent())
    {
        sim->setColor(255, 255, 255);
        sim->clearCanvas();

        sim->setColor(0, 0, 0);
        sim->drawPixel(60, 30);

        sim->setColor(255, 0, 0);
        sim->drawRect(10, 10, 10, 10);

        sim->showCanvas();
        msleep(500);
    }
    return 0;
}
