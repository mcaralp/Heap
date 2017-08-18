
#ifndef HEAP_RESOURCES_H_
#define HEAP_RESOURCES_H_

#include <SFML/Graphics.hpp>

namespace heap
{
    class Resources
    {
        public:
        	static sf::Font   & getFont();
        	static sf::Shader & getGrayscaleShader();
        	static sf::Shader & getGradientShader();
    };
}

#endif