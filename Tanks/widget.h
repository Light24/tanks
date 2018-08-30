#pragma once
#include "object.h"

class Widget : public Object
{
public:
	Widget(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~Widget();

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void HandleEvent(const sf::Event &in_Event) = 0;
};
