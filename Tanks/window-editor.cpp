#include "window-editor.h"
#include "button.h"
#include "widget-illuminated-object.h"

WindowEditor::WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window<Widget>(in_Pos, in_Size)
{
	m_WidgetGameEditor = new WidgetGameEditor(in_Engine, sf::Vector2f(0, 0), sf::Vector2f(in_Size.x * 0.8, in_Size.y));
	m_WidgetGameEditor->AddMoveBeginListener(PREPARE_MOVE_BEGIN_LISTENER(this, &WindowEditor::onMoveBeginListener));
	m_WidgetGameEditor->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMovingEndListener));
	m_WidgetGameEditor->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMoveListener));
	AddWidget(m_WidgetGameEditor);

	m_WidgetTemplates = new WidgetTemplates(in_Engine, sf::Vector2f(m_WidgetGameEditor->GetSize().x, 0), sf::Vector2f(in_Size.x - m_WidgetGameEditor->GetSize().x, in_Size.y));
	m_WidgetTemplates->AddMoveBeginListener(PREPARE_MOVE_BEGIN_LISTENER(this, &WindowEditor::onMoveBeginListener));
	m_WidgetTemplates->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMovingEndListener));
	m_WidgetGameEditor->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMoveListener));
	AddWidget(m_WidgetTemplates);
}


WindowEditor::~WindowEditor()
{
}

Object *WindowEditor::onMoveBeginListener(Object *in_Object, const sf::Event &in_Event)
{
	Container<Object> *container = dynamic_cast<Container<Object> *>(in_Object->GetParent());

	WidgetIlluminatedObject *illuminatedObject = new WidgetIlluminatedObject(in_Object);
	container->AddWidget(illuminatedObject);

	container->RemoveWidget(in_Object, false);

	return illuminatedObject;
}

void WindowEditor::onMovingEndListener(Object *in_Object, const sf::Event &in_Event)
{
	const sf::Vector2f pos = in_Object->GetAbsolutePos();

	Object *object = dynamic_cast<WidgetIlluminatedObject *>(in_Object)->GetOwnedObject();
	object->SetParent(NULL);

	Container<Object> *container = dynamic_cast<Container<Object> *>(in_Object->GetParent());
	container->RemoveWidget(in_Object);
	if (m_WidgetTemplates->CheckIntersect(sf::Vector2f(in_Event.mouseButton.x, in_Event.mouseButton.y)))
	{
		delete object;
		return;
	}

	object->SetPos(pos);
	m_WidgetGameEditor->AddWidget(object);
}

void WindowEditor::onMoveListener(Object *in_Object, const sf::Event &in_Event)
{
	if (m_WidgetTemplates->CheckIntersect(sf::Vector2f(in_Event.mouseMove.x, in_Event.mouseMove.y)))
	{
	}
}
