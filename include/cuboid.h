
#ifndef HEAP_CUBOID_H_
#define HEAP_CUBOID_H_

#include <cstdint>
#include <SFML/Graphics.hpp>

#include "util.h"

namespace heap
{
    class Cuboid
    {
        public:

            Cuboid(float width = 0, float length = 0, float height = 0, uint8_t color = 0, 
                   const sf::Vector2f & pos = sf::Vector2f(), uint8_t brightness = 150);

            void                 draw           (sf::RenderTarget & target, const sf::RenderStates & states);

            const sf::Vector2f & getPosition    () const;
            void                 setPosition    (const sf::Vector2f & pos);
            void                 addToPosition  (const sf::Vector2f & pos);

            float                getAlpha       () const;
            void                 setAlpha       (float alpha);
            void                 addToAlpha     (float alpha);

            float                getLength      () const;
            void                 setLength      (float value);
            void                 addToLength        (float value);

            float                getWidth       () const;
            void                 setWidth       (float value);
            void                 addToWidth     (float value);

            float                getHeight      () const;

            uint8_t              getColor       () const;
            uint8_t              getBrightness  () const;

            float                getTotalHeight () const;

            static const float   speed;
            static const float   angle;

        private:

            sf::VertexArray  m_array;
            sf::Vector2f     m_pos;
            sf::Vector2f     m_mov;

            uint8_t          m_color;

            float            m_alpha;

            uint8_t          m_brightness;  

            float            m_length;
            float            m_width;
            float            m_height;
    };

}

#endif
