#pragma once
#include "container.h"

class WidgetGameStatistic : public Container
{
public:
	WidgetGameStatistic(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WidgetGameStatistic();

public:
	void OnPlayerHealthChanged(const size_t in_HealthCount);

	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;

private:
	size_t m_HealthMax;
	size_t m_HealthCurrent;
	sf::Sprite *m_HealthFullSprite;
	sf::Sprite *m_HealthEmptySprite;
};

