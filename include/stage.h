
#ifndef HEAP_STAGE_H_
#define HEAP_STAGE_H_

#include <cstdint>
#include <SFML/Graphics.hpp>

#include "util.h"
#include "cuboid.h"

namespace heap
{
    class Stage
    {
        public:

            enum Shifting
            {
                ShiftLeft  = 0,
                ShiftRight = 1, 
                ShiftDown  = 2,
                ShiftUp    = 3,
                NoShifting = 4
            };

            Stage (float width, float length, float height, const sf::Vector2f & center, 
                   uint8_t color, Stage::Shifting shift, uint32_t screenWidth, float speed);

            Stage buildNext(const sf::Vector2f & d, Stage::Shifting shift) const;

            void  update    ();
            void  draw      (sf::RenderTarget & target, const sf::RenderStates & states);
            void  move      (Stage::Shifting shift);
            bool  heapOver (Stage & bottom);
            float getY      ();

            float getTotalHeight () const;

        private:

            sf::Vector2f     m_mov;

            bool             m_erase;
            bool             m_stop;
            bool             m_first;

            Stage::Shifting  m_shift;

            float            m_newY;
            float            m_speed;
            float            m_totalMove;

            Cuboid           m_cuboid;
            Cuboid           m_animation;

            uint32_t         m_distanceToBorder;
    };
}

#endif
