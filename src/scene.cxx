
#include <cmath>
#include <iostream>
#include <algorithm>


#include "resources.h"
#include "scene.h"
#include "startButton.h"

#define NS heap::Scene

const uint8_t NS::startingCuboids  = 5;
const uint8_t NS::margin           = 2;
const uint8_t NS::heapHeight       = 25;
const uint8_t NS::heapWidth        = 7;

NS::Scene(uint32_t width, uint32_t height)
    : m_window(sf::VideoMode(width, height), "Heap", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 4)),

      m_startText    (sf::Vector2f(width / 2, height * 0.6), "Press space to start", width * 0.1),
      m_continueText (sf::Vector2f(width / 2, height * 0.9), "Press space to continue", width * 0.09),
      m_scoreText    (sf::Vector2f(width / 2, height * 0.9), "Enter your name", width * 0.10),

      m_scores(width, height)
{
    // Computing the different sizes of objects, depending on the screen size
    m_height = height;
    m_width  = width;
    
    m_cuboidHeight = m_height / heapHeight;
    m_cuboidWidth  = m_cuboidHeight * heapWidth;
    
    m_distanceToBorder = m_cuboidWidth + m_cuboidHeight * margin;
    
    m_window.setFramerateLimit(60);

    // This is the position where cuboids spawn
    m_center = sf::Vector2f(m_width / 2, m_height - m_cuboidHeight * startingCuboids);
    
    m_leftStart  = polarToCartesian(180 + Cuboid::angle, m_distanceToBorder);
    m_rightStart = polarToCartesian(-Cuboid::angle, m_distanceToBorder);

    m_grayScale = 0;
    m_grayScaleCible = 0;
    
    m_scale = 1;
    m_viewY = 0;

    reset();
    heapScaling();
}

void NS::reset()
{
    m_cuboids.clear();
    
    m_newY = 0;
    
    m_newScale = 1;
    m_totalY = 0;   

    m_state = BeginState;

    m_score = 0;
    m_grayScaleCible = 0;
    
    m_lastShift = Stage::ShiftDown;

    for(unsigned i(0); i < startingCuboids; ++i)
    {
        sf::Vector2f pos = sf::Vector2f(0, (startingCuboids - i) * m_cuboidHeight) + m_center;
        m_cuboids.push_back(Stage(m_cuboidWidth, m_cuboidWidth, m_cuboidHeight, pos, 0, Stage::NoShifting, m_width, 0));
        m_totalY += m_cuboidHeight;
    }


}

void NS::start()
{
    reset();

    m_cuboids.push_back(Stage(m_cuboidWidth, m_cuboidWidth, m_cuboidHeight, m_center + m_leftStart,
                              4, Stage::ShiftDown, m_distanceToBorder, m_cuboidHeight / 5.f));
    m_state = PlayState;
    
}

void NS::heapScaling()
{
    Stage & bottom  = m_cuboids[m_cuboids.size() - 2];

    float totalHeight = m_totalY + bottom.getTotalHeight() + m_cuboidHeight;

    if(totalHeight > m_height)
    {
        m_newScale = m_height / totalHeight;
        m_newY = m_newScale * m_cuboidHeight;
    }
    else
        m_newY = m_cuboidHeight;
}

bool NS::update()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed)
            return false;

        switch(m_state)
        {
            case BeginState: beginStateEvent(event); break;
            case PlayState:  playStateEvent(event);  break;
            case DeadState:  deadStateEvent(event);  break;
        }
    }

    m_viewY     = lerp(m_viewY, m_newY, 0.1);
    m_scale     = lerp(m_scale, m_newScale, 0.1);
    m_grayScale = lerp(m_grayScale, m_grayScaleCible, 0.1);

    switch(m_state)
    {
        case BeginState: beginStateUpdate(); break;
        case PlayState:  playStateUpdate();  break;
        case DeadState:  deadStateUpdate();  break;
    }

    for(unsigned i(0); i < m_cuboids.size(); ++i)
        m_cuboids[i].update();
    
    m_back.update();

    return true;
}


