
#include "util.h"

#include <cmath>

#define NS heap


float NS::degreesToRadians(float degrees)
{
    return degrees * M_PI / 180.0;
}

sf::Vector2f NS::polarToCartesian(float angle, float length)
{
    return sf::Vector2f(length * std::cos(degreesToRadians(angle)), length * std::sin(degreesToRadians(angle)));
}

sf::Color NS::colorFromHSV(uint8_t hue, uint8_t sat, uint8_t val, uint8_t alpha)
{
    const float hueMax  = 256;
    const float hueBand = hueMax / 6;
    const float valueMax = 256;

    int ti = hue / hueBand;
    int f  = hue - ti * hueBand;
    int l  = (val * (valueMax - sat)) / valueMax;
    int m  = (val * (valueMax * hueBand - f * sat)) / (valueMax * hueBand);
    int n  = (val * (valueMax * hueBand - (hueBand-f) * sat)) / (valueMax * hueBand);

    switch(ti)
    {
        case 0: return sf::Color(val,n,l, alpha); break;
        case 1: return sf::Color(m,val,l, alpha); break;
        case 2: return sf::Color(l,val,n, alpha); break;
        case 3: return sf::Color(l,m,val, alpha); break;
        case 4: return sf::Color(n,l,val, alpha); break;
        case 5: return sf::Color(val,l,m, alpha); break;
    }

    return sf::Color(0, 0, 0, alpha);
}

float NS::lerp(float current, float next, float step)
{
    return current + (next - current) * step;
}

float NS::map(float value, float istart, float istop, float ostart, float ostop) 
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

sf::Vector2f NS::addToX (const sf::Vector2f & v, float x)
{
    return v + sf::Vector2f(x, 0);
}

sf::Vector2f NS::addToY (const sf::Vector2f & v, float y)
{
    return v + sf::Vector2f(0, y);
}

#undef NS
