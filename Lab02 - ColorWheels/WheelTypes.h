#pragma once
#include "ColorWheel.h"

class RGB final : public ColorWheel {
	public:
		explicit RGB(double radius);
		~RGB() = default;
		virtual sf::Color convertColor(double angle, double r) const override;
		void updateWheel(double parametr);
};

class CMY final : public ColorWheel {
	public:
		explicit CMY(double radius);
		~CMY() = default;
		virtual sf::Color convertColor(double angle, double r) const override;
		void updateWheel(double parametr);
};

class HSV final : public ColorWheel {
	public:
		explicit HSV(double radius);
		~HSV() = default;
		virtual sf::Color convertColor(double angle, double r) const override;
		void updateWheel(double parametr);
};

class HSL final : public ColorWheel {
	public:
		explicit HSL(double radius);
		~HSL() = default;
		virtual sf::Color convertColor(double angle, double r) const override;
		void updateWheel(double parametr);
};
