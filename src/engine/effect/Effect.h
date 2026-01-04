#ifndef MOLE_EFFECT_H
#define MOLE_EFFECT_H

#include "definitions.h"
#include "timer.h"

using namespace mole_def;

namespace MoleDemo
{
    class Effect
    {

    protected:
        Timer* const timer;

        Effect(Timer* timer, Screen* screen);

        static index_t GetPixelIndex(Point2D& point);
        static index_t GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
        rgbaColor GetColorAt(Point2D point, PixelBuffer& pixelBuffer);
        static void PutPixel(Point2D point, rgbaColor color);
        static void PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer);
        Screen* get_screen() const;

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
