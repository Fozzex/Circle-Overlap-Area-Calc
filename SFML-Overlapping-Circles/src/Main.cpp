#include <SFML/Graphics.hpp>
#include <iostream>

#include "DraggableCircle.h"
#include "imgui.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"
#include "ImGui/imgui-SFML.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Overlapping Circles", sf::Style::Close, settings);
	ImGui::SFML::Init(window);

	DraggableCircle circle(150.0f);

	circle.setPosition(0.0f, 0.0f);
	circle.setFillColor({ 0, 0, 0, 0 });
	circle.setOutlineColor({ 255, 0, 0, 255 });
	circle.setOutlineThickness(5.0f);

	DraggableCircle circle2(150.0f);

	circle2.setPosition(0.0f, 0.0f);
	circle2.setFillColor({ 0, 0, 0, 0 });
	circle2.setOutlineColor({ 0, 255, 0, 255 });
	circle2.setOutlineThickness(5.0f);

	sf::Clock deltaClock;
	bool isMenuOpen = true;

	float circle1Colour[3] = { circle.getOutlineColor().r / 255.f, circle.getOutlineColor().g / 255.f, circle.getOutlineColor().b / 255.f };
	float circle2Colour[3] = { circle2.getOutlineColor().r / 255.f, circle2.getOutlineColor().g / 255.f, circle2.getOutlineColor().b / 255.f };

	int currTab = 0;

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (ImGui::SFML::ProcessEvent(evnt))
				continue;

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					isMenuOpen = !isMenuOpen;
			}

			if (!circle.ParseEvent(evnt))
			{
				circle2.ParseEvent(evnt);
			}
		
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		if (isMenuOpen)
		{
			ImGui::SetNextWindowSize(ImVec2(540, 200), ImGuiCond_FirstUseEver);
			ImGui::Begin("Information", &isMenuOpen);
			ImGui::Columns(2);

			ImGui::BeginChild("Left", ImVec2(0, 100));
			ImGui::Text("Circle 1");
			if (ImGui::ColorEdit3("Colour", circle1Colour))
			{
				circle.setOutlineColor({
					static_cast<sf::Uint8>(circle1Colour[0] * 255),
					static_cast<sf::Uint8>(circle1Colour[1] * 255),
					static_cast<sf::Uint8>(circle1Colour[2] * 255),
					255
					});
			}

			ImGui::BulletText("Centre position: (%i, %i)", (int)circle.GetCentre().x, (int)circle.GetCentre().y);
			ImGui::BulletText("Area: %.2f", circle.GetArea());
			ImGui::EndChild();

			ImGui::NextColumn();
			ImGui::BeginChild("Right", ImVec2(0, 100));
			ImGui::Text("Circle 2");
			if (ImGui::ColorEdit3("Colour", circle2Colour))
			{
				circle2.setOutlineColor({
					static_cast<sf::Uint8>(circle2Colour[0] * 255),
					static_cast<sf::Uint8>(circle2Colour[1] * 255),
					static_cast<sf::Uint8>(circle2Colour[2] * 255),
					255
					});
			}

			ImGui::BulletText("Centre position: (%i, %i)", (int)circle2.GetCentre().x, (int)circle2.GetCentre().y);
			ImGui::BulletText("Area: %.2f", circle2.GetArea());


			ImGui::EndChild();
			ImGui::Columns(1);

			ImGui::Separator();
			ImGui::Text("Overlap Area: %f", circle.GetOverlapArea(circle2));
			ImGui::Separator();

			ImGui::End();
		}

		window.clear();

		window.draw(circle2);
		window.draw(circle);

		ImGui::SFML::Render(window);
		window.display();
	}
}