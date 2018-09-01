#include "menu-window.h"
#include "window-game.h"
#include "window-editor.h"

#include <functional>

#define PREPARE_CALLBACK(in_Pointer, in_Method) [in_Pointer] (Button *in_Object) -> void { (in_Pointer->*in_Method)(in_Object); }

#define BUTTON_SIZE sf::Vector2f(120, 40)
#define BUTTON_OFFSET_Y 10

MenuWindow::MenuWindow(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window<Widget>(in_Pos, in_Size)
{
	m_Engine = in_Engine;

	Button *button;

	button = new Button(sf::Vector2f(GetSize().x / 2 - BUTTON_SIZE.x / 2, GetSize().y / 2 - (BUTTON_SIZE.y + BUTTON_OFFSET_Y)), BUTTON_SIZE);
	button->SetText(L"Играть");
	button->SetOnClickedListener(PREPARE_CALLBACK(this, &MenuWindow::onStartClicked));
	AddWidget(button);

	button = new Button(sf::Vector2f(GetSize().x / 2 - BUTTON_SIZE.x / 2, GetSize().y / 2), BUTTON_SIZE);
	button->SetText(L"Редактор");
	button->SetOnClickedListener(PREPARE_CALLBACK(this, &MenuWindow::onEditorClicked));
	AddWidget(button);

	button = new Button(sf::Vector2f(GetSize().x / 2 - BUTTON_SIZE.x / 2, GetSize().y / 2 + (BUTTON_SIZE.y + BUTTON_OFFSET_Y)), BUTTON_SIZE);
	button->SetText(L"Выход");
	button->SetOnClickedListener(PREPARE_CALLBACK(this, &MenuWindow::onExitClicked));
	AddWidget(button);
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::onStartClicked(Button *in_Button)
{
	Window *window = new WindowGame(m_Engine, sf::Vector2f(), m_Engine->GetSize());
	m_Engine->AddWindow(window);
}

void MenuWindow::onEditorClicked(Button *in_Button)
{
	Window *window = new WindowEditor(m_Engine, sf::Vector2f(), m_Engine->GetSize());
	m_Engine->AddWindow(window);
}

void MenuWindow::onExitClicked(Button *in_Button)
{
	m_Engine->Close();
}
