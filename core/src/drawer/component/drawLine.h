//
// Created by AWAY on 25-6-8.
//

#ifndef DRAWLINE_H
#define DRAWLINE_H

#include "../drawBase.h"
#include "../../Faxic_type.h"
#include <cassert>

namespace Faxic {

class LineStyle : public DrawStyle {
	RGB_t color;
	uint32_t width = 1;
	uint32_t dashWidth = 0;
	uint32_t dashGap = 0;
	bool roundStart = false, roundEnd = false;

public:
	enum LineType {
		Solid,
		Dash
	};

	LineStyle(Point _p1, Point _p2, RGB_t _color) : color(_color) {};
	~LineStyle() {}
	void setWidth(uint32_t _width) { width = _width; }
	void setDash(uint32_t _dashWidth, int _dashGap) { dashWidth = _dashWidth, dashGap = _dashGap; }
	void setStRound(bool rd) { roundStart = rd; }
	void setEdRound(bool rd) { roundEnd = rd; }
	void setColor(RGB_t _color) { color = _color; }

	RGB_t getColor() { return color; }
	uint32_t getWidth() { return width; }
	bool getIsDash() {
		bool IsDash = dashWidth && dashGap;
		return IsDash;
	}
	uint32_t getDashWidth() { return dashWidth; }
	uint32_t getDashGap() { return dashGap; }
	bool getRoundStart() { return roundStart; }
	bool getRoundEnd() { return roundEnd; }




};

class DrawLine : public DrawBase {
	Point p1, p2;
public:
    DrawLine(Point _p1, Point _p2, LineStyle *_style) : p1(_p1), p2(_p2), DrawBase(_style) {
    	assert(dynamic_cast<LineStyle*>(_style) != nullptr);
    };
    ~DrawLine() {}
    void draw(Gbuffer &buf) override; // 绘制
	void setP1(Point _p1) { p1 = _p1; }
	void setP2(Point _p2) { p2 = _p2; }

	Point getP1() { return p1; }
	Point getP2() { return p2; }

private:
    void drawHorLine(Gbuffer &buf);
    void drawVerLine(Gbuffer &buf);
    void drawSkewLine(Gbuffer &buf);
};

}





#endif //DRAWLINE_H
