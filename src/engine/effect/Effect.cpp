#include "Effect.h"

namespace MoleDemo
{
	using namespace mole_def;

	Effect::Effect(Timer* timer, Screen* screen) :
		timer{ timer },
		screen{ screen },
		buffer{}
	{

		ReserveBuffer();
	}

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
		pixelBuffer.assign(screen->GetPixelCount(), color);
	}

	rgbaColor Effect::GetPixel(Point2D p) {
		return GetPixel(GetPixelIndex(p));
	}

	rgbaColor Effect::GetPixel(index index) {
		return buffer[index];
	}
}

