#include "Menu.h"
#include "Figures.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include<iostream>

int main() {
	// user interface controls
	bool isInsideWorkspace = false;
	bool isInsidePalette = false;
	bool wasKeyPressed = false;
	bool isMouseReleased = false;
	bool isDrawing = false;
	sf::Vector2f mousePosition;
	sf::Vector2f clickPosition;
	sf::Keyboard::Key key;
	sf::Texture texture;


	sf::RenderWindow window(sf::VideoMode(800, 650), "Paint", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	std::string filePath = "IOfile.png";
	Menu menu;
	Figures shapes(&window);
	
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		window.clear(sf::Color::Black);

		while (window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (!isDrawing) {
						wasKeyPressed = true;
						key = event.key.code;
						menu.setStyle(key);
						isMouseReleased = isInsideWorkspace = false;
					}
					break;
				case sf::Event::MouseButtonPressed: 
					if (event.mouseButton.button == sf::Mouse::Left) {
						clickPosition = sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y));
						isInsideWorkspace = menu.isInsideWorkspace(clickPosition);
						isInsidePalette = menu.isInsidePalette(clickPosition);
						if (isInsideWorkspace) isDrawing = true;
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) {
						isMouseReleased = true;
						isDrawing = false;
					}
					break;
				case sf::Event::MouseMoved:
					if(menu.isInsideWorkspace(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))))
						mousePosition = sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
					break;
			}
		}
		
		shapes.draw();

		if (wasKeyPressed) {
			if (isInsideWorkspace) {
				if (key == sf::Keyboard::L) {
					sf::VertexArray *line = new sf::VertexArray(sf::Lines, 2);
					(*line)[0] = sf::Vertex(clickPosition, menu.getDrawingColor());
					(*line)[1] = sf::Vertex(mousePosition, menu.getFillingColor());
					
					window.draw(*line);
					if (isMouseReleased)
						shapes.add(line);
					else delete line;
				} else if (key == sf::Keyboard::R) {
					sf::RectangleShape *rectangle = new sf::RectangleShape(mousePosition - clickPosition);
					rectangle->setPosition(clickPosition);
					rectangle->setFillColor(sf::Color::Transparent);
					rectangle->setOutlineColor(menu.getDrawingColor());
					rectangle->setOutlineThickness(1.0f);

					window.draw(*rectangle);
					if (isMouseReleased)
						shapes.add(rectangle);
					else delete rectangle;
				} else if (key == sf::Keyboard::A) {
					sf::RectangleShape *rectangle = new sf::RectangleShape(mousePosition - clickPosition);
					rectangle->setPosition(clickPosition);
					rectangle->setFillColor(menu.getFillingColor());
					rectangle->setOutlineColor(menu.getDrawingColor());
					rectangle->setOutlineThickness(1.0f);

					window.draw(*rectangle);
					if (isMouseReleased)
						shapes.add(rectangle);
					else delete rectangle;
				} else if (key == sf::Keyboard::C) {
					sf::CircleShape *circle = new sf::CircleShape();
					float radius = sqrt(pow(clickPosition.x - mousePosition.x, 2) + pow(clickPosition.y - mousePosition.y, 2));
					float rotationAngle = static_cast<float>(atan2(mousePosition.y - clickPosition.y, mousePosition.x - clickPosition.x) * (180 / M_PI) - 45);

					circle->setRadius(radius);
					circle->setPosition(clickPosition);
					circle->rotate(rotationAngle);
					circle->move(sf::Vector2f((radius - radius * sqrt(2)) * cos((rotationAngle + 45) * M_PI / 180),
						(radius - radius * sqrt(2)) * sin((rotationAngle + 45) * M_PI / 180)));
					circle->setOutlineColor(menu.getDrawingColor());
					circle->setOutlineThickness(1.0f);
					circle->setFillColor(menu.getFillingColor());
					
					window.draw(*circle);
					if (isMouseReleased)
						shapes.add(circle);
					else delete circle;
				}

				if (isMouseReleased)
					isMouseReleased = isInsideWorkspace = false;

			} else if (isInsidePalette) {
				if (key == sf::Keyboard::F) { 
					menu.setDrawingColor(menu.pickColor(clickPosition));
				} else if (key == sf::Keyboard::B) { 
					menu.setFillingColor(menu.pickColor(clickPosition));
				}
				isInsidePalette = false;
			}
		}

		window.draw(menu);
		window.display();


		if (wasKeyPressed) {
			if (key == sf::Keyboard::Escape) {
				window.close();
			}

			if (key == sf::Keyboard::Key::W) {
				shapes.saveToFile(filePath);	
				wasKeyPressed = false;
				menu.setStyle();
			}

			if (key == sf::Keyboard::Key::O) {
				shapes.loadFromFile(filePath, texture);
				wasKeyPressed = false;
				menu.setStyle();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && key == sf::Keyboard::Z) {
				shapes.remove();
				wasKeyPressed = false;
				menu.setStyle();
			}
		}
	}
	return 0;
}