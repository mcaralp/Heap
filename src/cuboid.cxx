
#include "cuboid.h"

#define NS heap::Cuboid

const float NS::angle = 25;


NS::Cuboid(float width, float length, float height, uint8_t color, const sf::Vector2f & pos, uint8_t brightness)
    : m_pos(pos), m_color(color),
      m_alpha(255), m_brightness(brightness), m_length(length), m_width(width), m_height(height)
{
    m_array.setPrimitiveType(sf::Triangles);
    m_array.resize(18);
}

void NS::draw (sf::RenderTarget & target, const sf::RenderStates & states)
{

    sf::Vector2f right = polarToCartesian(-angle, m_length);
    sf::Vector2f left = polarToCartesian(180 + angle, m_width);

    sf::Vector2f heightVec(0, -m_height);

    m_array[0].position  = m_pos + heightVec + left;
    m_array[1].position  = m_pos + heightVec + right;
    m_array[2].position  = m_pos + heightVec + left + right;

    m_array[3].position  = m_pos + heightVec;
    m_array[4].position  = m_pos + heightVec + left;
    m_array[5].position  = m_pos + heightVec + right;

    m_array[6].position  = m_pos;
    m_array[7].position  = m_pos + right;
    m_array[8].position  = m_pos + right + heightVec;

    m_array[9].position  = m_pos + heightVec;
    m_array[10].position = m_pos;
    m_array[11].position = m_pos + right + heightVec;

    m_array[12].position = m_pos;
    m_array[13].position = m_pos + left;
    m_array[14].position = m_pos + left + heightVec;

    m_array[15].position = m_pos + heightVec;
    m_array[16].position = m_pos;
    m_array[17].position = m_pos + left + heightVec;

    m_array[0].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);
    m_array[1].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);
    m_array[2].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);

    m_array[3].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);
    m_array[4].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);
    m_array[5].color  = colorFromHSV(m_color, m_brightness, 255, m_alpha);

    m_array[6].color  = colorFromHSV(m_color, m_brightness, 200, m_alpha);
    m_array[7].color  = colorFromHSV(m_color, m_brightness, 200, m_alpha);
    m_array[8].color  = colorFromHSV(m_color, m_brightness, 200, m_alpha);

    m_array[9].color  = colorFromHSV(m_color, m_brightness, 200, m_alpha);
    m_array[10].color = colorFromHSV(m_color, m_brightness, 200, m_alpha);
    m_array[11].color = colorFromHSV(m_color, m_brightness, 200, m_alpha);

    m_array[12].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);
    m_array[13].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);
    m_array[14].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);

    m_array[15].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);
    m_array[16].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);
    m_array[17].color = colorFromHSV(m_color, m_brightness, 150, m_alpha);

    target.draw(m_array, states);
}

const sf::Vector2f & NS::getPosition() const
{
    return m_pos;
}

void NS::setAlpha(float alpha)
{
    m_alpha = alpha;
}

void NS::addToAlpha(float alpha)
{
    setAlpha(m_alpha + alpha);
}

float NS::getAlpha() const
{
    return m_alpha;
}

void NS::addToPosition(const sf::Vector2f & pos)
{
    setPosition(pos + m_pos);
}

void NS::setPosition(const sf::Vector2f & pos)
{
    m_pos = pos;
}

void NS::setLength(float value)
{
    m_length = value;
}

void NS::addToLength(float value)
{
    setLength(m_length + value);
}

void NS::setWidth(float value)
{
    m_width = value;
}

void NS::addToWidth(float value)
{
    setWidth(m_width + value);
}

float NS::getLength() const
{
    return m_length;
}

float NS::getWidth() const
{
    return m_width;
}

float NS::getHeight() const
{
    return m_height;
}

uint8_t NS::getColor () const
{
    return m_color;
}

uint8_t NS::getBrightness () const
{
    return m_brightness;
}

float NS::getTotalHeight() const
{
    sf::Vector2f right = polarToCartesian(-angle, m_length);
    sf::Vector2f left = polarToCartesian(180 + angle, m_width);

    sf::Vector2f heightVec(0, -m_height);

    return -(heightVec + left + right).y;
}

#undef NS
