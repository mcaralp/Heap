    
#ifndef HEAP_SCENE_H_
#define HEAP_SCENE_H_

#include <SFML/Graphics.hpp>

#include "util.h"
#include "stage.h"
#include "background.h"
#include "scrollingScores.h"
#include "blinkingText.h"

namespace heap
{
    class Scene
    {
        public:
            Scene(uint32_t width, uint32_t height);

            void reset();
            void start();
            void heapScaling();
            bool update();
            bool draw();

            void beginStateEvent  (sf::Event & event);
            void playStateEvent   (sf::Event & event);
            void deadStateEvent   (sf::Event & event);
            void beginStateUpdate ();
            void playStateUpdate  ();
            void deadStateUpdate  ();
            void beginStateDraw   ();
            void playStateDraw    ();
            void deadStateDraw    ();
        private:

            enum State
            {
                BeginState,
                PlayState,
                DeadState
            };

            

            static const uint8_t startingCuboids;
            static const uint8_t heapHeight;
            static const uint8_t heapWidth;
            static const uint8_t margin;
        
            uint32_t         m_score;

            float            m_width;
            float            m_height;
            float            m_cuboidHeight;
            float            m_cuboidWidth;

            sf::RenderWindow m_window;

            Background         m_back;
            std::vector<Stage> m_cuboids;

            sf::Vector2f m_leftStart;
            sf::Vector2f m_rightStart;

            sf::Vector2f m_center;  

            float        m_viewY;
            float        m_scale;
            float        m_newY;
            float        m_totalY;
            float        m_newScale;
            float        m_distanceToBorder;

            Stage::Shifting m_lastShift;

            State        m_state;
        
            float        m_grayScale;
            float        m_grayScaleCible;

            BlinkingText m_startText;
            BlinkingText m_continueText;
            BlinkingText m_scoreText;

            ScrollingScores m_scores;

    };
}

#endif
