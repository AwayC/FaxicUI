//
// Created by AWAY on 25-4-22.
//

#ifndef DRAWER_H
#define DRAWER_H

#include "halDisplay.h"
#include <vector>
#include "drawBase.h"
#include "draw_buff.h"
#include "../Faxic_profiler.h"

namespace Faxic {

class Drawer {
	halDisplay* display;
	int width;
	int height;
	uint8_t alpha;
	Gbuffer buffer; // 缓冲区

public:
	Drawer(halDisplay* display);
	~Drawer() {
		display->~halDisplay();
		delete display;
	}

	void drawComponent(DrawBase* component); // 绘制组件
	void flush();
	void clear();
	void setColor(RGB_t color);
	void setAlpha(uint8_t a);

};

}


#endif //GRAPHICS_H
