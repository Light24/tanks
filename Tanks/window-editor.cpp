#include "window-editor.h"
#include "button.h"
#include "widget-illuminated-object.h"

WindowEditor::WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window<Widget>(in_Pos, in_Size)
{
	m_WidgetGameEditor = new WidgetGameEditor(in_Engine, sf::Vector2f(0, 0), sf::Vector2f(in_Size.x * 0.8, in_Size.y));
	m_WidgetGameEditor->AddMoveBeginListener(PREPARE_MOVE_BEGIN_LISTENER(this, &WindowEditor::onMoveBeginListener));
	m_WidgetGameEditor->AddMovingListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMoveListener));
	m_WidgetGameEditor->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMovingEndListener));
	AddWidget(m_WidgetGameEditor);

	m_WidgetTemplates = new WidgetTemplates(in_Engine, sf::Vector2f(m_WidgetGameEditor->GetSize().x, 0), sf::Vector2f(in_Size.x - m_WidgetGameEditor->GetSize().x, in_Size.y));
	m_WidgetTemplates->AddMoveBeginListener(PREPARE_MOVE_BEGIN_LISTENER(this, &WindowEditor::onMoveBeginListener));
	m_WidgetTemplates->AddMovingListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMoveListener));
	m_WidgetTemplates->AddMoveEndListener(PREPARE_MOVE_LISTENER(this, &WindowEditor::onMovingEndListener));
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

void WindowEditor::onMoveListener(Object *in_Object, const sf::Event &in_Event)
{
	in_Object->SetTexture("action_forbidden.png");
	// const WidgetIlluminatedObject *illuminatedObject = dynamic_cast<WidgetIlluminatedObject *>(in_Object);
	if (m_WidgetTemplates->CheckIntersect(sf::Vector2f(in_Event.mouseMove.x, in_Event.mouseMove.y)))
		return;

	if (!m_WidgetGameEditor->CheckIntersect(sf::Vector2f(in_Event.mouseMove.x, in_Event.mouseMove.y)))
		return;

	in_Object->SetTexture(NULL); // "action_accept.png");

	// найдем объект, с которым переекается наш объект,
	// сместим наш объект по одной из осей так, что бы избежать пересечения
	for (size_t i = 0; i != m_WidgetGameEditor->GetWidgetsCount(); ++i)
	{
		const Object *object = m_WidgetGameEditor->GetWidget(i);
		if (in_Object == object)
			continue;

		if (in_Object->CheckIntersectX(object) && in_Object->CheckIntersectY(object))
		{
			sf::Vector2f deltaPos;
			if (in_Object->GetAbsolutePos().x < object->GetAbsolutePos().x)
				deltaPos.x = (in_Object->GetAbsolutePos().x + in_Object->GetSize().x) - object->GetAbsolutePos().x;
			else
				deltaPos.x = in_Object->GetAbsolutePos().x - (object->GetAbsolutePos().x + object->GetSize().x);
			if (object->GetAbsolutePos().y > in_Object->GetAbsolutePos().y)
				deltaPos.y = (in_Object->GetAbsolutePos().y + in_Object->GetSize().y) - object->GetAbsolutePos().y;
			else
				deltaPos.y = in_Object->GetAbsolutePos().y - (object->GetAbsolutePos().y + object->GetSize().y);

			// будем выравнивать объект только по той оси, по которой мышкой глубже попали в соседнюю фигуру
			if (fabs(deltaPos.x) > fabs(deltaPos.y))
				deltaPos.x = 0;
			else
				deltaPos.y = 0;

			in_Object->SetPos(sf::Vector2f(in_Object->GetPos().x - deltaPos.x, in_Object->GetPos().y - deltaPos.y));
		}
	}
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
