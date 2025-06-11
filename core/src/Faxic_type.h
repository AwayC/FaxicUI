//
// Created by AWAY on 25-6-8.
//

#ifndef FAXIC_TYPE_H
#define FAXIC_TYPE_H
#include <stdint.h>
namespace Faxic
{

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

typedef struct
{
    int x, y;
} Point;

using RGBA_hex_t = uint32_t;

}


#endif //FAXIC_TYPE_H
