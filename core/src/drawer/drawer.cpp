//
// Created by AWAY on 25-4-22.
//

#include "drawer.h"

#include <cassert>

#include "iostream"

namespace Faxic {

Drawer::Drawer(halDisplay* display) {
	assert(display != nullptr);
	this->display = display;
	width = display->getWidth();
	height = display->getHeight();
	alpha = display->getAlpha();
	buffer.resize(width, height); // 初始化缓冲区

	std::cout << "Drawer Created" << std::endl;
}

void Drawer::setColor(RGB_t color) {
	assert(this->display != nullptr);
    display->setColor(color);
}
void Drawer::setAlpha(uint8_t a) {
	assert(this->display != nullptr);
    this->alpha = a;
    display->setA(a);
}

void Drawer::flush() {
    // flush the buffer
	assert(this->display != nullptr);
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