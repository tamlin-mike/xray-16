#include "xrCore/_color.h"
#include "xrCore/_bitwise.h" // iFloor
#include "xrCore/_std_extensions.h" // _sqrt
#include "xrCore/xrDebug_macros.h"

namespace {
inline s32 clamp_to_8bit(const s32 val) noexcept
{
	if (val < 0) return 0;
	if (val > 255) return 255;
	return val;
}
}

u32 color_argb_f(f32 a, f32 r, f32 g, f32 b) noexcept
{
#if 0
	s32 _r = clampr(iFloor(r*255.f), 0, 255);
	s32 _g = clampr(iFloor(g*255.f), 0, 255);
	s32 _b = clampr(iFloor(b*255.f), 0, 255);
	s32 _a = clampr(iFloor(a*255.f), 0, 255);
#else
	s32 _r = clamp_to_8bit(iFloor(r*255.f));
	s32 _g = clamp_to_8bit(iFloor(g*255.f));
	s32 _b = clamp_to_8bit(iFloor(b*255.f));
	s32 _a = clamp_to_8bit(iFloor(a*255.f));
#endif
	return color_argb(_a, _r, _g, _b);
}

//////////////////////////////////////////////////////////////////


Fcolor& Fcolor::set(u32 dw) noexcept
{
	const float f = float(1.0) / float(255.0);
	a = f * float((dw >> 24) & 0xff);
	r = f * float((dw >> 16) & 0xff);
	g = f * float((dw >> 8) & 0xff);
	b = f * float((dw >> 0) & 0xff);
	return *this;
};
//Fcolor& Fcolor::set(float _r, float _g, float _b, float _a)
//{
//	r = _r; g = _g; b = _b; a = _a;
//	return *this;
//};
Fcolor& Fcolor::set(const Fcolor& rhs) noexcept
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	a = rhs.a;
	return *this;
};
u32 Fcolor::get() const noexcept { return color_rgba_f(r, g, b, a); }
u32 Fcolor::get_windows() const noexcept // Get color as a Windows DWORD value.
{
	u8 _a, _r, _g, _b;
	_a = (u8)(a*255.f);
	_r = (u8)(r*255.f);
	_g = (u8)(g*255.f);
	_b = (u8)(b*255.f);
	return ((u32)(_a << 24) | (_b << 16) | (_g << 8) | (_r));
};
Fcolor& Fcolor::set_windows(u32 dw) noexcept // Set color from a Windows DWORD color value.
{
	const float f = 1.0f / 255.0f;
	a = f * (float)(u8)(dw >> 24);
	b = f * (float)(u8)(dw >> 16);
	g = f * (float)(u8)(dw >> 8);
	r = f * (float)(u8)(dw >> 0);
	return *this;
};
Fcolor& Fcolor::adjust_contrast(float f) noexcept // >1 - contrast will be increased
{
	r = 0.5f + f * (r - 0.5f);
	g = 0.5f + f * (g - 0.5f);
	b = 0.5f + f * (b - 0.5f);
	return *this;
};
Fcolor& Fcolor::adjust_contrast(const Fcolor& in, float f) noexcept // >1 - contrast will be increased
{
	r = 0.5f + f * (in.r - 0.5f);
	g = 0.5f + f * (in.g - 0.5f);
	b = 0.5f + f * (in.b - 0.5f);
	return *this;
};
Fcolor& Fcolor::adjust_saturation(float s) noexcept
{
	// Approximate values for each component's contribution to luminance.
	// Based upon the NTSC standard described in ITU-R Recommendation BT.709.
	float grey = r * 0.2125f + g * 0.7154f + b * 0.0721f;

	r = grey + s * (r - grey);
	g = grey + s * (g - grey);
	b = grey + s * (b - grey);
	return *this;
};
Fcolor& Fcolor::adjust_saturation(const Fcolor& in, float s) noexcept
{
	// Approximate values for each component's contribution to luminance.
	// Based upon the NTSC standard described in ITU-R Recommendation BT.709.
	float grey = in.r * 0.2125f + in.g * 0.7154f + in.b * 0.0721f;

	r = grey + s * (in.r - grey);
	g = grey + s * (in.g - grey);
	b = grey + s * (in.b - grey);
	return *this;
};
Fcolor& Fcolor::modulate(Fcolor& in) noexcept
{
	r *= in.r;
	g *= in.g;
	b *= in.b;
	a *= in.a;
	return *this;
};
Fcolor& Fcolor::modulate(const Fcolor& in1, const Fcolor& in2) noexcept
{
	r = in1.r*in2.r;
	g = in1.g*in2.g;
	b = in1.b*in2.b;
	a = in1.a*in2.a;
	return *this;
};
Fcolor& Fcolor::negative(const Fcolor& in) noexcept
{
	r = 1.0f - in.r;
	g = 1.0f - in.g;
	b = 1.0f - in.b;
	a = 1.0f - in.a;
	return *this;
};
Fcolor& Fcolor::negative() noexcept
{
	r = 1.0f - r;
	g = 1.0f - g;
	b = 1.0f - b;
	a = 1.0f - a;
	return *this;
};
Fcolor& Fcolor::sub_rgb(float s) noexcept
{
	r -= s;
	g -= s;
	b -= s;
	// a=1.0f-a;
	return *this;
};
Fcolor& Fcolor::add_rgb(float s) noexcept
{
	r += s;
	g += s;
	b += s;
	return *this;
};
Fcolor& Fcolor::add_rgba(float s) noexcept
{
	r += s;
	g += s;
	b += s;
	a += s;
	return *this;
};
Fcolor& Fcolor::mul_rgba(float s) noexcept
{
	r *= s;
	g *= s;
	b *= s;
	a *= s;
	return *this;
}
Fcolor& Fcolor::mul_rgb(float s) noexcept
{
	r *= s;
	g *= s;
	b *= s;
	return *this;
}
Fcolor& Fcolor::mul_rgba(const Fcolor& c, float s) noexcept
{
	r = c.r*s;
	g = c.g*s;
	b = c.b*s;
	a = c.a*s;
	return *this;
}
Fcolor& Fcolor::mul_rgb(const Fcolor& c, float s) noexcept
{
	r = c.r*s;
	g = c.g*s;
	b = c.b*s;
	return *this;
}

