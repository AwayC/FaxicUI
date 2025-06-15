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
const int WIDTH = 128, HEIGHT = 64;
Simulator *sim; // 全局变量
Drawer *drawer; // 全局变量

void msleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void init() {
    sim = new Simulator(WIDTH, HEIGHT);
    sim->init();
    drawer = new Drawer(sim);
    std::cout << "Inited" << std::endl;
}

void deinit() {
    drawer->~Drawer();
    delete drawer;
    std::cout << "Deinited" << std::endl;
}

void testVerLine() {

}

void testHorLine() {

}

void testSkewLine() {

}

void testDrawLine() {
    testVerLine();
    testHorLine();
    testSkewLine();
}

void test() {
    drawer->clear();



    drawer->flush();
}

int main() {
    init();
    while(sim->checkEvent()) {
        test();
        msleep(100);
    }

    deinit();

    return 0;
}