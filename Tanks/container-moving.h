#pragma once
#include "widget.h"
#include "container.h"
#include "game-object.h"
#include <functional>

#define PREPARE_MOVE_BEGIN_LISTENER(in_Pointer, in_Method) [in_Pointer] (Object *in_Object, const sf::Event &in_Event) -> Object * { return (in_Pointer->*in_Method)(in_Object, in_Event); }
#define PREPARE_MOVE_LISTENER(in_Pointer, in_Method) [in_Pointer] (Object *in_Object, const sf::Event &in_Event) -> void { (in_Pointer->*in_Method)(in_Object, in_Event); }

template <typename ObjectType>
class ContainerMoving : public Container<ObjectType>
{
public:
	ContainerMoving(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~ContainerMoving();

	typedef std::function<Object *(Object *in_Object, const sf::Event &in_Event)> MoveBeginListener;
	typedef std::function<void(Object *in_Object, const sf::Event &in_Event)> MoveListener;
	void AddMoveBeginListener(MoveBeginListener in_MovedListener);
	void AddMovingListener(MoveListener in_MovedListener);
	void AddMoveEndListener(MoveListener in_MovedListener);

	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	ObjectType *m_MovableWidget;
	sf::Vector2f m_MovableWidgetOffset;

	std::vector<MoveBeginListener> m_MoveBeginListeners;
	std::vector<MoveListener> m_MovingListeners;
	std::vector<MoveListener> m_MoveEndListeners;
};
template class ContainerMoving<Object>;
