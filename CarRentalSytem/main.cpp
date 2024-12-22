#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Shop {

	public :
		std::vector<Car> cars = {};

		void list() {
			std::cout << "Bonjour, Voici les modèle disponible : " << std::endl;
			for (Car c : cars) {
				c.displayLine();
			}
		}

		void addCar(Car car) {
			cars.push_back(car);
		}

		void removeCar(Car car) {
			for (int i = 0; i < cars.size(); i++) {
				if (cars[i].get_uuid() == car.get_uuid()) { //override le == operator
					cars.erase(cars.begin() + i);
					delete &car;
				}
			}
		}
};

class Car {

	Car(std::string& a, double& b, int& c, int& d) : modele(a), price(b), year(c), uuid(d) {}

	private:
		std::string modele;
		double price;
		int year, uuid;

	public :
		void set_year(int& y) {
			year = y;
		}

		void set_price(double& p) {
			price = p;
		}

		void set_modele(std::string& m) {
			modele = m;
		}

		int get_uuid() {
			return uuid;
		}

		void displayLine() {
			std::cout << "-----------------------------------------------------------------" <<std::endl;
			std::cout << "|   " << modele << "   |   " << price << "€  |  " << year << "   |" << std::endl;
		}
};

class User {

	User(std::string u, std::string p) : username(u), password(p) {};

	private:
		std::string username, password;
	public:
		bool checkPassword(std::string input) { return input == password; }
};

int main() {


	return 0;
}