export module render;

import std;
import definitions;
import effect;
import renderables;
import sdl_wrapper;

using namespace mole_def;
namespace MoleDemo {

	using size_t = std::size_t;
	export class RenderManager;

	class RenderQueue;
	struct Blending;
	struct OverrideBlend;
	struct AlphaBlend;
}

struct  MoleDemo::Blending {
	const BlendMode mode;
	virtual ~Blending() {}
	virtual rgbaColor Blend(const rgbaColor base, const rgbaColor next) = 0;
	virtual rgbaColor Blend(Color& base, Color& next) = 0;
protected:
	Blending(BlendMode mode) :
		mode{ mode } {}
};

struct  MoleDemo::OverrideBlend : public Blending {
	OverrideBlend() :
		Blending{ BlendMode::Override } {}
	~OverrideBlend() {}
	rgbaColor Blend(const rgbaColor base, const rgbaColor next) override {
		return next;
	}
	rgbaColor Blend(Color& base, Color& next) override {
		return next.rgba();
	};

};

struct  MoleDemo::AlphaBlend : public  MoleDemo::Blending {
	AlphaBlend() :
		Blending{ BlendMode::AlphaBlend } {}
	~AlphaBlend() {}

	rgbaColor Blend(const rgbaColor base, const rgbaColor next) override {
		Color ref_base{ base };
		Color ref_next{ next };
		return Blend(ref_base, ref_next);
	};
	rgbaColor Blend(Color& base, Color& next)  override {

		tempChannel aB{ base.a() };
		tempChannel rB{ base.r() };
		tempChannel gB{ base.g() };
		tempChannel bB{ base.b() };

		tempChannel aN{ next.a() };
		tempChannel rN{ next.r() };
		tempChannel gN{ next.g() };
		tempChannel bN{ next.b() };

		channel a{ (channel)(aN + (0xFF - aN) * aB / 0xFF) };
		channel r{ (channel)(a == 0x0 ? 0x0 : (rN * aN + rB * (0xFF - aN)) / a) };
		channel g{ (channel)(a == 0x0 ? 0x0 : (gN * aN + gB * (0xFF - aN)) / a) };
		channel b{ (channel)(a == 0x0 ? 0x0 : (bN * aN + bB * (0xFF - aN)) / a) };

		return Color(r, g, b, a).rgba();
	};
};