bool NS::draw()
{
    m_window.clear(sf::Color::Black);
    
    sf::RenderStates states;
    
    states.shader = &Resources::getGrayscaleShader();
    Resources::getGrayscaleShader().setUniform("alpha", 1.f - m_grayScale);
    Resources::getGrayscaleShader().setUniform("lerpValue", m_grayScale);

    m_back.draw(m_window, states);
    
    states.transform.translate(0, -m_viewY);
    states.transform.scale(m_scale, m_scale, m_width / 2, m_height);
    
    for(unsigned i(0); i < m_cuboids.size(); ++i)
        m_cuboids[i].draw(m_window, states);

    switch(m_state)
    {
        case BeginState: beginStateDraw(); break;
        case PlayState:  playStateDraw();  break;
        case DeadState:  deadStateDraw();  break;
    }


    m_window.display();

    return true;
}


void NS::beginStateEvent(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        start();
}

void NS::playStateEvent(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        Stage & current = m_cuboids[m_cuboids.size() - 1];
        Stage & bottom  = m_cuboids[m_cuboids.size() - 2];

        if(!current.heapOver(bottom))
        {
            m_state = DeadState;
            m_grayScaleCible = 0.8;

            m_scores.newScore(m_score);
            
            heapScaling();

            return;
        }
        
        ++m_score;

        m_newY += m_cuboids[m_cuboids.size() - startingCuboids].getY() - 
                  m_cuboids[m_cuboids.size() - startingCuboids - 1].getY();     

        m_totalY += bottom.getY() - current.getY();     

        if(m_lastShift == Stage::ShiftLeft)
        {
            m_lastShift = Stage::ShiftDown;
            m_cuboids.push_back(current.buildNext(m_leftStart, m_lastShift));
        }
        else
        {
            m_lastShift = Stage::ShiftLeft;
            m_cuboids.push_back(current.buildNext(m_rightStart, m_lastShift));
        }

        m_cuboids[m_cuboids.size() - 1].move(m_lastShift);
       
    }
}

void NS::deadStateEvent(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && m_scores.isInScrollingMode())
        start();

    m_scores.event(event);

    
}

void NS::beginStateUpdate()
{
    m_startText.update();
}

void NS::playStateUpdate()
{
     
}

void NS::deadStateUpdate()
{
    if(m_scores.isInScrollingMode())
        m_continueText.update();
    else
        m_scoreText.update();
    

     
    m_scores.update();
}


void NS::beginStateDraw()
{
    StartButton button(m_width, m_height);
    button.draw(m_window);

   m_startText.draw(m_window);

}

void NS::playStateDraw()
{
    sf::Text score(std::to_string(m_score), Resources::getFont(), m_width * 0.1);
    score.setPosition(sf::Vector2f(m_width - getWidth(score) - getHeight(score), getHeight(score)));
    m_window.draw(score);   
}

void NS::deadStateDraw()
{
   
    sf::Text score("Game over", Resources::getFont(), m_width * 0.1);
    setOriginCenter(score);
    // The score is horizontally centered, vertically at 10% of the height. 
    score.setPosition(sf::Vector2f(m_width * 0.5, m_height * 0.05));

    sf::Text text("Your score : " + std::to_string(m_score), Resources::getFont(), m_width * 0.1);
    setOriginCenter(text);
    // The game over text is horizontally centered, vertically at 20% of the height. 
    text.setPosition(sf::Vector2f(m_width * 0.5, m_height * 0.15));
    
    m_window.draw(score);
    m_window.draw(text);

    if(m_scores.isInScrollingMode())
        m_continueText.draw(m_window);
    else
        m_scoreText.draw(m_window);

    m_scores.draw(m_window);
}


#undef NS
