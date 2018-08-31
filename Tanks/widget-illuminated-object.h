#pragma once
#include "widget.h"

class WidgetIlluminatedObject : public Widget
{
public:
	WidgetIlluminatedObject(Object *in_Object);
	~WidgetIlluminatedObject();

public:
	Object *GetOwnedObject() const;
	void SetOwnedObject(Object *in_Object);

public:
	virtual void SetPos(const sf::Vector2f &in_Pos) override;

	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	Object *m_OwnedObject;
};

