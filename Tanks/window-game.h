#pragma once
#include "window.h"
#include "SFML/Graphics.hpp"
#include "engine.h"

class Engine;
class WindowGame : public Window<Widget>
{
public:
	WindowGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~WindowGame();

public:
};
