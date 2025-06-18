//
// Created by AWAY on 25-4-18.
//

#include "simulator.h"

#include <cassert>

#define SET_WHITE SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)
#define SET_BLACK SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)
#define SET_RED SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255)
/**** color : fill color ****/
namespace Faxic
{
    void Simulator::setColor(RGB_t color)
    {
        this->drawColor = color; // set color
#if 0
        std::cout << "set color: " << (int)color.r << " " << (int)color.g << " " << (int)color.b << std::endl;
        std::cout << "alpha: " << (int)alpha << std::endl;
#endif
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
    }

    void Simulator::setColor(uint8_t r, uint8_t g, uint8_t b)
    {
        this->drawColor = {r, g, b};
        SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    }


    void Simulator::clearCanvas(){
        SDL_RenderClear(renderer);
    };

    void Simulator::drawPixel(int x, int y){

        SDL_Rect rect = {x * SIM_POINT_SIZE,
                         y * SIM_POINT_SIZE,
                         SIM_POINT_SIZE,
                         SIM_POINT_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    };

    void Simulator::drawRect(int x, int y, int w, int h) {

        SDL_Rect rect = {x * SIM_POINT_SIZE,
                         y * SIM_POINT_SIZE,
                         w * SIM_POINT_SIZE,
                         h * SIM_POINT_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }


    bool Simulator::init() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width * SIM_POINT_SIZE,
                                  height * SIM_POINT_SIZE,
                                  0);
        if (nullptr == window)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return false;
        } else
        {
            std::cout << "width: " << width << std::endl;
            std::cout << "height: " << height << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(nullptr == renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return false;
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);  // 启用透明度混合
        setColor(RGB_WHITE);
        clearCanvas();
        showCanvas();
        std::cout << "SDL_Init Success" << std::endl;
        return true;
    }

    void Simulator::showCanvas() const
    {
        assert(renderer != nullptr);
        SDL_RenderPresent(renderer);
    }

    void Simulator::delay(int ms)
    {
        SDL_Delay(ms);
    }

    bool Simulator::checkEvent()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return false;
        }
        return true;
    }

    int Simulator::getTick() {
        return SDL_GetTicks();
    }

    void Simulator::setA(uint8_t a) {
        alpha = a;
    }
}


