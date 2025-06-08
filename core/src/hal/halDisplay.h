//
// Created by AWAY on 25-6-7.
//

#ifndef HALDISPLAY_H
#define HALDISPLAY_H

#include <stdint.h>

namespace Faxic
{
	typedef struct
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	} RGB_t;

	class halDisplay {
	protected:
		int width;
		int height;
		RGB_t drawColor;
		uint8_t alpha;

	public:
		halDisplay(int wid, int hei) : width(wid), height(hei) {};
		virtual ~halDisplay() {};
		virtual bool init() = 0;
		virtual void deinit() = 0;
		virtual void drawPixel(int x, int y) = 0;
		virtual void drawRect(int x, int y, int w, int h) = 0;
		virtual void clearCanvas() = 0;
		virtual void delay(int ms) = 0;
		virtual bool checkEvent() = 0;
		virtual int getTick() = 0;
		virtual void showCanvas() const = 0;
		virtual void setColor(RGB_t color) = 0;
		virtual void setA(uint8_t a) = 0;

		int getWidth() { return width; }
		int getHeight() { return height; }
		RGB_t getColor() { return drawColor; }
		uint8_t getAlpha() { return alpha; }

	};
}

#endif //HAL_H
