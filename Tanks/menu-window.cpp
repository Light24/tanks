#include "menu-window.h"
#include <functional>

#define Prepare_Callback(in_Pointer, in_Method) [in_Pointer] (Button *in_Object) -> void { (in_Pointer->*in_Method)(in_Object); }

MenuWindow::MenuWindow(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window<Widget>(in_Pos, in_Size)
{
	m_Engine = in_Engine;

	Button *button;

	button = new Button(sf::Vector2f(GetSize().x / 2, GetSize().y / 2 - 60), sf::Vector2f(120, 40));
	button->SetText(L"Играть");
	button->SetOnClickedListener(Prepare_Callback(this, &MenuWindow::onStartClicked));//  Prepare_Callback(this, MenuWindow::onStartClicked));
	AddWidget(button);

	button = new Button(sf::Vector2f(GetSize().x / 2, GetSize().y / 2), sf::Vector2f(120, 40));
	button->SetText(L"Редактор");
	button->SetOnClickedListener(Prepare_Callback(this, &MenuWindow::onEditorClicked));
	AddWidget(button);

	button = new Button(sf::Vector2f(GetSize().x / 2, GetSize().y / 2 + 60), sf::Vector2f(120, 40));
	button->SetText(L"Выход");
	button->SetOnClickedListener(Prepare_Callback(this, &MenuWindow::onExitClicked));
	AddWidget(button);
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::onStartClicked(Button *in_Button)
{
	// m_Engine->
}

void MenuWindow::onEditorClicked(Button *in_Button)
{
	// m_Engine->
}

void MenuWindow::onExitClicked(Button *in_Button)
{
	// m_Engine->
}
