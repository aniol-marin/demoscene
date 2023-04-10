module effects;

namespace MoleDemo {
	Fire::Fire(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
	}

	Fire::~Fire() {
	}

	void Fire::Load() {
		srand(0);
		ClearBuffer(0x55005500);
		ClearBuffer(0x55005500, first);
		ClearBuffer(0x55005500, second);
	}

	void Fire::Unload() {
	}

	void Fire::Update(permille intensity) {
	}

	void Fire::Cache(StencilBuffer& mask) {
	}

	void  Fire::GeneratePalette() {

	}

	void  Fire::GenerateHotspots() {

		point1D start{ rand() % screen->w };
		point1D end{ std::min(start + (point1D)(rand() % 256), screen->w) };
		Color random{};

		for (uint_fast8_t i = start; i < end; ++i) {

			point1D i1{ GetPixel(Point2D{i, (point1D)(screen->h - 1)}) };
			point1D i2{ GetPixel(Point2D{i, (point1D)(screen->h - 2)}) };
			point1D i3{ GetPixel(Point2D{i, (point1D)(screen->h - 3)}) };

			random.SetRGBA(
				(channel)(200 + (rand() % 55)),
				(channel)(50 + (rand() % 55)),
				(channel)(50 + (rand() % 55)));
			first[i1] = random.rgba();
			first[i2] = random.rgba();
			first[i3] = random.rgba();

		}
	}

	void Fire::FilterPrevious() {

	}
}

