#include "animation-manager.h"


AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{
	for (size_t i = 0; i != m_Animations.size(); ++i)
		delete m_Animations[i];
	m_Animations.clear();

	for (size_t i = 0; i != m_TemplatesAnimations.size(); ++i)
		delete m_TemplatesAnimations[i];
	m_TemplatesAnimations.clear();
}

AnimationManager *AnimationManager::m_Instance;
AnimationManager *AnimationManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new AnimationManager();

	return m_Instance;
}


void AnimationManager::Play(sf::RenderWindow *in_RenderWindow, const sf::Time &in_Time)
{
	for (auto it = m_Animations.begin(); it != m_Animations.end(); )
	{
		(*it)->Draw(in_RenderWindow);
		(*it)->Update(in_Time);
		
		if (!(*it)->IsAnimationEnd())
		{
			++it;
			continue;
		}
		
		Animation *animation = (*it);
		it = m_Animations.erase(it);
		delete animation;
	}
}

Animation *AnimationManager::GetTemplateAnimation(const Animation_Type in_AnimationType)
{
	for (auto it = m_TemplatesAnimations.begin(); it != m_TemplatesAnimations.end(); ++it)
		if ((*it)->HasAnimationType(in_AnimationType))
			return *it;

	return NULL;
}

void AnimationManager::AddAnimation(Animation *in_Animation)
{
	m_Animations.push_back(in_Animation);
}

void AnimationManager::AddTemplateAnimation(Animation *in_Animation)
{
	m_TemplatesAnimations.push_back(in_Animation);
}
