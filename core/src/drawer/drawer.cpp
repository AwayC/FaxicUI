//
// Created by AWAY on 25-4-22.
//

#include "drawer.h"

namespace Faxic {

Drawer::Drawer(halDisplay* display) {
	width = display->getWidth();
	height = display->getHeight();
	RGB_t color = display->getColor();
	alpha = display->getAlpha();
	buffer.resize(width * height);
}

void Drawer::setColor(RGB_t color) {
    this->drawColor = color; // set color
}
void Drawer::setAlpha(uint8_t a) {
    this->alpha = a;
}

void Drawer::flush() {
    // flush the buffer
	for(int x = 0;x < width;x ++) {
		for(int y = 0;y < height;y ++) {
			display->setColor(buffer[x + y * width]);
			display->drawPixel(x, y);
		}
	}
	display->showCanvas();
}

}