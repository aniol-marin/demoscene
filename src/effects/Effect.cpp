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

	void Effect::PutPixel(Point2D point, rgbaColor color) {

		rgbaColor& pixel = buffer.at(GetPixelIndex(point));
		pixel = color;
	}

	void Effect::ReserveBuffer() {
		ClearBuffer(0x0);
		//buffer.reserve(size);
	}

	void Effect::ClearBuffer(rgbaColor color) {
		ClearBuffer(color, buffer);
	}

	void Effect::ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer) {
		pixelBuffer.assign((size_t)screen->w * (size_t)screen->h, color);
	}

	rgbaColor Effect::GetPixel(Point2D p) {
		return GetPixel(GetPixelIndex(p));
	}

	rgbaColor Effect::GetPixel(index index) {
		return buffer[index];
	}

	PixelBuffer& Effect::GetBuffer() {
		return buffer;
	}
}