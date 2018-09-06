#pragma once
#include "container.h"

class Window : public Container
{
public:
	Window(const sf::Vector2f &in_Pos = sf::Vector2f(0, 0), const sf::Vector2f &in_Size = sf::Vector2f(200, 200));
	virtual ~Window();

public:

private:
};
