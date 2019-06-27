#pragma once
#include <SFML/Graphics.hpp>

class Slider final : public sf::Drawable, public sf::Transformable {
	public:
		Slider();
		~Slider();
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void updatePosition(sf::Vector2f vec);
		double getParameter() const {
			return _parameter;
		}

	private:
		unsigned width = 40, height = 300;
		double _parameter = 0.51;
		sf::Texture *_texture;
		sf::Sprite *_sprite;
		sf::VertexArray _line;
};

