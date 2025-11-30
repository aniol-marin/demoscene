export module effect;

import std;
export import definitions;
export import timer;

using namespace mole_def;

namespace MoleDemo
{
	export class Effect;
}

class MoleDemo::Effect
{
	PixelBuffer buffer;

protected:
	Timer* const timer;
	Screen* const screen;

	Effect(Timer* timer, Screen* screen);

	/*
	index GetPixelIndex(Point2D& point);
	index GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
	rgbaColor GetColorAt(Point2D point, PixelBuffer& pixelBuffer);
	void PutPixel(Point2D point, rgbaColor color);
	void PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer);
	*/

	void ReserveBuffer();
	void ClearBuffer(rgbaColor color);
	void ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer);

	/*
public:

	virtual rgbaColor GetPixel(Point2D p);
	virtual rgbaColor GetPixel(index index);

	virtual void Unload() = 0;

	virtual void Update(permille intensity, milliseconds delta) = 0;

	virtual void Cache(StencilBuffer& mask) = 0;
	 */
public:
	Effect() = delete;
	virtual ~Effect() = default;
	virtual rgbaColor GetPixel(Point2D p){ return {}; }
	virtual rgbaColor GetPixel(index index){ return {}; }
	virtual void Cache(StencilBuffer& mask) {}
	virtual void Update(permille intensity, milliseconds delta) {}
	virtual void Load() = 0;
	virtual void Unload() =0;
};

