#include "window.h"

template <typename ObjectType>
Window<ObjectType>::Window(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size)
{
}

template <typename ObjectType>
Window<ObjectType>::~Window()
{
}