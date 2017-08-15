
#include <cmath>
#include <iostream>
#include <algorithm>

#include "scene.h"
#include "startButton.h"

#include "data/fontData.h"
#include "data/shaderData.h"

#define NS heap::Scene

const uint8_t NS::startingCuboids   = 5;
const uint8_t NS::margin            = 2;
const uint8_t NS::heapHeight       = 25;
const uint8_t NS::heapWidth        = 7;

NS::Scene()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    // Computing the different sizes of objects, depending on the screen size
    m_height = mode.height * (3 / 4.f);
    m_cuboidHeight = m_height / heapHeight;
    m_cuboidWidth  = m_cuboidHeight * heapWidth;
    
    m_distanceToBorder = m_cuboidWidth + m_cuboidHeight * margin;
    
    m_width = polarToCartesian(Cuboid::angle, m_distanceToBorder).x * 2;

    m_window.create(sf::VideoMode(m_width, m_height), "Heap", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 4));
    m_window.setFramerateLimit(60);

    // This is the position where cuboids spawn
    m_center = sf::Vector2f(m_width / 2, m_height - m_cuboidHeight * startingCuboids);
    
    m_leftStart  = polarToCartesian(180 + Cuboid::angle, m_distanceToBorder);
    m_rightStart = polarToCartesian(-Cuboid::angle, m_distanceToBorder);
    
    m_grayscaleShader.loadFromMemory(std::string(reinterpret_cast<char *>(data::shader), sizeof(data::shader)),
                                     sf::Shader::Vertex);

    m_gradientShader.loadFromFile("/Users/mathieu/Documents/Developpement/Heap/res/shaders/gradient.vert", sf::Shader::Vertex);
    m_grayScale = 0;
    m_grayScaleCible = 0;
    
    m_scale = 1;
    m_viewY = 0;

    m_font.loadFromFile("/Users/mathieu/Documents/Developpement/Heap/res/fonts/GlacialIndifference-Regular.otf");
    //m_font.loadFromMemory(data::font, sizeof(data::font));

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

    m_scores.clear();

    m_scores.push_back(Score("MAX 1", 0));
    m_scores.push_back(Score("MAX 2", 1));
    m_scores.push_back(Score("MAX 3", 2));
    m_scores.push_back(Score("MAX 4", 3));
    //m_scores.push_back(Score("        ", 9999));
    m_scores.push_back(Score("MAX 5", 5));
    m_scores.push_back(Score("MAX 6", 6));
    m_scores.push_back(Score("MAX 1", 0));
    m_scores.push_back(Score("MAX 2", 1));
    m_scores.push_back(Score("MAX 3", 2));
    m_scores.push_back(Score("MAX 4", 3));
    //m_scores.push_back(Score("        ", 9999));
    m_scores.push_back(Score("MAX 5", 5));
    m_scores.push_back(Score("MAX 6", 6));

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
            case BeginState: beginStateUpdate(event); break;
            case PlayState:  playStateUpdate(event);  break;
            case DeadState:  deadStateUpdate(event);  break;
        }
    }

    m_viewY = lerp(m_viewY, m_newY, 0.1);
    m_scale = lerp(m_scale, m_newScale, 0.1);
    m_grayScale = lerp(m_grayScale, m_grayScaleCible, 0.1);

    for(unsigned i(0); i < m_cuboids.size(); ++i)
        m_cuboids[i].update();
    
    m_back.update();

    return true;
}


