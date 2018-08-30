#pragma once
#include "widget.h"
#include "container.h"
#include "game-object.h"

template <typename ObjectType>
class ContainerMoving : public Container<ObjectType>
{
public:
	ContainerMoving(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~ContainerMoving();
	
	typedef void(*MovedListener)(ObjectType *in_Widget);
	void SetMovedListener(MovedListener in_MovedListener);

	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	ObjectType *m_MovableWidget;
	MovedListener m_MovedListener;
};
