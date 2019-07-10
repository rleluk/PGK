#include "Slider.h"

Slider::Slider() : _line(sf::Lines, 2) {
	_texture = new sf::Texture;
	_sprite = new sf::Sprite;
	_texture->create(width, height);
	sf::Uint8 *colors = new sf::Uint8[4 * width * height];
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			if (x == 0 || y == 0 || x == width - 1|| y == height - 1) {
				colors[4 * (y * width + x) + 0] = sf::Color::Black.r;
				colors[4 * (y * width + x) + 2] = sf::Color::Black.b;
				colors[4 * (y * width + x) + 1] = sf::Color::Black.g;
				colors[4 * (y * width + x) + 3] = 200;
			}
			else {
				colors[4 * (y * width + x) + 0] = y * 255 / height;
				colors[4 * (y * width + x) + 1] = y * 255 / height;
				colors[4 * (y * width + x) + 2] = y * 255 / height;
				colors[4 * (y * width + x) + 3] = 200;
			}
		}
	}
	_texture->update(colors);
	_line[0] = sf::Vertex(sf::Vector2f(-3, height / 2), sf::Color::Black);
	_line[1] = sf::Vertex(sf::Vector2f(width + 3, height	 / 2), sf::Color::Black);
	_sprite->setTexture(*_texture);
	delete[] colors;
}

Slider::~Slider() {
	delete _texture;
	delete _sprite;
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*_sprite, states);
	target.draw(_line, states);
}

void Slider::updatePosition(sf::Vector2f vec) {
	const sf::Vector2f sliderPosition = getPosition();

	if ((sliderPosition.x <= vec.x && sliderPosition.x + width >= vec.x)
		&& (sliderPosition.y <= vec.y && sliderPosition.y + height >= vec.y)) {

		_line[0].position.y = _line[1].position.y = vec.y - sliderPosition.y;
		_parameter = (vec.y - sliderPosition.y) / (static_cast<double>(height));
		if (_parameter > 0.99) _parameter = 1.0;
		else if (_parameter < 0.01) _parameter = 0.0;
	}
}