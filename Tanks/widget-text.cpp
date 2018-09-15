#include "widget-text.h"

sf::Font font2;
WidgetText::WidgetText(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Widget(in_Pos, in_Size)
{
	SetTexture("button.png");
	font2.loadFromFile("C:/C++/Tanks/x64/Debug/capture-it.ttf");
	m_Text.setFont(font2);
	m_Text.setCharacterSize(20);
	m_Text.setColor(sf::Color::White);
}

WidgetText::~WidgetText()
{
}


void WidgetText::SetText(const wchar_t *in_Text)
{
	m_Text.setString(in_Text);
	m_Text.setOrigin(sf::Vector2f(m_Text.getLocalBounds().left + m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().top + m_Text.getLocalBounds().height / 2));
	calculatePosText();
}

const wchar_t *WidgetText::GetText() const
{
	return m_Text.getString().toWideString().c_str();
}

void WidgetText::Draw(sf::RenderWindow *in_RenderWindow)
{
	Widget::Draw(in_RenderWindow);
	in_RenderWindow->draw(m_Text);
}

void WidgetText::Update(const sf::Time &in_Time)
{
	Widget::Update(in_Time);
}

void WidgetText::HandleEvent(const sf::Event &in_Event)
{
}

void WidgetText::SetPos(const sf::Vector2f &in_Pos)
{
	Widget::SetPos(in_Pos);
	calculatePosText();
}

void WidgetText::calculatePosText()
{
	m_Text.setPosition(GetAbsolutePos().x + GetSize().x / 2, GetAbsolutePos().y + GetSize().y / 2);
}
