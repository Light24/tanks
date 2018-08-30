#include "widget.h"


Widget::Widget(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Object(in_Pos, in_Size)
{

}

Widget::~Widget()
{

}

void Widget::Draw(sf::RenderWindow *in_RenderWindow)
{
	sf::Vector2u screenSize = in_RenderWindow->getSize();

	sf::View view;// (in_RenderWindow->getDefaultView());
	view.setViewport(sf::FloatRect(GetPos().x / screenSize.x, GetPos().y / screenSize.y, GetSize().x / screenSize.x, GetSize().y / screenSize.y));
	Object::Draw(in_RenderWindow);
	// in_RenderWindow->setView(view);
}