
#ifndef HEAP_BLINKINGTEXT_H_
#define HEAP_BLINKINGTEXT_H_

#include <SFML/Graphics.hpp>

namespace heap
{
    class BlinkingText
    {
        public:
            BlinkingText (const sf::Vector2f & pos, const std::string & text, float textSize);

            void setText (const std::string & text);
            void draw    (sf::RenderTarget & target);
            void update  ();
            void setY    (float y);

        private:
            float        m_state;
            sf::Text     m_text;
    };
}

#endif