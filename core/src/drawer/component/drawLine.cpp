//
// Created by AWAY on 25-6-8.
//

#include "drawLine.h"

namespace Faxic {

void DrawLine::draw(Gbuffer &buf) {
    auto *sty = static_cast<LineStyle*>(style);

    if(sty->getWidth() < 1) return;

    Point p1 = sty->getP1();
    Point p2 = sty->getP2();
    if(p1.x == p2.x && p1.y == p2.y) return;

	if(p1.y == p2.y) drawHorLine(buf);
	else if(p1.x == p2.x) drawVerLine(buf);
	else drawSkewLine(buf);




    return ;
}

void DrawLine::drawHorLine(Gbuffer &buf) {
	auto *sty = static_cast<LineStyle*>(style);


	uint32_t w = sty->getWidth() - 1;
	uint32_t w_helf = w >> 1;

	bool dashed = sty->getIsDash();
	Point p1 = sty->getP1();
	Point p2 = sty->getP2();

	p1.y -= w_helf;
	p2.y += w_helf;

	if(!dashed) {
        buf.setArea(p1, p2, sty->getColor());
	} else {

	}
}

void DrawLine::drawVerLine(Gbuffer &buf) {

}

void DrawLine::drawSkewLine(Gbuffer &buf) {

}

}