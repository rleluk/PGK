#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Menu : public sf::Drawable {
	public:
		~Menu();
		Menu();
		void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const;
		void outtextxy(sf::RenderTarget& target, float x, float y, std::string str) const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool isInsidePalette(sf::Vector2f position) const;
		bool isInsideWorkspace(sf::Vector2f position) const;
		void setStyle(sf::Keyboard::Key key);
		void setStyle();
		void setFillingColor(sf::Color color);
		void setDrawingColor(sf::Color color);
		sf::Color pickColor(sf::Vector2f &mousePosition);
		sf::Color getFillingColor();
		sf::Color getDrawingColor();

	private:
		std::string lastStyle;
		sf::Color currentDrawingColor;
		sf::Color currentFillingColor;
		sf::RectangleShape *blockWithDrawingColor;
		sf::RectangleShape *blockWithFillingColor;
		sf::Font font;
		sf::Text *text;
		sf::RectangleShape *workspaceFrame;
		sf::Texture *colors_texture;
		sf::Uint8 *colors_pixels;
		sf::Sprite *palette;
		const unsigned int colors_size_x = 765;
		const unsigned int colors_size_y = 60;
		inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
			colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
			colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
			colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
			colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
		}
};


