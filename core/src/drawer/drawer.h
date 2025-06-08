//
// Created by AWAY on 25-4-22.
//

#ifndef DRAWER_H
#define DRAWER_H

#include "halDisplay.h"
#include <vector>

namespace Faxic {

using Gbuffer_t = std::vector<RGB_t>;

class Drawer {
	halDisplay* display;
	int width;
	int height;
	RGB_t drawColor;
	uint8_t alpha;
	Gbuffer_t buffer; // 缓冲区

public:
	Drawer(halDisplay* display);
	~Drawer() {
		display->~halDisplay();
		delete display;
	}

	void drawPixel(int x, int y);
	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(int x1, int y1, int x2, int y2);
	void drawRoundRect(int x1, int y1, int x2, int y2, int r);
	void drawEllipse(int x1, int y1, int x2, int y2);
	void drawCircle(int x, int y, int r);
	void flush();
	void clear();
	void setColor(RGB_t color);
	void setAlpha(uint8_t a);

};

}


#endif //GRAPHICS_H
