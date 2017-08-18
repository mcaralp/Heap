
#include "scrollingScores.h"
#include "resources.h"
#include "util.h"

#include <cmath>

#define NS heap::ScrollingScores

NS::ScrollingScores(uint32_t width, uint32_t height)
{
	m_pos = 0; 
	m_cpt = 0; 
	m_width = width; 
	m_height = height;

	m_startScroll  = height * 0.3;
    m_endScroll    = height * 0.8;
    m_heightScroll = m_endScroll - m_startScroll;
    m_heightScore  = m_width * 0.1 * 1.1;


    
    m_scores.clear();

    m_scores.push_back(Score("MAX 1", 20));
    m_scores.push_back(Score("MAX 2", 15));
    m_scores.push_back(Score("MAX 3", 13));
    m_scores.push_back(Score("MAX 4", 11));
    //m_scores.push_back(Score("        ", 9999));
    m_scores.push_back(Score("MAX 5", 8));
    m_scores.push_back(Score("MAX 6", 8));
    m_scores.push_back(Score("MAX 1", 7));
    m_scores.push_back(Score("MAX 2", 5));
    m_scores.push_back(Score("MAX 3", 2));
    m_scores.push_back(Score("MAX 4", 1));
    //m_scores.push_back(Score("        ", 9999));
    m_scores.push_back(Score("MAX 5", 1));
    m_scores.push_back(Score("MAX 6", 0));
    
}

void NS::newScore(uint32_t newScore)
{
	m_scrollingMode = true;

	for(unsigned i(0); i < m_scores.size(); ++i)
	{
		if(m_scores[i].score <= newScore)
		{
			m_scrollingMode = false;
			m_newScorePosition = i;
			m_scores.insert(m_scores.begin() + i, Score(" ", newScore));

			m_currentLetter = 0;
			m_cpt = 0;

			if(m_heightScore * i < m_heightScroll / 2)
				m_pos = 0;
			else
				m_pos = m_heightScore * i - m_heightScroll / 2;

			break;
		} 
	}
}

bool NS::isInScrollingMode()
{
	return m_scrollingMode;
}

void NS::update()
{
	const float maxPos = m_heightScore * (m_scores.size()) - m_heightScroll;

	if(m_scrollingMode)
	{
		if(m_pos == 0)
	    {
	    	if(m_cpt == 200)
	    	{
	    		m_cpt = 0;
		        ++m_pos;
	    	}
			else
				++m_cpt;        	
	        
	    }
	    else if(m_pos >= maxPos)
	    {
	    	if(m_cpt == 200)
	    	{
	    		m_cpt = 0;
		        m_pos = 0;
	    	}
	    	else 
	    		++m_cpt;
	    }

	    else
	        ++m_pos;
	}
	else if(m_currentLetter < 8)
	{
		if(m_cpt == 30)
			m_scores[m_newScorePosition].name[m_currentLetter] = '_';
		else if(m_cpt == 60)
		{
			m_scores[m_newScorePosition].name[m_currentLetter] = ' ';
			m_cpt = 0;
		}

		++m_cpt;
	}
}

void NS::event(sf::Event & event)
{
	if(m_scrollingMode) return;

    if(event.type == sf::Event::TextEntered)
    {
        if(event.text.unicode < 128 && std::isalpha(event.text.unicode) && m_currentLetter < 8)
        {
            m_scores[m_newScorePosition].name[m_currentLetter] = std::toupper(event.text.unicode);
            ++m_currentLetter;
            if(m_scores[m_newScorePosition].name.size() == m_currentLetter)
            	 m_scores[m_newScorePosition].name += ' ';
            m_cpt = 0;
        }
        else if(event.text.unicode == 8 && m_currentLetter > 0)
        {
            if(m_currentLetter < 8)
                m_scores[m_newScorePosition].name[m_currentLetter] = ' ';
            --m_currentLetter;
            m_scores[m_newScorePosition].name[m_currentLetter] = ' ';
            m_cpt = 0;
            
        }
    }
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
    	m_scores[m_newScorePosition].name.pop_back();
    	m_cpt = 0;
    	//m_pos = 0;
    	m_scrollingMode = true;
    }
}

void NS::draw (sf::RenderTarget & target)
{  
    uint32_t begin = m_pos / m_heightScore;      
    uint32_t end   = std::ceil((m_pos + m_heightScroll) / m_heightScore);
   
    end = std::min(end, (uint32_t) m_scores.size());

    float currentPos = m_pos - begin * m_heightScore;  

    Resources::getGradientShader().setUniform("height", map(m_heightScroll, 0, m_height, 0, 1));
    Resources::getGradientShader().setUniform("top",    map(m_startScroll, 0, m_height, 1, -1));

    sf::RenderStates states;
    states.shader = &Resources::getGradientShader();

    for(unsigned i(begin); i < end; ++i)
    {
        sf::Text name(m_scores[i].name, Resources::getFont(), m_width * 0.1);
        name.setPosition(sf::Vector2f(m_width * 0.1, m_startScroll - currentPos));
        target.draw(name, states);

        sf::Text score(std::to_string(m_scores[i].score), Resources::getFont(), m_width * 0.1);
        score.setPosition(sf::Vector2f(m_width - getWidth(score) - m_width * 0.1, m_startScroll - currentPos));
        target.draw(score, states);

        currentPos -= m_heightScore;
    }
}

void NS::reset()
{

}

#undef NS
