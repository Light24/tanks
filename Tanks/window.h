#pragma once
#include "container.h"

template <typename ObjectType>
class Window : public Container<ObjectType>
{
public:
	Window(const sf::Vector2f &in_Pos = sf::Vector2f(0, 0), const sf::Vector2f &in_Size = sf::Vector2f(200, 200));
	virtual ~Window();

public:

private:
};
template class Window<Widget>;
