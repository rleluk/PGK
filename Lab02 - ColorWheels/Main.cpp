#include <SFML/Graphics.hpp>
#include "WheelTypes.h"
#include "Slider.h"
#include <iostream>	

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "Color wheels", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	unsigned R = 120;

	Slider slider;
	slider.setPosition(5 * R + 90, 175);
	HSL hsl(R);
	hsl.setPosition(60, 40);
	HSV hsv(R);
	hsv.setPosition(3 * R, 40);
	CMY cmy(R);
	cmy.setPosition(60, 3 * R);
	RGB rgb(R);
	rgb.setPosition(3 * R , 3 * R);
	sf::Font font = hsl.getFont();
	sf::Text fps;
	fps.setPosition(5 * R + 90, 50);
	fps.setFont(font);
	fps.setCharacterSize(14);
	fps.setStyle(sf::Text::Bold);
	fps.setFillColor(sf::Color::Black);

	double currentParameter;
	bool isButtonPressed = false;

	unsigned int FPS = 0, frame_counter = 0;
	sf::Time time = sf::Time::Zero;
	clock.restart().asMilliseconds();

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				isButtonPressed = true;
				slider.updatePosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				break;
			case sf::Event::MouseMoved:
				if(isButtonPressed)
					slider.updatePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				break;
			case sf::Event::MouseButtonReleased:
				isButtonPressed = false;
			}
		}

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = static_cast<unsigned> ((static_cast<double>(frame_counter) / clock.getElapsedTime().asSeconds()));
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;
		fps.setString("FPS: " + std::to_string(FPS));

		currentParameter = slider.getParameter();
		hsv.updateWheel(currentParameter);
		hsl.updateWheel(currentParameter);	
		cmy.updateWheel(currentParameter);
		rgb.updateWheel(currentParameter);
		window.draw(fps);
		window.draw(slider);
		window.draw(hsl);
		window.draw(hsv);
		window.draw(cmy);
		window.draw(rgb);
		window.display();
	}
}