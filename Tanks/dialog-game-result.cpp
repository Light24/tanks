#include "dialog-game-result.h"
#include "widget-text.h"


DialogGameResult::DialogGameResult(const bool in_LevelComplete, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window(in_Pos, in_Size)
{
	if (in_LevelComplete)
	{
		WidgetText *widgetText = new WidgetText(sf::Vector2f(0, 0), sf::Vector2f(250, 30));
		widgetText->SetText(L"Победа! Следующий уровень?");
		AddWidget(widgetText);

		Button *buttonExit = new Button(sf::Vector2f(0, 50), sf::Vector2f(120, 30));
		buttonExit->SetText(L"Выход");
		buttonExit->SetOnClickedListener(PREPARE_CALLBACK(this, &DialogGameResult::OnExitListener));
		AddWidget(buttonExit);

		Button *buttonNextLevel = new Button(sf::Vector2f(130, 50), sf::Vector2f(120, 30));
		buttonNextLevel->SetText(L"Продолжить");
		buttonNextLevel->SetOnClickedListener(PREPARE_CALLBACK(this, &DialogGameResult::OnNextLevelListener));
		AddWidget(buttonNextLevel);
	}
	else
	{
		WidgetText *widgetText = new WidgetText(sf::Vector2f(0, 0), sf::Vector2f(250, 30));
		widgetText->SetText(L"Поражение! Ещё раз?");
		AddWidget(widgetText);

		Button *buttonExit = new Button(sf::Vector2f(0, 50), sf::Vector2f(120, 30));
		buttonExit->SetText(L"Выход");
		buttonExit->SetOnClickedListener(PREPARE_CALLBACK(this, &DialogGameResult::OnExitListener));
		AddWidget(buttonExit);

		Button *buttonRestart = new Button(sf::Vector2f(130, 50), sf::Vector2f(120, 30));
		buttonRestart->SetText(L"Повторить");
		buttonRestart->SetOnClickedListener(PREPARE_CALLBACK(this, &DialogGameResult::OnRestartListener));
		AddWidget(buttonRestart);
	}
}

DialogGameResult::~DialogGameResult()
{
}


void DialogGameResult::OnExitListener(Button *in_Button)
{

}

void DialogGameResult::OnNextLevelListener(Button *in_Button)
{

}

void DialogGameResult::OnRestartListener(Button *in_Button)
{

}
