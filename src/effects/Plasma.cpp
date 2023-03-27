import effects;

namespace MoleDemo {

	Plasma::Plasma(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
		ReserveBuffer(screen->w * screen->h);
	}

	Plasma::~Plasma() {
	}

	void Plasma::Load() {
		buildPalette(0);
		for (int j = 0; j < screen->h * 2; ++j) {
			for (int i = 0; i < screen->w * 2; ++i) {
				plasma1.push_back(64 + 63 * (sin((double)hypot(screen->h - j, screen->w - i) / 16)));
				plasma2.push_back((unsigned char)(64 + 63 * sin((float)i / (37 + 15 * cos((float)j / 74)))
					* cos((float)j / (31 + 11 * sin((float)i / 57)))));
			}
		}
	}

	void Plasma::Unload() {
	}
	void Plasma::Update(uint_fast16_t intensity) {

		accumulatedTime += intensity;
		// setup some nice colours, different every frame
		// this is a palette that wraps around itself, with different period sine
		// functions to prevent monotonous colours
		buildPalette(intensity);

		// move plasma with more sine functions :)
		Windowx1 = (screen->w / 2) + (int)(((screen->w / 2) - 1) * cos((double)accumulatedTime / 970));
		Windowx2 = (screen->w / 2) + (int)(((screen->w / 2) - 1) * sin((double)-accumulatedTime / 1140));
		Windowy1 = (screen->h / 2) + (int)(((screen->h / 2) - 1) * sin((double)accumulatedTime / 1230));
		Windowy2 = (screen->h / 2) + (int)(((screen->h / 2) - 1) * cos((double)-accumulatedTime / 750));
		// we only select the part of the precalculated buffer that we need
		src1 = Windowy1 * (screen->w * 2) + Windowx1;
		src2 = Windowy2 * (screen->w * 2) + Windowx2;

	}
	void Plasma::Cache(std::vector<bool>& mask) {
		int indexColor;
		for (uint16_t y = 0; y < screen->h; y++) {
			for (uint16_t x = 0; x < screen->w; x++) {

				indexColor = (plasma1[src1] + plasma2[src2]) % 256;
				PutPixel(Point2D{ x, y }, palette[indexColor].rgba());

				src1++; src2++;
			}
			// get the next line in the precalculated buffers
			src1 += screen->w; src2 += screen->w;
		}
	}

	void Plasma::buildPalette(uint16_t time) {
		for (int i = 0; i < 256; i++)
		{
			palette[i].SetRGBA(
				(unsigned char)(128 + 127 * cos(i * PI / 128 + (double)time / 740)),
				(unsigned char)(128 + 127 * sin(i * PI / 128 + (double)time / 630)),
				(unsigned char)(128 - 127 * cos(i * PI / 128 + (double)time / 810))
			);
		}

	}
}