
#ifndef HEAP_BACKGROUND_H_
#define HEAP_BACKGROUND_H_

#include <cstdint>
#include <SFML/Graphics.hpp>

namespace heap
{
    class Background
    {
        public:
            Background();

            void update();
            void draw(sf::RenderTarget & target, const sf::RenderStates & states);

        private:

            float           m_color;
            sf::VertexArray m_array;

            static const uint8_t startingColor;


    };
}

#endif
