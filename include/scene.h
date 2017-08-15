    
#ifndef HEAP_SCENE_H_
#define HEAP_SCENE_H_

#include <SFML/Graphics.hpp>

#include "util.h"
#include "stage.h"
#include "background.h"

namespace heap
{
    class Scene
    {
        public:
            Scene();

            void reset();
            void start();
            void heapScaling();
            bool update();
            bool draw();

            void beginStateUpdate (sf::Event & event);
            void playStateUpdate  (sf::Event & event);
            void deadStateUpdate  (sf::Event & event);
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

            struct Score
            {
                std::string name;
                uint32_t score;

                Score(const std::string & n, uint32_t s)
                    : name(n), score(s)
                {

                }
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

            sf::Font     m_font;

            sf::Shader   m_grayscaleShader;
            sf::Shader   m_gradientShader;
        
            float        m_grayScale;
            float        m_grayScaleCible;

            std::vector<Score> m_scores;
            uint32_t m_currentPosition = 4;
            uint32_t m_currentLetter = 0;
            uint32_t m_cptCursor = 0;

    };
}

#endif
