#pragma once
#include "game-object.h"

class Player
{
public:
	Player(GameObject *in_Object);
	~Player();

public:
	bool HandleEvent(const sf::Event &in_Event);

private:
	GameObject *m_Object;
};

