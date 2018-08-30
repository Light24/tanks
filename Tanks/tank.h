#pragma once
#include "game-object.h"

class Tank : public GameObject
{
public:
	Tank(const char *in_Buf);
	Tank(const Tank *in_Tank);
	~Tank();

	virtual GameObject *Clone() const override;

public:
	virtual void OnIntersect(GameObject *in_GameObject) override;

private:
};