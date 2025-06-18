//
// Created by AWAY on 25-6-8.
//

#include "drawLine.h"

#include <iostream>
#include <ostream>

namespace Faxic {

void DrawLine::draw(Gbuffer &buf) {
    auto *sty = static_cast<LineStyle*>(style);

    if(sty->getWidth() < 1) return;

    if(p1.x == p2.x && p1.y == p2.y) return;

	if(p1.y == p2.y) drawHorLine(buf);
	else if(p1.x == p2.x) drawVerLine(buf);
	else drawSkewLine(buf);

	if(sty->getRoundEnd() || sty->getRoundStart()) {

	}




    return ;
}

void DrawLine::drawHorLine(Gbuffer &buf) {
	auto *sty = static_cast<LineStyle*>(style);

	uint32_t w = sty->getWidth() - 1;
	uint32_t w_helf0 = w >> 1;
	uint32_t w_helf1 = w_helf0 + (w & 1);

	bool dashed = sty->getIsDash();

	int x1 = (int)std::min(p1.x, p2.x);
	int x2 = (int)std::max(p1.x, p2.x);
	int y1 = (int)p1.y - w_helf0;
	int y2 = (int)p1.y + w_helf1;


	if(!dashed) {
        buf.setArea(x1, y1, x2, y2, sty->getColor());
	} else {
		int dash_start = x1 % (sty->getDashWidth() + sty->getDashGap()) + 1;
		w ++;
		int dash_cnt = dash_start;
		for(int x = x1; x <= x2;x ++, dash_cnt ++) {
			if(dash_cnt <= sty->getDashWidth()) {
				int diff = sty->getDashWidth() - dash_cnt;
				buf.setArea(x, y1, std::min(diff + x, x2), y2, sty->getColor());
				x += diff;
				dash_cnt += diff;
			} else {
				int diff = sty->getDashWidth() + sty->getDashGap() - dash_cnt;
				x += diff;
				dash_cnt = 0;
			}
		}
	}
}

void DrawLine::drawVerLine(Gbuffer &buf) {
	auto *sty = static_cast<LineStyle*>(style);

	uint32_t w = sty->getWidth() - 1;
	uint32_t w_helf0 = w >> 1;
	uint32_t w_helf1 = w_helf0 + (w & 1);

	bool dashed = sty->getIsDash();

	int x1 = (int)p1.x - w_helf1;
	int x2 = (int)p1.x + w_helf0;
	int y1 = (int)std::min(p1.y, p2.y);
	int y2 = (int)std::max(p1.y, p2.y);


	if(!dashed) {
        buf.setArea(x1, y1, x2, y2, sty->getColor());
	} else {
		int dash_start = y1 % (sty->getDashWidth() + sty->getDashGap()) + 1;
		w ++;
		int dash_cnt = dash_start;
		for(int y = y1;y <= y2;y ++, dash_cnt ++) {
			if(dash_cnt <= sty->getDashWidth()) {
				int diff = sty->getDashWidth() - dash_cnt;
				buf.setArea(x1, y, x2, std::min(diff + y, y2), sty->getColor());
				y += diff;
				dash_cnt += diff;
			} else {
				int diff = sty->getDashWidth() + sty->getDashGap() - dash_cnt;
				y += diff;
				dash_cnt = 0;
			}
		}
	}
}

void DrawLine::drawSkewLine(Gbuffer &buf) {
	auto *sty = static_cast<LineStyle*>(style);

	if (p1.y > p2.y) std::swap(p1, p2);

	int xdiff = p2.x - p1.x;
	int ydiff = p2.y - p1.y;
	bool flat = std::abs(xdiff) > std::abs(ydiff);

	static const uint8_t wcorr[] = {
		128, 128, 128, 129, 129, 130, 130, 131,
        132, 133, 134, 135, 137, 138, 140, 141,
        143, 145, 147, 149, 151, 153, 155, 158,
        160, 162, 165, 167, 170, 173, 175, 178,
        181,
	};

	int w = sty->getWidth();
	int wcorr_i = 0;
	if(flat) wcorr_i = (std::abs(ydiff) << 5) / std::abs(xdiff);
	else wcorr_i = (std::abs(xdiff) << 5) / std::abs(ydiff);

	w = (w * wcorr[wcorr_i] + 63) >> 7;
	w --;
	std::cerr << "w = " << w << std::endl;
	int w_half0 = w >> 1;
	int w_half1 = w_half0 + (w & 0x1);


	int y1 = std::min(p1.y, p2.y) - w;
	int y2 = std::max(p1.y, p2.y) + w;

	int preX1 = -1, preX2 = -1, lastLineY = y1;

	auto mask = [&](int y) {
		int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
		if(flat) {
			if (xdiff > 0)
			{
				l1 = p1.x + (y - p1.y - w_half0) * xdiff / ydiff;
				r1 = p1.x + (y - p1.y + w_half1) * xdiff / ydiff;
			} else
			{
				l1 = p1.x + (y - p1.y + w_half1) * xdiff / ydiff;
				r1 = p1.x + (y - p1.y - w_half0) * xdiff / ydiff;
			}
		} else {
			l1 = p1.x - w_half0 + (y - p1.y ) * xdiff / ydiff;
			r1 = l1 + w;
		}

		if(xdiff < 0) {
			l2 = (p2.y - y) * ydiff / xdiff + p2.x;
			r2 = (p1.y - y) * ydiff / xdiff + p1.x;
		} else {
			l2 = (p1.y - y) * ydiff / xdiff + p1.x;
			r2 = (p2.y - y) * ydiff / xdiff + p2.x;
		}

		int l = std::max(l1, l2);
		int r = std::min(r1, r2);

		if(l > r)
			return Point({-1, -1});

		return Point({l, r});
	};

	for(int y = y1;y <= y2;y ++) {
		Point p = mask(y);
#if 1
		if (preX1 == p.x && preX2 == p.x)
		{
			continue;
		}

		if (preX1 == -1 && preX2 == -1)
		{
			lastLineY = y;
			preX1 = p.x, preX2 = p.y;
			continue;
		}
		buf.setArea(preX1, lastLineY, preX2, y - 1, sty->getColor());
		preX1 = p.x, preX2 = p.y;
		lastLineY = y;
#else
		if (p.x != -1 && p2.x != -1)
		buf.setArea(p.x, y, p.y, y, sty->getColor());
#endif

	}
#if 0
	buf.setPixel(p2.x, p2.y, RGB_RED);
	buf.setPixel(p1.x, p1.y, RGB_GREEN);
#endif
}

}
