#ifndef MOLE_EFFECT_H
#define MOLE_EFFECT_H

#include "definitions.h"
#include "timer.h"

using namespace mole_def;

namespace MoleDemo
{
    class Effect
    {
        PixelBuffer buffer;

    protected:
        Timer* const timer;
        Screen* const screen;

        Effect(Timer* timer, Screen* screen);

        index_t GetPixelIndex(Point2D& point);
        index_t GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
        rgbaColor GetColorAt(Point2D point, PixelBuffer& pixelBuffer);
        void PutPixel(Point2D point, rgbaColor color);
        void PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer);

        void ReserveBuffer();
        void ClearBuffer(rgbaColor color);
        void ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer);

    public:
        virtual ~Effect();

        virtual rgbaColor GetPixel(Point2D p);
        virtual rgbaColor GetPixel(index_t index);

        virtual void Load() = 0;
        virtual void Unload() = 0;

        virtual void Update(permille intensity, milliseconds delta) = 0;

        virtual void Cache(StencilBuffer& mask) = 0;
    };
}

#endif
