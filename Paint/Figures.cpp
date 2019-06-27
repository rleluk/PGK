#include "Figures.h"
#include <vector>


Figures::Figures(sf::RenderWindow *sourceWindow) : window(sourceWindow) {}

Figures::~Figures() {
	deleteData();
}

void Figures::add(sf::Drawable *figure) {
	data.push_back(figure);
}

void Figures::draw() {
	for (auto &shape : data)
		window->draw(*shape);
}

void Figures::deleteData() {
	for (auto &shape : data)
		delete shape;
	data.clear();
}

void Figures::saveToFile(std::string filePath) {
	sf::Texture texture;
	texture.create(window->getSize().x, window->getSize().y);
	texture.update(*window);
	sf::Image image;
	image.create(796, 536);
	image.copy(texture.copyToImage(), 0, 0, sf::IntRect(2, 62, 796, 536));
	image.saveToFile(filePath);
}

void Figures::loadFromFile(std::string filePath, sf::Texture &texture) {
	sf::Image imageFromFile;
	if (!imageFromFile.loadFromFile(filePath)) return;
	deleteData();
	texture.loadFromImage(imageFromFile);
	sf::Sprite *background = new sf::Sprite(texture);
	background->setPosition(sf::Vector2f(2, 62));
	data.push_back(background);
}

void Figures::remove() {
	if (!data.empty()) {
		sf::Drawable *obj = data.back();
		delete obj;
		data.pop_back();
	}
}