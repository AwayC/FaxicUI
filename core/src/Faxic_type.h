//
// Created by AWAY on 25-6-8.
//

#ifndef FAXIC_TYPE_H
#define FAXIC_TYPE_H
#include <stdint.h>
namespace Faxic
{

struct RGB_t
{
    uint8_t r, g, b;
    RGB_t() = default;
    RGB_t(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {};
};

#define RGB_WHITE RGB_t({255, 255, 255})
#define RGB_BLACK RGB_t({0, 0, 0})
#define RGB_RED RGB_t({255, 0, 0})
#define RGB_GREEN RGB_t({0, 255, 0})
#define RGB_BLUE RGB_t({0, 0, 255})
#define RGB_MAGENTA RGB_t({255, 0, 255})
#define RGB_CYAN RGB_t({0, 255, 255})
#define RGB_YELLOW RGB_t({255, 255, 0})    // 黄色
#define RGB_ORANGE RGB_t({255, 165, 0})     // 橙色
#define RGB_PURPLE RGB_t({128, 0, 128})     // 紫色
#define RGB_GRAY RGB_t({128, 128, 128})    // 灰色
#define RGB_PINK RGB_t({255, 192, 203})     // 粉色
#define RGB_NAVY RGB_t({0, 0, 139})

struct Point
{
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) {};
};

using RGBA_hex_t = uint32_t;

}


#endif //FAXIC_TYPE_H
