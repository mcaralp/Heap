
#include <cmath>

#include "stage.h"

#define NS heap::Stage

NS::Stage(float width, float length, float height, const sf::Vector2f & pos, 
          uint8_t color, Stage::Shifting shift, uint32_t distanceToBorder, float speed)

    : m_erase(false), m_stop(false), m_first(false), m_newY(0), m_speed(speed), m_totalMove(0),
      m_cuboid(width, length, height, color, pos, 150),
      m_animation(width, length, height, color, pos, 150),
      m_distanceToBorder(distanceToBorder)
{
    move(shift);
}

NS NS::buildNext(const sf::Vector2f & d, Stage::Shifting shift) const
{
    float height = m_cuboid.getHeight();
    float speed  = m_speed + 0.002 * height;
    if (speed > height / 2.5f) speed = height / 2.5f;

    return Stage(m_cuboid.getWidth(), m_cuboid.getLength(), height, 
            m_cuboid.getPosition() - sf::Vector2f(0, height) + d,
            m_cuboid.getColor() + 4, shift, m_distanceToBorder, speed);
} 


void NS::update()
{
    m_cuboid.addToPosition(m_mov);

    float val = lerp(0, m_newY, 0.2);

    m_cuboid.addToPosition(sf::Vector2f(0, val));
    m_newY -= val;  

    if(m_erase)
        m_animation.setAlpha(lerp(m_animation.getAlpha(), 0, 0.2 ));
    
    m_totalMove += m_speed;
    
    if(m_totalMove >= m_distanceToBorder * 2)
    {
        m_totalMove = 0;
        switch(m_shift)
        {
            case NoShifting : break;
            case ShiftRight:
                move(ShiftLeft);
                break;
            case ShiftLeft:
                move(ShiftRight);
                break;
            case ShiftUp: 
                move(ShiftDown);
                break;
            case ShiftDown: 
                move(ShiftUp);
                break;
        }
    }
}

void NS::draw (sf::RenderTarget & target, const sf::RenderStates & states)
{
    if(m_erase)
    {
        if(m_first)
        {
            if(!m_stop) m_cuboid.draw(target, states);
            m_animation.draw(target, states);
        }
        else
        {
            m_animation.draw(target, states);
            if(!m_stop) m_cuboid.draw(target, states);
        }
    }
    else    
        m_cuboid.draw(target, states);
}

void NS::move(Stage::Shifting shift)
{
    m_shift = shift;

    switch(shift)
    {
        case NoShifting : m_mov = sf::Vector2f(0, 0);                              break;
        case ShiftRight:  m_mov = polarToCartesian(-Cuboid::angle, m_speed);       break;
        case ShiftLeft:   m_mov = polarToCartesian(-Cuboid::angle, -m_speed);      break;
        case ShiftUp:     m_mov = polarToCartesian(180  + Cuboid::angle, m_speed); break;
        case ShiftDown:   m_mov = polarToCartesian(180 + Cuboid::angle, -m_speed); break;
    }
}

bool NS::heapOver(Stage & bottom)
{
    sf::Vector2f pos = m_cuboid.getPosition();
    sf::Vector2f posPrev = bottom.m_cuboid.getPosition();

    posPrev.y -= m_cuboid.getHeight();

    float distance = std::sqrt((pos.x - posPrev.x) * (pos.x - posPrev.x) + 
                               (pos.y - posPrev.y) * (pos.y - posPrev.y));

    if(distance < 5)
    {
        pos = posPrev;
        m_cuboid.setPosition(pos);
    }
    else 
    {
        if(m_shift == Stage::ShiftLeft || m_shift == Stage::ShiftRight)
        {
            if(m_cuboid.getLength() < distance)
            {
                move(Stage::NoShifting);
                m_animation.setPosition(pos);
                m_erase = true;
                m_stop = true;
                return false;
            }

            m_animation.setLength(distance);
            m_cuboid.addToLength(-distance);

            if(pos.x < posPrev.x)
            {
                pos = posPrev;
                m_cuboid.setPosition(pos);
                m_animation.setPosition(polarToCartesian(180 - Cuboid::angle, distance) + pos);
                m_first = true;
            }
            else
            {
                m_animation.setPosition(polarToCartesian(-Cuboid::angle, m_cuboid.getLength()) + pos);
            }
        }
        else
        {
            if(m_cuboid.getWidth() < distance)
            {
                move(Stage::NoShifting);
                m_animation.setPosition(pos);
                m_erase = true;
                m_stop = true;
                return false;
            }


            m_animation.setWidth(distance);
            m_cuboid.addToWidth(-distance);

            if(pos.x > posPrev.x)
            {
                pos = posPrev;
                m_cuboid.setPosition(pos);
                m_animation.setPosition(polarToCartesian(Cuboid::angle, distance) + pos);
                m_first = true;
            }
            else                            
                m_animation.setPosition(polarToCartesian(180 + Cuboid::angle, m_cuboid.getWidth()) + pos);
        
        }

        m_erase = true;

    
    }

    move(Stage::NoShifting);

    return true;

}

float NS::getY()
{
    return m_cuboid.getPosition().y;
}

float NS::getTotalHeight() const
{
    return m_cuboid.getTotalHeight();
}

#undef NS
