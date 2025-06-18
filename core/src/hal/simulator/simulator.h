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

#define SIM_POINT_SIZE 1
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

  }
  ~Simulator() override
  {
    if (renderer != nullptr)
    {
      SDL_DestroyRenderer(renderer);
      renderer = nullptr;
    }
    if (window != nullptr)
    {
      SDL_DestroyWindow(window);
      window = nullptr;
    }
    SDL_Quit();
  }
  bool init() override;
  void deinit() override {}
  void setColor(RGB_t color) override;
  void setColor(uint8_t r, uint8_t g, uint8_t b) override;
  void setA(uint8_t a) override;
  void drawPixel(int x, int y) override;
  void drawRect(int x, int y, int w, int h) override;
  void clearCanvas() override;
  void showCanvas() const override;
  void delay(int ms) override;
  bool checkEvent() override;
  int getTick() override;


};
}


#endif //SIMULATOR_H
