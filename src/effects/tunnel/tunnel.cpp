module tunnel;

namespace MoleDemo
{
    Tunel::Tunel(Timer* timer, Screen* screen) : du{}, dv{}, speedU{ 128 }, speedV{ 32 }, Effect{ timer, screen } {}

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

        uv.reserve(screen->GetPixelCount());
        offset1D half{ 2 };
        Offset2D center{ static_cast<offset1D>(screen->w) / half, static_cast<offset1D>(screen->h) / half };
        for (offset1D j{ -center.y }; j < center.y; ++j)
        {
            for (offset1D i{ -center.x }; i < center.x; ++i)
            {

                // get coordinates of ray that projects through this pixel
                float dx = (float) i / screen->h;
                float dy = (float) -j / screen->h;
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
                uv.push_back(Point2D{ u, v });
            }
        }
    }

    void Tunel::Unload() {}

    void Tunel::Update(permille intensity, milliseconds delta)
    {
        du = (du + intensity / speedU) % screen->w;
        dv = (dv + delta / speedV) % screen->h;
    }

    void Tunel::Cache(StencilBuffer& mask)
    {

        for (point1D y{}; y < screen->h; ++y)
        {
            for (point1D x{}; x < screen->w; ++x)
            {
                Point2D mapping{ uv[screen->GetIndex({ x, y })] };
                point1D u{ mapping.x + du };
                point1D v{ mapping.y + dv };
                Color base{ texture->GetMappedUV({ static_cast<offset1D>(u), static_cast<offset1D>(v) }) };
                PutPixel({ x, y }, base.rgba());
            }
        }
    }

    void Tunel::buildPalette(std::uint16_t time) {}

    void Tunel::AssignTexture(std::unique_ptr<Texturable> texture, Id id = 0)
    {
        this->texture = std::move(texture);
    }
}
