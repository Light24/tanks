#include "window-editor.h"
#include "button.h"

WindowEditor::WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : ContainerMoving<Widget>(in_Pos, in_Size)
{
	Button *button = new Button(sf::Vector2f(0, 0), sf::Vector2f(120, 40));
	AddWidget(button);

	SetMoveBeginListener([](Widget *in_Widget) -> Widget* {
		return in_Widget;
	});
}


WindowEditor::~WindowEditor()
{
}
