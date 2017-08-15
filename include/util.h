
#ifndef HEAP_UTIL_H_
#define HEAP_UTIL_H_

#include <cstdint>
#include <SFML/Graphics.hpp>

namespace heap
{
	template <class T>
	void         setOriginCenter   (T & obj);
	template <class T>
	float        getHeight         (T & obj);
	template <class T>
	float        getWidth         (T & obj);

    float        degreesToRadians  (float degrees);
    sf::Vector2f polarToCartesian  (float angle, float length);
    sf::Color    colorFromHSV      (uint8_t hue, uint8_t sat, uint8_t val, uint8_t alpha = 255);
    float        lerp              (float current, float next, float step);
    float        map               (float value, float istart, float istop, float ostart, float ostop);

    sf::Vector2f addToX            (const sf::Vector2f & v, float x);
 	sf::Vector2f addToY            (const sf::Vector2f & v, float y);

}

#include "util.inl"

#endif
