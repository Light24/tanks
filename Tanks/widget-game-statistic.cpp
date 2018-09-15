#include "widget-game-statistic.h"
#include "image.h"
#include "texture-manager.h"

WidgetGameStatistic::WidgetGameStatistic(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size), m_HealthMax(0)
{
	sf::Vector2f healthSize(30, 30);
	
	m_HealthFullSprite = new sf::Sprite(*TextureManager::GetInstance()->GetTexture("heart-full.png"));
	m_HealthFullSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_HealthFullSprite->getTexture()->getSize().x, m_HealthFullSprite->getTexture()->getSize().y)));
	m_HealthFullSprite->setScale(sf::Vector2f(healthSize.x / m_HealthFullSprite->getTexture()->getSize().x, healthSize.y / m_HealthFullSprite->getTexture()->getSize().y));

	m_HealthEmptySprite = new sf::Sprite(*TextureManager::GetInstance()->GetTexture("heart-empty.png"));
	m_HealthEmptySprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_HealthEmptySprite->getTexture()->getSize().x, m_HealthEmptySprite->getTexture()->getSize().y)));
	m_HealthEmptySprite->setScale(sf::Vector2f(healthSize.x / m_HealthEmptySprite->getTexture()->getSize().x, healthSize.y / m_HealthEmptySprite->getTexture()->getSize().y));
}

WidgetGameStatistic::~WidgetGameStatistic()
{
	if (m_HealthFullSprite)
	{
		delete m_HealthFullSprite;
		m_HealthFullSprite = NULL;
	}
	if (m_HealthEmptySprite)
	{
		delete m_HealthEmptySprite;
		m_HealthEmptySprite = NULL;
	}
}

void WidgetGameStatistic::OnPlayerHealthChanged(const size_t in_HealthCount)
{
	m_HealthMax = std::max(m_HealthMax, in_HealthCount);
	m_HealthCurrent = in_HealthCount;
}

#define HEALTH_SPRITE_OFFSET_X -4
#define HEALTH_SPRITE_OFFSET_Y 4
void WidgetGameStatistic::Draw(sf::RenderWindow *in_RenderWindow)
{
	Container::Draw(in_RenderWindow);

	sf::Vector2f pos(GetAbsolutePos().x, GetAbsolutePos().y);
	for (size_t i = 0; i != m_HealthMax; ++i)
	{
		sf::Sprite *sprite = (i < m_HealthCurrent) ? m_HealthFullSprite : m_HealthEmptySprite;
		sprite->setPosition(pos);
		in_RenderWindow->draw(*sprite);

		if ((pos.x - GetAbsolutePos().x) + sprite->getTextureRect().width * sprite->getScale().x + HEALTH_SPRITE_OFFSET_X < GetSize().x)
		{
			pos.x += sprite->getTextureRect().width * sprite->getScale().x + HEALTH_SPRITE_OFFSET_X;
		}
		else
		{
			pos.x = GetAbsolutePos().x;
			pos.y += sprite->getTextureRect().height * sprite->getScale().y + HEALTH_SPRITE_OFFSET_Y;
		}
	}
}
