export module renderables;

import definitions;
import effects;

namespace MoleDemo {

	export struct Layer;

	export class Transition;
	export class Cut;
	export class Fade;

}

struct MoleDemo::Layer : public Renderable {

	const BlendMode blend;
	Effect* const effect;

	Layer(BlendMode mode, Effect* effect) :
		blend{ mode },
		effect{ effect } {}
	~Layer() {
	}

	void Update(permille intensity, milliseconds deltaTime) override {
		effect->Update(intensity, deltaTime);
	}
	void Cache(StencilBuffer& mask) override {
		effect->Cache(mask);
	}
	rgbaColor GetPixel(Point2D point) override {
		return effect->GetPixel(point);
	}
	rgbaColor GetPixel(index index) override {
		return effect->GetPixel(index);
	}
	BlendMode GetBlend() override {
		return blend;
	}
	bool CheckStencil(index offset) override {
		// TODO buffer relevant content
		return true;
	}
};

class MoleDemo::Transition : public Renderable {
	const TransitionType type;
	milliseconds m_elapsed;
	const Timestamp time;
protected:
	Renderable* background;
	Renderable* foreground;
	Transition(Timestamp time, TransitionType type) :
		time{ time },
		type{ type } {}
	permille elapsed() const {
		return m_elapsed * permilleFactor / time.duration;
	}
public:
	virtual ~Transition() {}
	void Bind(Renderable* background, Renderable* foreground) {
		this->background = background;
		this->foreground = foreground;
	}
	void Update(permille intensity, milliseconds deltaTime) sealed {
		m_elapsed += deltaTime;
	}
	bool IsDone() {
		return m_elapsed > time.duration;
	}
	bool CheckStencil(index index) sealed {
		return true; //transitions by now are always be full screen
	}
};

class MoleDemo::Cut : public Transition {
	Renderable* ActiveLayer() {
		return IsDone() ? foreground : background;
	}
public:
	Cut(Timestamp time) :
		Transition{ time, TransitionType::Cut } {}
	~Cut() override {}
	void Cache(StencilBuffer& mask) override {
		background->Cache(mask);
		foreground->Cache(mask);
	}
	rgbaColor GetPixel(Point2D point) override {
		return ActiveLayer()->GetPixel(point);
	}
	rgbaColor GetPixel(index index) override {
		return ActiveLayer()->GetPixel(index);
	}
	BlendMode GetBlend() override {
		return ActiveLayer()->GetBlend();
	}
};

class MoleDemo::Fade : public Transition {
public:
	Fade(Timestamp time) :
		Transition{ time, TransitionType::Fade } {}
	~Fade() override {};
	void Cache(StencilBuffer& mask) override {
		background->Cache(mask);
		foreground->Cache(mask);
	}
	rgbaColor GetPixel(index index) override {

		Color next{ foreground->GetPixel(index) };
		rgbaColor result;

		if (!IsDone()) {
			Color base{ background->GetPixel(index) };
			result = base.lerp(next, elapsed()).rgba();
		}
		else {
			result = next.rgba();
		}

		return result;
	}
	rgbaColor GetPixel(Point2D point) override {

		rgbaColor result;
		Color next{ foreground->GetPixel(point) };

		if (!IsDone()) {
			Color base{ background->GetPixel(point) };
			result = base.lerp(next, elapsed()).rgba();
		}
		else {
			result = next.rgba();
		}

		return result;
	}
	BlendMode GetBlend() override {
		return background->GetBlend();
	}
};