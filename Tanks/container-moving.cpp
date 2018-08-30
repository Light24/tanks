#include "container-moving.h"


template <typename ObjectType>
ContainerMoving<ObjectType>::ContainerMoving(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size)
{
}


template <typename ObjectType>
ContainerMoving<ObjectType>::~ContainerMoving()
{
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::SetMovedListener(MovedListener in_MovedListener)
{
	m_MovedListener = in_MovedListener;
}

template <>
void ContainerMoving<GameObject>::HandleEvent(const sf::Event &in_Event)
{
	/*switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
			GameObject *selectedObject = NULL;
			for (size_t i = 0; i != GetWidgetsCount(); ++i)
			{
				const GameObject *object = GetWidget(i);
				if (object->)
				{
					selectedObject = object;
					break;
				}
			}

			if (selectedObject)
			{
				m_MovableWidget = selectedObject;
			}
				
			break;
		case sf::Event::MouseMoved:
			m_MovableWidget->

			break;
		case sf::Event::MouseButtonReleased:
			if (m_MovedListener && m_MovableWidget)
				m_MovedListener(m_MovableWidget);

			m_MovedListener = NULL;
			m_MovableWidget = NULL;

			break;
	}*/

	Container::HandleEvent(in_Event);
}


/*
template <typename ObjectType>
void ContainerMoving<ObjectType>::HandleEvent(const sf::Event &in_Event)
{
	switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
			// get selected widget
			break;
		case sf::Event::MouseMoved:

			break;
		case sf::Event::MouseButtonReleased:
			m_MovedListener(m_MovableWidget);
			break;
	}

	Container::HandleEvent(event);
}

template <typename ObjectType>
void ContainerMoving<ObjectType>::HandleEvent(const sf::Event &in_Event)
{
	switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
			// get selected widget
			break;
		case sf::Event::MouseMoved:

			break;
		case sf::Event::MouseButtonReleased:
			m_MovedListener(m_MovableWidget);
			break;
	}

	Container::HandleEvent(event);
}
*/