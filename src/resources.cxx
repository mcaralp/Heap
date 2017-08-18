
#include "resources.h"

#include "path.h"

#define NS heap::Resources

sf::Font & NS::getFont()
{
	static bool init = false;
	static sf::Font font;
	if(!init)
	{
		init = true;

		std::string file = Path::join(Path::getExecDir(), "../res/fonts/GlacialIndifference-Regular.otf");
		font.loadFromFile(file);
	}

	return font;
}

sf::Shader & NS::getGrayscaleShader()
{
	static bool init = false;
	static sf::Shader shader;
	if(!init)
	{
		init = true;

		std::string file = Path::join(Path::getExecDir(), "../res/shaders/grayscale.vert");
		shader.loadFromFile(file, sf::Shader::Vertex);
	}

	return shader;
}

sf::Shader & NS::getGradientShader()
{
	static bool init = false;
	static sf::Shader shader;
	if(!init)
	{
		init = true;
		std::string file = Path::join(Path::getExecDir(), "../res/shaders/gradient.vert");
		shader.loadFromFile(file, sf::Shader::Vertex);
	}

	return shader;
}

#undef NS