// SQ magnitude
float Fcolor::magnitude_sqr_rgb() const noexcept
{
	return r*r + g*g + b*b;
}
// magnitude
float Fcolor::magnitude_rgb() const noexcept
{
	return _sqrt(magnitude_sqr_rgb());
}
float Fcolor::intensity() const noexcept
{
	// XXX: Use the component percentages from adjust_saturation()?
	return (r + g + b) / 3.f;
}

// Normalize
Fcolor& Fcolor::normalize_rgb()
{
	VERIFY(magnitude_sqr_rgb() > EPS_S);
	return mul_rgb(1.f / magnitude_rgb());
}
Fcolor& Fcolor::normalize_rgb(const Fcolor& c)
{
	VERIFY(c.magnitude_sqr_rgb() > EPS_S);
	return mul_rgb(c, 1.f / c.magnitude_rgb());
}
Fcolor& Fcolor::lerp(const Fcolor& c1, const Fcolor& c2, float t) noexcept
{
	float invt = 1.f - t;
	r = c1.r*invt + c2.r*t;
	g = c1.g*invt + c2.g*t;
	b = c1.b*invt + c2.b*t;
	a = c1.a*invt + c2.a*t;
	return *this;
}
Fcolor& Fcolor::lerp(const Fcolor& c1, const Fcolor& c2, const Fcolor& c3, float t) noexcept
{
	if (t > .5f)
	{
		return lerp(c2, c3, t*2.f - 1.f);
	}
	else
	{
		return lerp(c1, c2, t*2.f);
	}
}
bool Fcolor::similar_rgba(const Fcolor& v, float E) const noexcept { return _abs(r - v.r) < E && _abs(g - v.g) < E && _abs(b - v.b) < E && _abs(a - v.a) < E; };
bool Fcolor::similar_rgb(const Fcolor& v, float E) const noexcept { return _abs(r - v.r) < E && _abs(g - v.g) < E && _abs(b - v.b) < E; };

bool _valid(const Fcolor& c) noexcept { return _valid(c.r) && _valid(c.g) && _valid(c.b) && _valid(c.a); }
