
#include "background.h"
#include "util.h"

#define NS heap::Background

const uint8_t NS::startingColor = 150;

NS::Background()
    : m_color(startingColor), m_array(sf::Triangles, 6)
{

}

void NS::update()
{
    m_color += 0.05;
}

void NS::draw(sf::RenderTarget & target, const sf::RenderStates & states)
{
    sf::Vector2u size = target.getSize();

    m_array[0].position = sf::Vector2f(0, 0);
    m_array[1].position = sf::Vector2f(size.x, 0);
    m_array[2].position = sf::Vector2f(size.x, size.y);

    m_array[3].position = sf::Vector2f(0, 0);
    m_array[4].position = sf::Vector2f(0, size.y);
    m_array[5].position = sf::Vector2f(size.x, size.y);
    
    sf::Color color1 = colorFromHSV(m_color, 200, 200);
    sf::Color color2 = colorFromHSV(m_color + 20, 100, 100);

    m_array[0].color = color1;
    m_array[1].color = color1;
    m_array[2].color = color2;
    
    m_array[3].color = color1;
    m_array[4].color = color2;
    m_array[5].color = color2;
    
    target.draw(m_array, states);
}

#undef NS
