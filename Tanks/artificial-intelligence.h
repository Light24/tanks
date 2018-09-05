#pragma once
#include "game-object.h"
#include "container.h"

class ArtificialIntelligence
{
public:
	ArtificialIntelligence();
	~ArtificialIntelligence();

public:
	void Update(Container<Object> *in_Container, const sf::Time &in_Time);
};
