#pragma once
#include <string>

class Car
{
	private:
		std::string modele;
		double price;
		int year, uuid;

	public:
		Car(std::string m, double p, int y) : modele(m), price(p), year(y) {
			Car::id = Car::id + 1;
			uuid = id;
		};
		static int id;
		int get_uuid() { return uuid; }
		void set_year(int& y) { year = y; }
		void set_price(double& p) { price = p; }
		void set_modele(std::string& m) { modele = m; }
		void displayLine(int idx) {
			std::cout << "----------------------------------------------------------------------------------------" << std::endl;
			std::cout << "| " << idx << " | " << modele << "   /   " << price << " euros  /  " << year << "   " << std::endl;
		}
		~Car() {}

};

