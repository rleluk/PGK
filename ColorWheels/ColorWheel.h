#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ColorWheel : public sf::Drawable, public sf::Transformable {
	public:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		sf::Font getFont() {
			return _font;
		}

	protected:
		unsigned _radius;
		sf::Uint8 *_colors;
		sf::Texture *_texture;
		sf::Sprite *_sprite;
		sf::Font _font;
		sf::Text _text;
		double _parameter = .51;

		explicit ColorWheel(double radius);
		virtual ~ColorWheel();
		void makeWheel();
		virtual sf::Color convertColor(double angle, double r) const = 0;
};





