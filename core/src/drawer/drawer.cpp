//
// Created by AWAY on 25-4-22.
//

#include "drawer.h"

namespace Faxic {

Drawer::Drawer(halDisplay* display) {
	width = display->getWidth();
	height = display->getHeight();
	alpha = display->getAlpha();
	setAlpha(alpha);
	buffer.resize(width, height); // 初始化缓冲区
	this->display = display;
}

void Drawer::setColor(RGB_t color) {
    display->setColor(color);
}
void Drawer::setAlpha(uint8_t a) {
    this->alpha = a;
    display->setA(a);
}

void Drawer::flush() {
    // flush the buffer
	for(int x = 0;x < width;x ++) {
		for(int y = 0;y < height;y ++) {
			display->setColor(buffer.at(x, y));
			display->drawPixel(x, y);
		}
	}
	display->showCanvas();
}

void Drawer::clear() {
    // clear the buffer
	buffer.clear();
}

void Drawer::drawComponent(DrawBase* component) {
	component->draw(buffer);
}

}