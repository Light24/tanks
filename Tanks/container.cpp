#include "container.h"


Container::Container(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Widget(in_Pos, in_Size), m_WidgetsCount(0), m_Widgets(NULL)
{
}

Container::~Container()
{
	if (m_Widgets)
	{
		delete m_Widgets;
		m_Widgets = NULL;
	}
}

void Container::SetPos(const sf::Vector2f &in_Pos)
{
	Widget::SetPos(in_Pos);
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->CalculateSpritePos();
}

void Container::AddWidget(Object *in_Widget, bool in_Top)
{
	Object **pWidgets = m_Widgets;
	
	m_Widgets = new Object*[++m_WidgetsCount];
	if (in_Top)
	{
		for (size_t i = 0; i != (m_WidgetsCount - 1); ++i)
			m_Widgets[i + 1] = pWidgets[i];
		m_Widgets[0] = in_Widget;
	}
	else
	{
		for (size_t i = 0; i != (m_WidgetsCount - 1); ++i)
			m_Widgets[i] = pWidgets[i];
		m_Widgets[m_WidgetsCount - 1] = in_Widget;

	}

	in_Widget->SetParent(this);

	delete pWidgets;
}

bool Container::RemoveWidget(Object *in_Widget, bool in_Deleting)
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

	if (in_Deleting)
		delete m_Widgets[widgetNum];
	else
		if (m_Widgets[widgetNum]->GetParent() == this)
			m_Widgets[widgetNum]->SetParent(NULL);
	m_Widgets[widgetNum] = m_Widgets[--m_WidgetsCount];

	return true;
}

Object *Container::GetWidget(const size_t in_Num) const
{
	if (in_Num < 0 || in_Num >= m_WidgetsCount)
		return NULL;

	return m_Widgets[in_Num];
}

size_t Container::GetWidgetsCount() const
{
	return m_WidgetsCount;
}

void Container::Draw(sf::RenderWindow *in_RenderWindow)
{
	Widget::Draw(in_RenderWindow);
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->Draw(in_RenderWindow);
}

void Container::Update(const sf::Time &in_Time)
{
	Widget::Update(in_Time);
	for (size_t i = 0; i != m_WidgetsCount; ++i)
		m_Widgets[i]->Update(in_Time);
}

void Container::HandleEvent(const sf::Event &in_Event)
{
	for (size_t i = 0; i != m_WidgetsCount; ++i)
	{
		Widget *widget = dynamic_cast<Widget *>(m_Widgets[i]);
		if (!widget)
			continue;

		widget->HandleEvent(in_Event);
	}
}
