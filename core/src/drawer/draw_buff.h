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
        buffer.resize(w * h); // 重新分配内存
    };

    void clear() {
        buffer.assign(w * h, RGB_t({255, 255, 255}));
    }

    RGB_t &at(int x, int y) {
        if (x < 0 || x >= w || y < 0 || y >= h) return buffer.at(0);
        return buffer.at(x + y * w);
    }

    [[nodiscard]] const RGB_t &at(int x, int y) const {
        if (x < 0 || x >= w || y < 0 || y >= h) return buffer.at(0);
        return buffer.at(x + y * w);
    }

    RGB_t get(int x, int y) {
        if (x < 0 || x >= w || y < 0 || y >= h) return {255, 255, 255};
        return buffer[x + y * w];
    }

    void setPixel(int x, int y, const RGB_t &color) {
        if (x < 0 || x >= w || y < 0 || y >= h) return;
        buffer[x + y * w] = color;
    }

    void setArea(Point _p1, Point _p2, const RGB_t &color) {
        int y1 = std::min(_p1.y, _p2.y);
        int y2 = std::max(_p1.y, _p2.y);
        int x1 = std::min(_p1.x, _p2.x);
        int x2 = std::max(_p1.x, _p2.x);

        const int wid = abs(_p2.x - _p1.x) + 1;

        auto mask = [&]()
        {
            if (x2 < 0 || x1 > w) return false;
            if (y2 < 0 || y1 > h) return false;
            y1 = std::max(y1, 0);
            y2 = std::min(w, y2);
            x1 = std::max(x1, 0);
            x2 = std::max(w, x2);

            return true;
        };

        if (!mask()) return; // 超出边界

        for(int y = y1;y <= y2;++ y) {
            auto* start = buffer.data() + y * w + x1;
            std::fill(start, start + wid, color);
        }
    }

    void setArea(int x1, int y1, int x2, int y2, const RGB_t &color) {
        int y1_ = std::min(y1, y2);
        int y2_ = std::max(y1, y2);
        int x1_ = std::min(x1, x2);
        int x2_ = std::max(x1, x2);

        auto mask = [&]()
        {
            if (x2_ < 0 || x1_ >= w) return false;
            if (y2_ < 0 || y1_ >= h) return false;
            y1_ = std::max(y1_, 0);
            y2_ = std::min(w, y2_);
            x1_ = std::max(x1_, 0);
            x2_ = std::max(w, x2_);

            return true;
        };

        if (!mask()) return; // 超出边界

        const int wid = abs(x2 - x1) + 1;
        for(int y = y1_; y <= y2_; ++ y) {
            auto* start = buffer.data() + y * w + x1_;
            std::fill(start, start + wid, color);
        }
    }


};

}

#endif //DRAW_TYPE_H
