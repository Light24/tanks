#pragma once

enum Animation_Type
{
	Idle,
	Top,
	Bottom,
	Left,
	Right,
};

class Animation
{
public:
	Animation();
	~Animation();

public:
	void LoadAnimation();

	void SetAnimationType(Animation_Type in_AnimationType);

	void Draw(sf::RenderWindow *in_RenderWindow);

private:
	Animation_Type m_AnimationType;
};
