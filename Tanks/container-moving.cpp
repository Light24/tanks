#include "container-moving.h"


template <typename ObjectType>
ContainerMoving<ObjectType>::ContainerMoving(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size)
{
	m_MovableWidget = NULL;

	m_MoveBeginListener = NULL;
	m_MovingListener = NULL;
	m_MoveEndListener = NULL;
}

template <typename ObjectType>
ContainerMoving<ObjectType>::~ContainerMoving()
{
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::SetMoveBeginListener(MoveBeginListener in_MoveListener)
{
	m_MoveBeginListener = in_MoveListener;
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::SetMovingListener(MoveListener in_MoveListener)
{
	m_MovingListener = in_MoveListener;
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::SetMoveEndListener(MoveListener in_MoveListener)
{
	m_MoveEndListener = in_MoveListener;
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::HandleEvent(const sf::Event &in_Event)
{
	switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			ObjectType *selectedObject(NULL);
			for (size_t i = 0; i != GetWidgetsCount(); ++i)
			{
				ObjectType *object = GetWidget(i);
				if (object->CheckIntersect(sf::Vector2f(in_Event.mouseButton.x, in_Event.mouseButton.y)))
				{
					selectedObject = object;
					break;
				}
			}
			if (!selectedObject)
				break;

			const sf::Vector2f &posAbsolute = selectedObject->GetAbsolutePos();

			m_MovableWidget = NULL;
			if (m_MoveBeginListener)
			{
				m_MovableWidget = m_MoveBeginListener(selectedObject);
				m_MovableWidget = m_MovableWidget ? m_MovableWidget : selectedObject;
			}
			else
			{
				m_MovableWidget = selectedObject;
			}
			m_MovableWidgetOffset = sf::Vector2f(in_Event.mouseButton.x - posAbsolute.x, in_Event.mouseButton.y - posAbsolute.y);

			break;
		}
		case sf::Event::MouseMoved:
		{
			if (!m_MovableWidget)
				break;
			if (m_MovingListener)
				m_MovingListener(m_MovableWidget);

			const sf::Vector2f &posAbsolute = m_MovableWidget->GetAbsolutePos();
			const sf::Vector2f &posRelative = m_MovableWidget->GetPos();
			const sf::Vector2f &size = m_MovableWidget->GetSize();
			m_MovableWidget->SetPos(sf::Vector2f(in_Event.mouseMove.x - (posAbsolute.x - posRelative.x) - m_MovableWidgetOffset.x, in_Event.mouseMove.y - (posAbsolute.y - posRelative.y) - m_MovableWidgetOffset.y));

			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			if (!m_MovableWidget)
				break;

			if (m_MoveEndListener)
				m_MoveEndListener(m_MovableWidget);

			m_MovableWidget = NULL;

			break;
		}
	}

	Container::HandleEvent(in_Event);
}
