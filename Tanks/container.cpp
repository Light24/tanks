#include "container.h"


template <typename ObjectType>
Container<ObjectType>::Container(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Widget(in_Pos, in_Size), m_WidgetsCount(0), m_Widgets(NULL)
{
}

template <typename ObjectType>
Container<ObjectType>::~Container()
{
	if (m_Widgets)
	{
		delete m_Widgets;
		m_Widgets = NULL;
	}
}

template <typename ObjectType>
void Container<ObjectType>::SetPos(const sf::Vector2f &in_Pos)
{
	Widget::SetPos(in_Pos);
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->CalculateSpritePos();
}

template <typename ObjectType>
void Container<ObjectType>::AddWidget(ObjectType *in_Widget)
{
	ObjectType **pWidgets = m_Widgets;
	
	m_Widgets = new ObjectType*[++m_WidgetsCount];
	for (size_t i = 0; i != (m_WidgetsCount - 1); ++i)
		m_Widgets[i] = pWidgets[i];
	m_Widgets[m_WidgetsCount - 1] = in_Widget;

	in_Widget->SetParent(this);

	delete pWidgets;
}

template <typename ObjectType>
bool Container<ObjectType>::RemoveWidget(ObjectType *in_Widget)
{
	size_t widgetNum = -1;
	for (size_t i = 0; i != m_WidgetsCount; ++i)
	{
		if (m_Widgets[i] == in_Widget)
		{
			widgetNum = i;
			break;
		}
	}

	if (widgetNum == -1)
		return false;

	delete m_Widgets[widgetNum];
	m_Widgets[widgetNum] = m_Widgets[--m_WidgetsCount];

	return true;
}

template <typename ObjectType>
ObjectType *Container<ObjectType>::GetWidget(const size_t in_Num) const
{
	if (in_Num < 0 || in_Num >= m_WidgetsCount)
		return NULL;

	return m_Widgets[in_Num];
}

template <typename ObjectType>
size_t Container<ObjectType>::GetWidgetsCount() const
{
	return m_WidgetsCount;
}

template <typename ObjectType>
void Container<ObjectType>::Draw(sf::RenderWindow *in_RenderWindow)
{
	Widget::Draw(in_RenderWindow);
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->Draw(in_RenderWindow);
}

template <typename ObjectType>
void Container<ObjectType>::Update(const sf::Time &in_Time)
{
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->Update(in_Time);
}

template <>
void Container<Widget>::HandleEvent(const sf::Event &in_Event)
{
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->HandleEvent(in_Event);
}

template <typename ObjectType>
void Container<ObjectType>::HandleEvent(const sf::Event &in_Event)
{
}

