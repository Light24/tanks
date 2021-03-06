#include "container-moving.h"


ContainerMoving::ContainerMoving(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size)
{
	m_MovableWidget = NULL;
}

ContainerMoving::~ContainerMoving()
{
}

void ContainerMoving::AddMoveBeginListener(MoveBeginListener in_MoveListener)
{
	m_MoveBeginListeners.push_back(in_MoveListener);
}

void ContainerMoving::AddMovingListener(MoveListener in_MoveListener)
{
	m_MovingListeners.push_back(in_MoveListener);
}

void ContainerMoving::AddMoveEndListener(MoveListener in_MoveListener)
{
	m_MoveEndListeners.push_back(in_MoveListener);
}

void ContainerMoving::HandleEvent(const sf::Event &in_Event)
{
	switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			Object *selectedObject(NULL);
			for (size_t i = 0; i != GetWidgetsCount(); ++i)
			{
				Object *object = GetWidget(i);
				if (object->CheckIntersect(sf::Vector2f(in_Event.mouseButton.x, in_Event.mouseButton.y)))
				{
					selectedObject = object;
					break;
				}
			}
			if (!selectedObject)
				break;

			for (auto it = m_MoveBeginListeners.begin(); it != m_MoveBeginListeners.end(); ++it)
				selectedObject = (*it)(selectedObject, in_Event);
			m_MovableWidget = selectedObject;
			if (!selectedObject)
				break;

			const sf::Vector2f &posAbsolute = selectedObject->GetAbsolutePos();
			m_MovableWidgetOffset = sf::Vector2f(in_Event.mouseButton.x - posAbsolute.x, in_Event.mouseButton.y - posAbsolute.y);

			break;
		}
		case sf::Event::MouseMoved:
		{
			if (!m_MovableWidget)
				break;

			const sf::Vector2f &posAbsolute = m_MovableWidget->GetAbsolutePos();
			const sf::Vector2f &posRelative = m_MovableWidget->GetPos();
			const sf::Vector2f &size = m_MovableWidget->GetSize();
			m_MovableWidget->SetPos(sf::Vector2f(in_Event.mouseMove.x - (posAbsolute.x - posRelative.x) - m_MovableWidgetOffset.x, in_Event.mouseMove.y - (posAbsolute.y - posRelative.y) - m_MovableWidgetOffset.y));

			for (auto it = m_MovingListeners.begin(); it != m_MovingListeners.end(); ++it)
				(*it)(m_MovableWidget, in_Event);

			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			if (!m_MovableWidget)
				break;

			for (auto it = m_MoveEndListeners.begin(); it != m_MoveEndListeners.end(); ++it)
				(*it)(m_MovableWidget, in_Event);

			m_MovableWidget = NULL;

			break;
		}
	}

	Container::HandleEvent(in_Event);
}
