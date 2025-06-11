//
// Created by AWAY on 25-6-8.
//

#ifndef DRAW_TYPE_H
#define DRAW_TYPE_H
#include <vector>
#include "../Faxic_type.h"
#include <cmath>
namespace Faxic {

class Gbuffer {
    std::vector<RGB_t> buffer;
    int w = 0, h = 0;
public:
    Gbuffer(int _w, int _h) : w(_w), h(_h) {
        buffer.resize(w * h);
    };
    Gbuffer() {};
    ~Gbuffer() {};
    void resize(int _w, int _h) {
        w = _w; h = _h;
    };
    void clear() {
        buffer.assign(w * h, RGB_t({255, 255, 255}));
    }
    RGB_t &at(int x, int y) {
        return buffer.at(x + y * w);
    }
    const RGB_t &at(int x, int y) const {
        return buffer.at(x + y * w);
    }

    RGB_t get(int x, int y) {
        return buffer[x + y * w];
    }

    void setPixel(int x, int y, const RGB_t &color) {
        buffer[x + y * w] = color;
    }

    void setArea(Point _p1, Point _p2, const RGB_t &color) {
        int y1 = std::min(_p1.y, _p2.y);
        int y2 = std::max(_p1.y, _p2.y);
        int x1 = std::min(_p1.x, _p2.x);

        const int wid = abs(_p2.x - _p1.x);

        for(int y = y1;y < y2;++ y) {
            auto* start = buffer.data() + y * w + x1;
            std::fill(start, start + wid, color);
        }
    }


};

}

#endif //DRAW_TYPE_H
