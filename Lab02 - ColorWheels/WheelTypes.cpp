#include "WheelTypes.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

/////////////////////////////////// RGB ///////////////////////////////////

RGB::RGB(double radius) : ColorWheel(radius) {
	_text.setPosition(radius / 2 + 15, 2 * radius + 20);
	_text.setString("RGB B = " + std::to_string(static_cast<int>(_parameter * 255)));
	makeWheel();
	_sprite->setTexture(*_texture);
}

sf::Color RGB::convertColor(double angle, double r) const {
	return sf::Color(255.0 * r / _radius, (angle / (2 * M_PI)) * 255, _parameter * 255);
}

void RGB::updateWheel(double parameter) {
	if (fabs(_parameter - parameter) > 0.01) {
		_parameter = parameter;
		_text.setString("RGB B = " + std::to_string(static_cast<int>(_parameter * 255)));
		makeWheel();
	}
}

/////////////////////////////////// CMY ///////////////////////////////////

CMY::CMY(double radius) : ColorWheel(radius) {
	_text.setPosition(radius / 2 + 15, 2 * radius + 20);
	_text.setString("CMY Y = " + std::to_string(static_cast<int>(_parameter * 100)) + "%");
	makeWheel();
	_sprite->setTexture(*_texture);
}

sf::Color CMY::convertColor(double angle, double r) const {
	return sf::Color(255.0 - 255.0 * (r / _radius), 255.0 - 255.0 * (angle / (2 * M_PI)), 255.0 - 255.0 * _parameter);
}

void CMY::updateWheel(double parameter) {
	if (fabs(_parameter - parameter) > 0.01) {
		_parameter = parameter;
		_text.setString("CMY Y = " + std::to_string(static_cast<int>(_parameter * 100)) + "%");
		makeWheel();
	}
}

/////////////////////////////////// HSV ///////////////////////////////////

HSV::HSV(double radius) : ColorWheel(radius) {
	_text.setPosition(radius / 2, 2 * radius + 20);
	_text.setString("HSV V = " + std::to_string(_parameter).substr(0, 5));
	makeWheel();
	_sprite->setTexture(*_texture);
}

sf::Color HSV::convertColor(const double angle, const double radius) const {
	double s = radius / _radius;
	double c = _parameter * s;
	double x = c * (1 - fabs(fmod(angle * 3 / M_PI, 2) - 1));
	double m = _parameter - c;

	double r, g, b;
	if (angle <= M_PI / 3) {
		r = c; g = x; b = 0;
	} else if (angle <= 2 * M_PI / 3) {
		r = x; g = c; b = 0;
	} else if (angle <= M_PI) {
		r = 0; g = c; b = x;
	} else if (angle <= 4 * M_PI / 3) {
		r = 0; g = x; b = c;
	} else if (angle <= 5 * M_PI / 3) {
		r = x; g = 0; b = c;
	} else if (angle <= 2 * M_PI) {
		r = c; g = 0; b = x;
	}

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

void HSV::updateWheel(double parameter) {
	if (fabs(_parameter - parameter) > 0.01) {
		_parameter = parameter;
		_text.setString("HSV V = " + std::to_string(_parameter).substr(0, 5));
		makeWheel();
	}
}

/////////////////////////////////// HSL ///////////////////////////////////

HSL::HSL(double radius) : ColorWheel(radius) {
	_text.setPosition(radius / 2, 2 * radius + 20);
	_text.setString("HSL L = " + std::to_string(_parameter).substr(0, 5));
	makeWheel();
	_sprite->setTexture(*_texture);
}

sf::Color HSL::convertColor(double angle, double radius) const {
	double s = radius / _radius;
	double c = (1 - fabs(2 * _parameter - 1)) * s;

	double x = c * (1 - fabs(fmod(angle * 3 / M_PI, 2) - 1));
	double m = _parameter - c / 2;

	double r, g, b;
	if (angle <= M_PI / 3) {
		r = c; g = x; b = 0;
	} else if (angle <= 2 * M_PI / 3) {
		r = x; g = c; b = 0;
	} else if (angle <= M_PI) {
		r = 0; g = c; b = x;
	} else if (angle <= 4 * M_PI / 3) {
		r = 0; g = x; b = c;
	} else if (angle <= 5 * M_PI / 3) {
		r = x; g = 0; b = c;
	} else if (angle <= 2 * M_PI) {
		r = c; g = 0; b = x;
	} else r = g = b = -255;

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

void HSL::updateWheel(double parameter) {
	if (fabs(_parameter - parameter) > 0.01) {
		_parameter = parameter;
		_text.setString("HSL L = " + std::to_string(_parameter).substr(0, 5));
		makeWheel();
	}
}