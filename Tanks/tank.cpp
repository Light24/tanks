#include "tank.h"
#include "config.h"

Tank::Tank(const char *in_Buf) : GameObject(in_Buf)
{
	const char *pBuf = in_Buf;
}


Tank::Tank(const Tank *in_Tank) : GameObject(in_Tank)
{
}

Tank::~Tank()
{
}

GameObject *Tank::Clone() const
{
	return new Tank(this);
}

void Tank::OnIntersect(GameObject *in_GameObject)
{

}