
uniform float height;
uniform float top;

float map(float value, float istart, float istop, float ostart, float ostop) 
{
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	
	float middle = top - height;
	float base = top - height * 2.0; 

	float t = top - height * 0.2;
	float b = base + height * 0.2;


	if(gl_Position.y > t)
		gl_FrontColor = vec4(gl_Color.x, gl_Color.y, gl_Color.z, map(gl_Position.y, top, t, 0.0, 1.0));
	else if(gl_Position.y < b)
		gl_FrontColor = vec4(gl_Color.x, gl_Color.y, gl_Color.z, map(gl_Position.y, base, b, 0.0, 1.0));
	else
		gl_FrontColor = vec4(gl_Color.x, gl_Color.y, gl_Color.z, 1.0);
} 