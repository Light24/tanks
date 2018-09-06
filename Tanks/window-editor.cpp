#include "window-editor.h"
#include "button.h"
#include "widget-illuminated-object.h"

WindowEditor::WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window(in_Pos, in_Size)
{
	m_Engine = in_Engine;
	m_IsShiftPressed = false;

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

	loadLevel();
}

WindowEditor::~WindowEditor()
{
	saveLevel();
}


void WindowEditor::HandleEvent(const sf::Event &in_Event)
{
	Window::HandleEvent(in_Event);

	if (in_Event.type == sf::Event::KeyPressed)
	{
		if (in_Event.key.code == sf::Keyboard::Escape)
		{
			m_Engine->RemoveWindow(this);
			return;
		}
		else if (in_Event.key.code == sf::Keyboard::LShift)
		{
			setShiftPressed(true);
		}
	}
	else if (in_Event.type == sf::Event::KeyReleased)
	{
		setShiftPressed(false);
	}
}

Object *WindowEditor::onMoveBeginListener(Object *in_Object, const sf::Event &in_Event)
{
	Container *container = dynamic_cast<Container *>(in_Object->GetParent());

	// найдем игрока
	if (dynamic_cast<GameObject *>(in_Object)->GetSubtype() == Object_Subtype_Player)
	{
		// если у нас уже есть игрок и мы хотим создать нового игрока, то запретим это делать
		const Object *player = NULL;
		for (size_t i = 0; i != m_WidgetGameEditor->GetWidgetsCount(); ++i)
		{
			const GameObject *object = dynamic_cast<GameObject *>(m_WidgetGameEditor->GetWidget(i));
			if (object->GetSubtype() == Object_Subtype_Player)
			{
				player = object;
				break;
			}
		}
		if (player)
		{
			if (in_Object != player)
			{
				container->RemoveWidget(in_Object);
				return NULL;
			}
		}
	}

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
			{
				if (isShiftPressed())
					deltaPos.x = (in_Object->GetAbsolutePos().x - object->GetAbsolutePos().x);
				else
					deltaPos.x = 0;
			}
			else
			{
				if (isShiftPressed())
					deltaPos.y = (in_Object->GetAbsolutePos().y - object->GetAbsolutePos().y);
				else
					deltaPos.y = 0;
			}

			in_Object->SetPos(sf::Vector2f(in_Object->GetPos().x - deltaPos.x, in_Object->GetPos().y - deltaPos.y));
		}
	}
}

void WindowEditor::onMovingEndListener(Object *in_Object, const sf::Event &in_Event)
{
	const sf::Vector2f pos = in_Object->GetAbsolutePos();

	Object *object = dynamic_cast<WidgetIlluminatedObject *>(in_Object)->GetOwnedObject();
	object->SetParent(NULL);

	Container *container = dynamic_cast<Container *>(in_Object->GetParent());
	container->RemoveWidget(in_Object);
	if (m_WidgetTemplates->CheckIntersect(sf::Vector2f(in_Event.mouseButton.x, in_Event.mouseButton.y)))
	{
		delete object;
		return;
	}

	object->SetPos(pos);
	m_WidgetGameEditor->AddWidget(object);
}

void WindowEditor::loadLevel()
{
	// Container<GameObject> *container = dynamic_cast<Container<GameObject> *>(m_WidgetGameEditor);
	m_Engine->GetConfigManager()->LoadLevel("data/levels/level_0.lvl", m_WidgetGameEditor);
}

void WindowEditor::saveLevel()
{
	// Container<GameObject> *container = dynamic_cast<Container<GameObject> *>(m_WidgetGameEditor);
	m_Engine->GetConfigManager()->SaveLevel("data/levels/level_0.lvl", m_WidgetGameEditor);
}


const void WindowEditor::setShiftPressed(bool isPressed)
{
	m_IsShiftPressed = isPressed;
}

bool WindowEditor::isShiftPressed() const
{
	return m_IsShiftPressed;
}
