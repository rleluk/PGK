#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Figures {
	public:
		Figures(sf::RenderWindow *sourceWindow);
		~Figures();
		void add(sf::Drawable *figure);
		void draw();
		void deleteData();
		void saveToFile(std::string filePath);
		void loadFromFile(std::string filePath, sf::Texture &texture);
		void remove();

	private:
		sf::RenderWindow *window;
		std::vector<sf::Drawable *> data;
};

