#pragma once
#include <string>

class Car
{
	private:
		std::string modele;
		double price;
		int year;

	public:
		Car(std::string m, double p, int y) : modele(m), price(p), year(y) {};
		void set_year(int& y) { year = y; }
		void set_price(double& p) { price = p; }
		void set_modele(std::string& m) { modele = m; }
		~Car() {}

};

