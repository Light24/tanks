#pragma once
#include "widget.h"

class Image : public Widget
{
public:
	Image(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~Image();

public:
	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
};
