#pragma once
#include "container-moving.h"
#include "engine.h"

class WidgetGameEditor : public ContainerMoving<Object>
{
public:
	WidgetGameEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WidgetGameEditor();

public:
	void SaveLevel(Engine *in_Engine);

private:
	Engine * m_Engine;
};
