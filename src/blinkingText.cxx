
#include "blinkingText.h"

#include "util.h"
#include "resources.h"

#define NS heap::BlinkingText

NS::BlinkingText(const sf::Vector2f & pos, const std::string & text, float textSize)
	: m_text(text, Resources::getFont(), textSize)
{
    setOriginCenter(m_text);
	m_text.setPosition(pos);
}

void NS::draw (sf::RenderTarget & target)
{
	target.draw(m_text);
}

void NS::update ()
{
	m_state = lerp(m_state, 512, 0.01);

    if(m_state >= 500)
        m_state = 1;

    m_text.setFillColor(sf::Color(255, 255, 255, m_state > 255 ? m_state - 256 : 256 - m_state));
}
#undef NS
