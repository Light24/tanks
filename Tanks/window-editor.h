#pragma once
#include "container-moving.h"
#include "engine.h"

class WindowEditor : public ContainerMoving<Widget>
{
public:
	WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WindowEditor();
};
