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

	typedef ObjectType *(*MoveBeginListener)(ObjectType *in_Widget);
	typedef void (*MoveListener)(ObjectType *in_Widget);
	void SetMoveBeginListener(MoveBeginListener in_MovedListener);
	void SetMovingListener(MoveListener in_MovedListener);
	void SetMoveEndListener(MoveListener in_MovedListener);

	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	ObjectType *m_MovableWidget;
	sf::Vector2f m_MovableWidgetOffset;
	MoveBeginListener m_MoveBeginListener;
	MoveListener m_MovingListener;
	MoveListener m_MoveEndListener;
};
template class ContainerMoving<Widget>;
