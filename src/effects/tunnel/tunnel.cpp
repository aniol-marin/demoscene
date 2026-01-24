#include "tunnel.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

namespace MoleDemo
{
    using namespace mole_def;

    Tunel::Tunel(Timer* timer, Screen* screen) : du(), dv(), speedU(128), speedV(32), Effect(timer, screen) {}

    /*
     * position of the centre of the hole along the X axis
     */
    float get_x_pos(float f)
    {
        return -16 * std::sin(f * PI / 256);
    };

    /*
     * position of the centre of the hole along the Y axis
     */
    float get_y_pos(float f)
    {
        return -16 * std::sin(f * PI / 256);
    };

    /*
     * size of the hole
     */
    float get_radius(float f)
    {
        return 128;
    };

    void Tunel::Load()
    {

        texture->Load();

        uv.reserve(get_screen()->GetPixelCount());
        offset1D half(2);
        Offset2D center =
                Offset2D(static_cast<offset1D>(get_screen()->w) / half, static_cast<offset1D>(get_screen()->h) / half);
        for (offset1D j = -center.y; j < center.y; ++j)
        {
            for (offset1D i = -center.x; i < center.x; ++i)
            {

                // get coordinates of ray that projects through this pixel
                float dx = (float) i / get_screen()->h;
                float dy = (float) -j / get_screen()->h;
                float dz = 1;
                // normalize them
                float d = 20 / std::sqrt(dx * dx + dy * dy + 1);
                dx *= d;
                dy *= d;
                dz *= d;
                // start interpolation at origin
                float x = 0;
                float y = 0;
                float z = 0;
                // set original precision
                d = 16;
                // interpolate along ray
                while (d > 0)
                {
                    // continue until we hit a wall
                    while (((x - get_x_pos(z)) * (x - get_x_pos(z)) + (y - get_y_pos(z)) * (y - get_y_pos(z)) <
                            get_radius(z)) &&
                           (z < 1024))
                    {
                        x += dx;
                        y += dy;
                        z += dz;
                    };
                    // reduce precision and reverse direction
                    x -= dx;
                    dx /= 2;
                    y -= dy;
                    dy /= 2;
                    z -= dz;
                    dz /= 2;
                    d -= 1;
                }
                // calculate the texture coordinates
                x -= get_x_pos(z);
                y -= get_y_pos(z);
                float ang = std::atan2(y, x) * 256 / PI;
                unsigned char u = (unsigned char) ang;
                unsigned char v = (unsigned char) z;
                // store texture coordinates
                uv.push_back(Point2D(u, v));
            }
        }
    }

    void Tunel::Unload() {}

    void Tunel::Update(permille intensity, milliseconds delta)
    {
        du = (du + intensity / speedU) % get_screen()->w;
        dv = (dv + delta / speedV) % get_screen()->h;
    }

    void Tunel::Cache(StencilBuffer& mask)
    {

        for (point1D y; y < get_screen()->h; ++y)
        {
            for (point1D x; x < get_screen()->w; ++x)
            {
                Point2D mapping(uv[get_screen()->GetIndex(Point2D(x, y))]);
                point1D u(mapping.x + du);
                point1D v(mapping.y + dv);
                std::cerr << "deactivated\n";
                exit(1);
                /*
        Color base(texture->GetMappedUV(static_cast<offset1D>(u), static_cast<offset1D>(v)));
        PutPixel(Offset2D(x, y), base.rgba());
                */
            }
        }
    }

    void Tunel::buildPalette(short int time) {}

    void Tunel::AssignTexture(Texturable* texture, Id id = 0)
    {
        this->texture = texture;
    }

    rgbaColor Tunel::GetMappedUV(CoordinateUV uv)
    {
        Point2D mapped(std::abs((int) (uv.u * permilleFactor() / get_screen()->w)) % get_screen()->w,
                       std::abs((int) (uv.v * permilleFactor() / get_screen()->h)) % get_screen()->h);
        return Effect::GetPixel(mapped);
    }
}
