#include "Draggable.h"

Draggable::Draggable()
{
}

Draggable::Draggable(sf::Shape* base) :
	m_Base(base)
{
}

bool Draggable::ParseEvent(const sf::Event& e)
{
	if (m_Base == nullptr)
		return false;

	sf::Vector2f basePosition(m_Base->getPosition());
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:

		if (e.mouseButton.button != sf::Mouse::Left)
			return false;

		if (this->ContainsPoint(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y)))
		{
			m_Dragging = true;
			m_DragOffset = { e.mouseButton.x - basePosition.x, e.mouseButton.y - basePosition.y };

			return true;
		}
		break;

	case sf::Event::MouseButtonReleased:

		if (e.mouseButton.button != sf::Mouse::Left || !m_Dragging)
			return false;

		if (this->ContainsPoint(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y)))
		{
			m_Dragging = false;
			return true;
		}
		break;

	case sf::Event::MouseMoved:

		if (m_Dragging)
		{
			m_Base->setPosition(e.mouseMove.x - m_DragOffset.x, e.mouseMove.y - m_DragOffset.y);
			return true;
		}
		break;
	}

	return false;
}

sf::Vector2f Draggable::GetCentre() const
{
	if (m_Base == nullptr)
		return sf::Vector2f();

	sf::FloatRect bounds = m_Base->getGlobalBounds();
	return sf::Vector2f( bounds.left + (bounds.width / 2.0f), bounds.top + (bounds.height / 2.0f) );
}

bool Draggable::ContainsPoint(const sf::Vector2f& point) const
{
	if (m_Base == nullptr)
		return false;

	return m_Base->getGlobalBounds().contains(point);
}