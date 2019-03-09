#pragma once
#include <SFML/Graphics.hpp>

class Draggable
{
public:

	Draggable();
	Draggable(sf::Shape* base);

	bool ParseEvent(const sf::Event& e);
	sf::Vector2f GetCentre() const;

	inline void SetBase(sf::Shape* base) { m_Base = base; }

protected:

	virtual bool ContainsPoint(const sf::Vector2f& point) const;

private:

	sf::Shape* m_Base;
	bool m_Dragging = false;
	sf::Vector2f m_DragOffset;

};