module effects;

namespace MoleDemo {
	Effect::Effect(Timer* timer, Screen* screen) :
		timer{ timer },
		screen{ screen },
		buffer{} {}

	Effect::~Effect() {};

	uint_fast16_t Effect::GetPixelIndex(Point2D& point) {
		return GetPixelIndex(point, buffer);
	}

	uint_fast16_t Effect::GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer) {
		return (size_t)screen->w * (size_t)point.y + (size_t)point.x;
	}

	void Effect::PutPixel(Point2D point, uint32_t color) {
		size_t index = GetPixelIndex(point);
		if (index > buffer.size()) {
			int d = 0;
		}
		uint32_t& position = buffer.at(GetPixelIndex(point));
		position = color;
	}

	void Effect::ReserveBuffer(size_t size) {
		ClearBuffer(0x0);
		//buffer.reserve(size);
	}

	void Effect::ClearBuffer(uint32_t color) {
		ClearBuffer(color, buffer);
	}

	void Effect::ClearBuffer(uint32_t color, PixelBuffer& pixelBuffer) {
		pixelBuffer.assign((size_t)screen->w * (size_t)screen->h, color);
	}

	uint32_t Effect::GetPixel(Point2D p) {
		return buffer[p.y];
	}

	PixelBuffer& Effect::GetBuffer() {
		return buffer;
	}
}