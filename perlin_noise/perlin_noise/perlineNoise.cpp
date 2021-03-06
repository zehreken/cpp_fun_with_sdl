#include "perlineNoise.hpp"
#include "constants.hpp"

float clamp(float x, float lower, float upper)
{
	if (x < lower)
		x = lower;
	else if (x > upper)
		x = upper;
	
	return x;
}

float smoothstep(float a0, float a1, float w)
{
	w = clamp((w - a0) / (a1 - a0), -1, 1);
	
	return w * w * (3 - 2 * w);
}

float lerp(float a0, float a1, float w)
{
	return (1.0 - w) * a0 + w * a1;
}

float dotGridGradient(int ix, int iy, float x, float y)
{
	extern float Gradient[GRAD_ROW_COUNT][GRAD_COLUMN_COUNT][2];
	
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	
	return (dx * Gradient[iy][ix][0] + dy * Gradient[iy][ix][1]);
}

float perlin(float x, float y)
{
	int x0 = (int)x;
	int x1 = x0 + 1;
	int y0 = (int)y;
	int y1 = y0 + 1;
	
	float sx = x - (float)x0;
	float sy = y - (float)y0;
	
	float n0, n1, ix0, ix1, value;
	
	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = lerp(n0, n1, sx);
//	ix0 = smoothstep(n0, n1, sx);
	
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = lerp(n0, n1, sx);
//	ix1 = smoothstep(n0, n1, sx);
	
	value = lerp(ix0, ix1, sy);
//	value = smoothstep(ix0, ix1, sy);
	
	return value;
}
