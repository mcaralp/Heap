
#ifndef HEAP_START_BUTTON_H_
#define HEAP_START_BUTTON_H_

#include <SFML/Graphics.hpp>

namespace heap
{
	class StartButton
	{
		public:
			StartButton(uint32_t width, uint32_t height);

			void draw        (sf::RenderTarget & target);

		private:
			sf::CircleShape m_circle;
			sf::ConvexShape m_triangle;
 	};

}

#endif
