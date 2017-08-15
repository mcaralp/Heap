
#include "startButton.h"
#include "util.h"

#define NS heap::StartButton

NS::StartButton (uint32_t width, uint32_t height)
{
	const float sizeCircle   = width / 6;
    const float sizeTriangle = width / 10;

    m_circle.setRadius(sizeCircle);
    m_circle.setPointCount(80);

    sf::Vector2f center(width / 2, height / 2);
    sf::Vector2f circlePosition(center - sf::Vector2f(0, sizeCircle));

    setOriginCenter(m_circle);

    m_circle.setPosition(circlePosition);
    m_circle.setFillColor(sf::Color(255, 255, 255, 60));
    m_circle.setOutlineThickness(width / 80);
    m_circle.setOutlineColor(sf::Color(255, 255, 255, 200));

    m_triangle.setPointCount(3);

    m_triangle.setPoint(0, circlePosition + polarToCartesian(0,   sizeTriangle));
    m_triangle.setPoint(1, circlePosition + polarToCartesian(120, sizeTriangle));
    m_triangle.setPoint(2, circlePosition + polarToCartesian(240, sizeTriangle));

    m_triangle.setFillColor(sf::Color(255, 255, 255, 230));
    m_triangle.setOutlineThickness(0);
}

void NS::draw (sf::RenderTarget & target)
{
	target.draw(m_circle);
	target.draw(m_triangle);
}

#undef NS