bool NS::draw()
{
    m_window.clear(sf::Color::Black);
    
    sf::RenderStates states;
    
    states.shader = &m_grayscaleShader;
    m_grayscaleShader.setUniform("alpha", 1.f - m_grayScale);
    m_grayscaleShader.setUniform("lerpValue", m_grayScale);

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


void NS::beginStateUpdate(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        start();
}

void NS::playStateUpdate(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        Stage & current = m_cuboids[m_cuboids.size() - 1];
        Stage & bottom  = m_cuboids[m_cuboids.size() - 2];

        if(!current.heapOver(bottom))
        {
            m_state = DeadState;
            m_grayScaleCible = 0.8;
            
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

void NS::deadStateUpdate(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        start();

    if(event.type == sf::Event::TextEntered)
    {
        if(event.text.unicode < 128 && std::isalpha(event.text.unicode) && m_currentLetter < 8)
        {
            m_scores[m_currentPosition].name[m_currentLetter] = std::toupper(event.text.unicode);
            ++m_currentLetter;
            m_cptCursor = 0;
        }
        else if(event.text.unicode == 8 && m_currentLetter > 0)
        {
            if(m_currentLetter < 8)
                m_scores[m_currentPosition].name[m_currentLetter] = ' ';
            --m_currentLetter;
            m_scores[m_currentPosition].name[m_currentLetter] = ' ';
            m_cptCursor = 0;
            
        }
    }


    
}


void NS::beginStateDraw()
{
    StartButton button(m_width, m_height);

    sf::Text text("Press space to play", m_font, m_width * 0.1);
    setOriginCenter(text);
    text.setPosition(sf::Vector2f(m_width * 0.5, m_height * 0.5 + getHeight(text)));

    button.draw(m_window);

    m_window.draw(text);
}

void NS::playStateDraw()
{
    sf::Text score(std::to_string(m_score), m_font, m_width * 0.1);
    score.setPosition(sf::Vector2f(m_width - getWidth(score) - getHeight(score), getHeight(score)));
    m_window.draw(score);   
}

float pos = 0;
int cpt = 0;


void NS::deadStateDraw()
{
    /*
    if(m_currentLetter < 4)
    {
        if(m_cptCursor++ == 0)
            m_scores[m_currentPosition].name[m_currentLetter] = '_';
        else if(m_cptCursor == 30)
            m_scores[m_currentPosition].name[m_currentLetter] = ' ';
        else if(m_cptCursor == 60)
            m_cptCursor = 0;
    }
    */

    const float scale = 0.1;
    
    sf::Text score("Game over", m_font, m_width * scale);
    setOriginCenter(score);
    // The score is horizontally centered, vertically at 10% of the height. 
    score.setPosition(sf::Vector2f(m_width * 0.5, m_height * 0.1));

    sf::Text text("Your score : " + std::to_string(m_score), m_font, m_width * scale);
    setOriginCenter(text);
    // The game over text is horizontally centered, vertically at 20% of the height. 
    text.setPosition(sf::Vector2f(m_width * 0.5, m_height * 0.2));
    
    m_window.draw(score);
    m_window.draw(text);

    const float startScroll  = m_height * 0.4;
    const float endScroll    = m_height * 0.9;
    const float heightScroll = endScroll - startScroll;
    const float heightScore  = m_width * scale * 1.1;


    if(pos <= 0)
    {
        cpt++;
        if(cpt == 200)
        {
            pos = heightScore * (m_scores.size() - 1) - heightScroll;
            cpt = 0;
        }
    }
    else
        pos--;
    
   
    uint32_t begin = pos / heightScore;      
    uint32_t end   = std::ceil((pos + heightScroll) / heightScore);
   
    end = std::min(end, (uint32_t) m_scores.size());

    float currentPos = pos - begin * heightScore;  

    m_gradientShader.setUniform("height", map(heightScroll, 0, m_height, 0, 1));
    m_gradientShader.setUniform("top",    map(startScroll, 0, m_height, 1, -1));

    sf::RenderStates states;
    states.shader = &m_gradientShader;

    for(unsigned i(begin); i < end; ++i)
    {
        sf::Text name(m_scores[i].name, m_font, m_width * scale);
        name.setPosition(sf::Vector2f(m_width * 0.1, startScroll - currentPos));
        m_window.draw(name, states);

        sf::Text score(std::to_string(m_scores[i].score), m_font, m_width * scale);
        score.setPosition(sf::Vector2f(m_width - getWidth(score) - m_width * 0.1, startScroll - currentPos));
        m_window.draw(score, states);

        currentPos -= heightScore;
    }

}


#undef NS
