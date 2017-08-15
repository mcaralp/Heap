
#ifndef HEAP_SCROLLING_SCORES_H_
#define HEAP_SCROLLING_SCORES_H_

#include <SFML/Graphics.hpp>

namespace heap
{
	class ScrollingScores
	{
		public:
			ScrollingScores (uint32_t width, uint32_t height);
			void draw       (sf::RenderTarget & target);
			void reset 		();

		private:
			
			uint32_t pos;
			uint32_t cpt;
 	};

}

#endif
