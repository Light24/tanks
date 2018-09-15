#pragma once
#include "widget.h"

class WidgetText : public Widget
{
public:
	WidgetText(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WidgetText();

public:
	void SetText(const wchar_t *in_Text);
	const wchar_t *GetText() const;

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

	virtual void SetPos(const sf::Vector2f &in_Pos) override;

private:
	void calculatePosText();

private:
	sf::Text m_Text;
};
