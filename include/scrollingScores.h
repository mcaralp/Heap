
#ifndef HEAP_SCROLLING_SCORES_H_
#define HEAP_SCROLLING_SCORES_H_

#include <SFML/Graphics.hpp>
#include <vector>

namespace heap
{
	class ScrollingScores
	{
		public:
			ScrollingScores        (uint32_t width, uint32_t height);
			void draw              (sf::RenderTarget & target);
			void update      	   ();
			void reset 		       ();
			bool isInScrollingMode ();
			void newScore          (uint32_t newScore);
			void event             (sf::Event & event);

		private:

			struct Score
            {
                std::string name;
                uint32_t    score;

                Score(const std::string & n, uint32_t s)
                    : name(n), score(s)
                {

                }
            };
 
            using Scores = std::vector<Score>;
			
			uint32_t m_pos;
			uint32_t m_cpt;

			uint32_t m_width;
			uint32_t m_height;

			float    m_startScroll;
   	 		float    m_endScroll;
    		float    m_heightScroll;
    		float    m_heightScore;

    		bool     m_scrollingMode;
    		uint32_t m_newScorePosition;
    		uint32_t m_currentLetter;
    		Scores   m_scores;
           
 	};

}

#endif
