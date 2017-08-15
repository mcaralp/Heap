
uniform float lerpValue;
uniform float alpha;

float lerp(float current, float next, float step)
{
    return current + (next - current) * step;
}

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	float rBase = gl_Color.x * alpha;
	float gBase = gl_Color.y * alpha;
	float bBase = gl_Color.z * alpha;

	if (rBase < 0.0) rBase = 0.0;
	if (gBase < 0.0) gBase = 0.0;
	if (bBase < 0.0) bBase = 0.0;

	float gray = (rBase + gBase + bBase) / 3.0;

	float r = lerp(gl_Color.x, gray, lerpValue);
	float g = lerp(gl_Color.y, gray, lerpValue);
	float b = lerp(gl_Color.z, gray, lerpValue);

	gl_FrontColor = vec4(r, g, b, gl_Color.w);
}