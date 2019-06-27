#include "Menu.h"
#include "font.h"
#include <iostream>
Menu::Menu() : currentDrawingColor(sf::Color::Black), currentFillingColor(sf::Color::Transparent), lastStyle("None") {
	font.loadFromMemory(font_data, font_data_size);
	text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);

	workspaceFrame = new sf::RectangleShape(sf::Vector2f(796, 536));
	workspaceFrame->setFillColor(sf::Color::Transparent);
	workspaceFrame->setOutlineColor(sf::Color::White);
	workspaceFrame->setOutlineThickness(1.0f);
	workspaceFrame->setPosition(2, 62);

	unsigned int x, y;
	colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
	for (x = 0; x < 255; x++)
		for (y = 0; y < 30; y++)
		{
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	colors_texture = new sf::Texture();
	colors_texture->create(colors_size_x, colors_size_y);
	colors_texture->update(colors_pixels);

	palette = new sf::Sprite();
	palette->setTexture(*colors_texture);
	palette->setPosition(1, 1);

	blockWithDrawingColor = new sf::RectangleShape(sf::Vector2f(95., 30.));
	blockWithFillingColor = new sf::RectangleShape(sf::Vector2f(95., 30.));
	blockWithDrawingColor->setPosition(colors_size_x + 2, 1);
	blockWithFillingColor->setPosition(colors_size_x + 2, 31);
	blockWithDrawingColor->setFillColor(currentDrawingColor);
	blockWithFillingColor->setFillColor(currentFillingColor);
}

Menu::~Menu() {
	delete blockWithDrawingColor;
	delete blockWithFillingColor;
	delete text;
	delete workspaceFrame;
	delete colors_texture;
	delete colors_pixels;
	delete palette;
}

sf::Color Menu::pickColor(sf::Vector2f &position) {
	int x = static_cast<int>(position.x);
	int y = static_cast<int>(position.y);
	return sf::Color(colors_pixels[4 * (y * colors_size_x + x) + 0],
					 colors_pixels[4 * (y * colors_size_x + x) + 1],
					 colors_pixels[4 * (y * colors_size_x + x) + 2]);
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const {
	text->setPosition(x, y);
	text->setString(str);
	target.draw(*text);
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, std::string str) const {
	text->setPosition(x, y);
	text->setString(str);
	target.draw(*text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const { 
	outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
	outtextxy(target, 5, 615, L"b - wybór koloru wypełniania");
	outtextxy(target, 5, 630, L"l - rysowanie linii");

	outtextxy(target, 200, 600, L"r - rysowanie prostokąta");
	outtextxy(target, 200, 615, L"a - rysowanie wypełnionego prostokąta");
	outtextxy(target, 200, 630, L"c - rysowanie okręgu");

	outtextxy(target, 470, 600, L"w - zapis do pliku");
	outtextxy(target, 470, 615, L"o - odczyt z pliku");
	outtextxy(target, 470, 630, L"esc - wyjście");

	outtextxy(target, 650, 600, L"ctrl + z - cofnij");
	outtextxy(target, 650, 615, L"Aktualne:");
	outtextxy(target, 715, 615, lastStyle);

	blockWithDrawingColor->setFillColor(currentDrawingColor);
	blockWithFillingColor->setFillColor(currentFillingColor);

	target.draw(*workspaceFrame);
	target.draw(*palette);

	target.draw(*blockWithDrawingColor);
	target.draw(*blockWithFillingColor);
}

bool Menu::isInsidePalette(sf::Vector2f position) const {
	if (position.x > 764 || position.y  > 59) return false;
	return true;			
}

bool Menu::isInsideWorkspace(sf::Vector2f position) const {
	if (position.x < 2 || position.x > 798 || position.y < 63 || position.y > 598) return false;
	return true;
}

sf::Color Menu::getFillingColor() {
	return currentFillingColor;
}

sf::Color Menu::getDrawingColor() {
	return currentDrawingColor;
}

void Menu::setStyle() {
	lastStyle = "";
}

void Menu::setStyle(sf::Keyboard::Key key) {
	switch (key) {
		case sf::Keyboard::F :
			lastStyle = "f";
			break;
		case sf::Keyboard::B:
			lastStyle = "b";
			break;
		case sf::Keyboard::L:
			lastStyle = "l";
			break;
		case sf::Keyboard::R:
			lastStyle = "r";
			break;
		case sf::Keyboard::A:
			lastStyle = "a";
			break;
		case sf::Keyboard::C:
			lastStyle = "c";
			break;
		case sf::Keyboard::W:
			lastStyle = "w";
			break;
		case sf::Keyboard::O:
			lastStyle = "o";
			break;
	}
}

void Menu::setFillingColor(sf::Color color) {
	currentFillingColor = color;
}

void Menu::setDrawingColor(sf::Color color) {
	currentDrawingColor = color;
}