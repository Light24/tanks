#pragma once
#include "widget.h"
#include <functional>

class Button : public Widget
{
public:
	Button(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~Button();

public:
	void SetText(const wchar_t *in_Text);
	const wchar_t *GetText() const;

	typedef std::function<void (Button *)> ClickedListener;
	void SetOnClickedListener(ClickedListener in_ClickedListener);

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

	virtual void SetPos(const sf::Vector2f &in_Pos) override;

private:
	void calculatePosText();

private:
	sf::Text m_Text;

	bool m_Checked;
	ClickedListener m_ClickedListener;
};

