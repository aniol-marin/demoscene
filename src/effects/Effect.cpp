module;

#include <cstdint>
#include <cstddef>

module effects;

namespace MoleDemo {
	Effect::Effect(Timer* timer, Screen* screen) :
		timer{ timer },
		screen{ screen },
		buffer{} {

		ReserveBuffer();
	}

	Effect::~Effect() {};

	index Effect::GetPixelIndex(Point2D& point) {
		return GetPixelIndex(point, buffer);
	}

	index Effect::GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer) {
		return (size_t)screen->w * (size_t)point.y + (size_t)point.x;
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
		buffer.reserve(screen->GetPixelCount());
		ClearBuffer(transparent);
	}

	void Effect::ClearBuffer(rgbaColor color) {
		ClearBuffer(color, buffer);
	}

	void Effect::ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer) {
		pixelBuffer.assign(size_t{ screen->GetPixelCount() }, color);
	}

	rgbaColor Effect::GetPixel(Point2D p) {
		return GetPixel(GetPixelIndex(p));
	}

	rgbaColor Effect::GetPixel(index index) {
		return buffer[index];
	}
}
