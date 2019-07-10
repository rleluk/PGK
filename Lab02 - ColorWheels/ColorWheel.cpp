#include "ColorWheel.h"
#include "font.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

ColorWheel::ColorWheel(double radius) : _radius(radius) {
	_colors = new sf::Uint8[16 * _radius * _radius];
	_sprite = new sf::Sprite;
	_texture = new sf::Texture;
	_font.loadFromMemory(font_data, font_data_size);
	_text.setFont(_font);
	_text.setCharacterSize(14);
	_text.setFillColor(sf::Color::Black);
	_text.setStyle(sf::Text::Regular);
	_text.setPosition(0.f, 0.f);
	_texture->create(2. * radius, 2. * radius);
}

ColorWheel::~ColorWheel() {
	delete _texture;
	delete _sprite;
	delete[] _colors;
}

void ColorWheel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*_sprite, states);
	target.draw(_text, states);
}

void ColorWheel::makeWheel() {
	unsigned diameter = _radius * 2;
	for (int x = 0; x < diameter; x++) {
		for (int y = 0; y < diameter; y++) {
			double _x = x - static_cast<int>(_radius);
			double _y = static_cast<int>(_radius) - y;
			double angle = atan2(_y, _x);
			if (angle < 0.)
				angle = 2 * M_PI + fmod(angle, 2 * M_PI);
			double r = sqrt(_x * _x + _y * _y);
			sf::Color color = convertColor(angle, r);
			if (r <= _radius) {
				_colors[4 * (y * 2 * _radius + x) + 0] = color.r;
				_colors[4 * (y * 2 * _radius + x) + 1] = color.g;
				_colors[4 * (y * 2 * _radius + x) + 2] = color.b;
				_colors[4 * (y * 2 * _radius + x) + 3] = 255;
			}
			else
				for (int i{}; i < 4; ++i)
					_colors[4 * (y * 2 * _radius + x) + i] = 0;
		}
		_texture->update(_colors);
	}
}