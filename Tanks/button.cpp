#include "button.h"


sf::Font font;
Button::Button(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Widget(in_Pos, in_Size), m_ClickedListener(NULL)
{
	SetTexture("button.png");
	font.loadFromFile("C:/C++/Tanks/x64/Debug/capture-it.ttf");
	m_Text.setFont(font);
	m_Text.setCharacterSize(20);
	m_Text.setColor(sf::Color::White);
}

Button::~Button()
{
}

void Button::SetText(const wchar_t *in_Text)
{
	m_Text.setString(in_Text);
	m_Text.setOrigin(sf::Vector2f(m_Text.getLocalBounds().left + m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().top + m_Text.getLocalBounds().height / 2));
	calculatePosText();
}

const wchar_t *Button::GetText() const
{
	return m_Text.getString().toWideString().c_str();
}

void Button::SetOnClickedListener(ClickedListener in_ClickedListener)
{
	m_ClickedListener = in_ClickedListener;
}

void Button::Draw(sf::RenderWindow *in_RenderWindow)
{
	Widget::Draw(in_RenderWindow);
	in_RenderWindow->draw(m_Text);
}

void Button::Update(const sf::Time &in_Time)
{
	Widget::Update(in_Time);
}

void Button::HandleEvent(const sf::Event &in_Event)
{
	switch (in_Event.type)
	{
		case sf::Event::MouseButtonPressed:
			if (!CheckIntersect(sf::Vector2f(in_Event.mouseButton.x, in_Event.mouseButton.y)))
				break;

			if (m_ClickedListener)
				m_ClickedListener(this);
			m_Checked = true;
			break;

		case sf::Event::MouseButtonReleased:
			m_Checked = false;
			break;
	}
}

void Button::SetPos(const sf::Vector2f &in_Pos)
{
	Widget::SetPos(in_Pos);
	calculatePosText();
}

void Button::calculatePosText()
{
	m_Text.setPosition(GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2);
}
