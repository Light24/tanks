#include "widget-illuminated-object.h"


WidgetIlluminatedObject::WidgetIlluminatedObject(Object *in_Object) : Widget(sf::Vector2f(), sf::Vector2f())
{
	SetOwnedObject(in_Object);
}

WidgetIlluminatedObject::~WidgetIlluminatedObject()
{
}

Object *WidgetIlluminatedObject::GetOwnedObject() const
{
	return m_OwnedObject;
}

void WidgetIlluminatedObject::SetOwnedObject(Object *in_Object)
{
	const sf::Vector2f pos = in_Object->GetPos();

	m_OwnedObject = in_Object;
	SetParent(in_Object->GetParent());
	m_OwnedObject->SetPos(sf::Vector2f(0, 0));
	SetPos(pos);

	in_Object->SetParent(this);
}

void WidgetIlluminatedObject::SetPos(const sf::Vector2f &in_Pos)
{
	Widget::SetPos(in_Pos);
	m_OwnedObject->CalculateSpritePos();
}

void WidgetIlluminatedObject::Draw(sf::RenderWindow *in_RenderWindow)
{
	Widget::Draw(in_RenderWindow);
	m_OwnedObject->Draw(in_RenderWindow);
}

void WidgetIlluminatedObject::Update(const sf::Time &in_Time)
{
	m_OwnedObject->Update(in_Time);
}

void WidgetIlluminatedObject::HandleEvent(const sf::Event &in_Event)
{
}