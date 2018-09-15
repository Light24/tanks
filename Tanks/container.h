#pragma once
#include "widget.h"
#include "SFML/graphics.hpp"
#include "game-object.h"

class Container : public Widget
{
public:
	Container(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~Container();

public:
	virtual void SetPos(const sf::Vector2f &in_Pos) override;

	virtual void AddWidget(Object *in_Widget, bool in_Top = false);
	virtual bool RemoveWidget(Object *in_Widget, bool in_Deleting = true);
	Object *GetWidget(const size_t in_Num) const;
	size_t GetWidgetsCount() const;

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	size_t m_WidgetsCount;
	Object **m_Widgets;
};
