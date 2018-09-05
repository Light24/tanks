#pragma once
#include "animation.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	static AnimationManager *GetInstance();

public:
	void Play(sf::RenderWindow *in_RenderWindow, const sf::Time &in_Time);

	Animation *GetTemplateAnimation(const Animation_Type in_AnimationType);

public:
	void AddTemplateAnimation(Animation *in_Animation);
	void AddAnimation(Animation *in_Animation);

private:
	static AnimationManager *m_Instance;

	std::vector<Animation *> m_TemplatesAnimations;
	std::vector<Animation *> m_Animations;
};
