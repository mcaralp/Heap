
#ifndef HEAP_UTIL_INL_
#define HEAP_UTIL_INL_

#include "util.h"

#define NS heap

template <class T>
void NS::setOriginCenter(T & obj)
{
	sf::FloatRect rect = obj.getGlobalBounds();
    obj.setOrigin(rect.width / 2, rect.height / 2);
}

template <class T>
float NS::getHeight(T & obj)
{
	return obj.getGlobalBounds().height;
}

template <class T>
float NS::getWidth(T & obj)
{
	return obj.getGlobalBounds().width;
}

#undef NS

#endif
