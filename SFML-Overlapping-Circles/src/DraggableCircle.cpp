#include "DraggableCircle.h"

DraggableCircle::DraggableCircle(float radius) :
	sf::CircleShape(radius)
{
	this->SetBase(this);
}

bool DraggableCircle::ContainsPoint(const sf::Vector2f& point) const
{
	sf::Vector2f centre(this->GetCentre());
	sf::Vector2f offset(point.x - centre.x, point.y - centre.y);

	return (offset.x * offset.x) + (offset.y * offset.y) < (this->GetTotalRadius() * this->GetTotalRadius());
}

float DraggableCircle::GetArea() const
{
	return (this->getRadius() * this->getRadius()) * (float)PI;
}

float DraggableCircle::GetOverlapArea(const DraggableCircle& circle) const
{
	float distanceX = this->GetCentre().x - circle.GetCentre().x;
	float distanceY = this->GetCentre().y - circle.GetCentre().y;
	float distance = sqrtf((distanceX * distanceX) + (distanceY * distanceY));

	float radius = this->getRadius();
	float halfRadius = radius / 2.0f;

	float intersectAngle = acos((distance / 2) / radius) * 2;
	float sectorArea = 0.5f * (radius * radius) * intersectAngle;

	float triangleArea = 0.5f * (radius * radius) * sinf(intersectAngle);

	return (sectorArea - triangleArea) * 2;
}