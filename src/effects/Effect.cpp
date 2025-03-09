module;

#include <exception>

export module effect;

import definitions;
import timer;

namespace MoleDemo {

	export class Effect;
}

class MoleDemo::Effect {

	PixelBuffer buffer;

protected:
	Timer* const timer;
	Screen* const screen;

	Effect(Timer* timer, Screen* screen);

	index GetPixelIndex(Point2D& point);
	index GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
	rgbaColor GetColorAt(Point2D point, PixelBuffer& pixelBuffer);
	void PutPixel(Point2D point, rgbaColor color);
	void PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer);

	void ReserveBuffer();
	void ClearBuffer(rgbaColor color);
	void ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer);

public:

	virtual ~Effect();

	virtual rgbaColor GetPixel(Point2D p);
	virtual rgbaColor GetPixel(index index);

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(permille intensity, milliseconds delta) = 0;

	virtual void Cache(StencilBuffer& mask) = 0;
};

namespace MoleDemo {
	Effect::Effect(Timer* timer, Screen* screen) :
		timer{ timer },
		screen{ screen },
		buffer{}
	{

		ReserveBuffer();
	}

	Effect::~Effect() {};

	index Effect::GetPixelIndex(Point2D& point) {
		return GetPixelIndex(point, buffer);
	}

	index Effect::GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer) {
		return (pixel_count)screen->w * (pixel_count)point.y + (pixel_count)point.x;
	}

	rgbaColor Effect::GetColorAt(Point2D point, PixelBuffer& pixelBuffer) {
		return pixelBuffer[GetPixelIndex(point, pixelBuffer)];
	}

	void Effect::PutPixel(Point2D point, rgbaColor color) {
		PutPixel(point, color, buffer);
	}

	void Effect::PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer) {

		rgbaColor& pixel = buffer.at(GetPixelIndex(point));
		pixel = color;
	}

	void Effect::ReserveBuffer() {
		/*
		buffer.reserve(screen->GetPixelCount());
		*/
		ClearBuffer(transparent);
	}

	void Effect::ClearBuffer(rgbaColor color) {
		ClearBuffer(color, buffer);
	}

	void Effect::ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer) {
		/*
		pixelBuffer.assign(screen->GetPixelCount(), color);
		*/
		throw std::exception();
	}

	rgbaColor Effect::GetPixel(Point2D p) {
		return GetPixel(GetPixelIndex(p));
	}

	rgbaColor Effect::GetPixel(index index) {
		return buffer[index];
	}
}

