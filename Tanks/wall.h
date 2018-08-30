#pragma once
#include "game-object.h"

class Wall : public GameObject
{
public:
	Wall(const char *in_Buf);
	Wall(const Wall *in_Wall);
	~Wall();

	virtual GameObject *Clone() const override;

public:
	virtual void OnIntersect(GameObject *in_GameObject) override;

private:
};
