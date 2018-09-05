#include "artificial-intelligence.h"

#include "tank.h"


ArtificialIntelligence::ArtificialIntelligence()
{
}

ArtificialIntelligence::~ArtificialIntelligence()
{
}


void ArtificialIntelligence::Update(Container<Object> *in_Container, const sf::Time &in_Time)
{
	for (size_t i = 0; i != in_Container->GetWidgetsCount(); ++i)
	{
		GameObject *gameObject = dynamic_cast<GameObject *>(in_Container->GetWidget(i));
		if (gameObject->GetType() != Object_Type_Tank)
			continue;
		if (gameObject->GetSubtype() == Object_Subtype_Player)
			continue;

		if (rand() % 1000 == 0)
		{
			dynamic_cast<Tank *>(gameObject)->Fire();
		}

		if (gameObject->GetVelocity().x == 0 && gameObject->GetVelocity().y == 0)
		{
			sf::Vector2f direction;
			size_t directionAxis = rand() % 2;
			int directionSign = (rand() % 2 == 1) ? 1 : -1;
			direction.x = (directionAxis == 0) ? directionSign : 0;
			direction.y = (directionAxis == 1) ? directionSign : 0;

			gameObject->SetVelocity(direction);
		}
	}
}
