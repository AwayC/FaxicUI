//
// Created by AWAY on 25-6-8.
//

#ifndef DRAWBASE_H
#define DRAWBASE_H
#include "halDisplay.h"
#include "draw_buff.h"

namespace Faxic {

class DrawStyle {
protected:

public:
    DrawStyle() {}
    virtual ~DrawStyle() {}
};

class DrawBase {
protected:
    DrawStyle *style;
public:
    DrawBase(DrawStyle *_style) : style(_style) {};
    virtual ~DrawBase() = default;
    virtual void draw(Gbuffer &buf) = 0;

};

}

#endif //DRAWBASE_H
