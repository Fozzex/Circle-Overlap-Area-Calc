#pragma once
#include <SFML/Graphics.hpp>

#include "Draggable.h"

namespace
{
	const double PI = 3.1415926535;
}

class DraggableCircle : public sf::CircleShape, public Draggable
{
public:

	DraggableCircle(float radius);
	
	float GetArea() const;
	float GetOverlapArea(const DraggableCircle& circle) const;
	inline float GetTotalRadius() const { return this->getRadius() + this->getOutlineThickness(); }

protected:

	bool ContainsPoint(const sf::Vector2f& point) const override;

};