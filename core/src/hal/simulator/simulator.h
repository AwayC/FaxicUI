//
// Created by AWAY on 25-4-18.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <SDL2/SDL.h>
#include <iostream>
#include "../halDisplay.h"


#define RGB_WHITE  RGB_t({255, 255, 255})
#define RGB_BLACK RGB_t({0, 0, 0})

#define SIM_POINT_SIZE 5
#define SIM_COLOR_DEFAULT RGB_WHITE
#define SIM_BACKGROUND_DEFAULT RGB_BLACK
/************ simulate the oled srcreen ***********/

namespace Faxic
{
class Simulator : public halDisplay{
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

public:
  Simulator(int wid, int hei) : halDisplay(wid, hei) {
    this->drawColor = RGB_WHITE;
    this->alpha = 255;
  }
  ~Simulator() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
  bool init();
  void deinit() {
    return ;
  }
  void setColor(RGB_t color);
  void setColor(uint8_t r, uint8_t g, uint8_t b);
  void setA(uint8_t a);
  void drawPixel(int x, int y);
  void drawRect(int x, int y, int w, int h);
  void clearCanvas();
  void showCanvas() const;
  void delay(int ms);
  bool checkEvent();
  int getTick();


};
}


#endif //SIMULATOR_H
