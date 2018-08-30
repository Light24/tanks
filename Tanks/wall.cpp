#include "Wall.h"


Wall::Wall(const char *in_Buf) : GameObject(in_Buf)
{

}

Wall::Wall(const Wall *in_Wall) : GameObject(in_Wall)
{

}

Wall::~Wall()
{

}

GameObject *Wall::Clone() const
{
	return new Wall(this);
}

void Wall::OnIntersect(GameObject *in_GameObject)
{

}
