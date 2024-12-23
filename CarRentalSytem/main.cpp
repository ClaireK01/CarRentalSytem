#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <exception>


// TODO : 
// - page de login
// - page de list
// - ajout et suppresion des voitures

class Car {
	private:
		std::string modele;
		double price;
		int year, uuid;

	public :
		static std::vector<Car> list;
		static int id;

		//constructor
		Car(std::string& a, double& b, int& c) : modele(a), price(b), year(c) {
			Car::list.push_back(*this);
			Car::id = Car::id + 1;
			uuid = id;
		}


		//copy assignment
		Car& operator=(Car other)
		{
			Car::list.push_back(*this);
			Car::id++;
			other.uuid = id;
			return *this;
		}

		void set_year(int& y) {year = y;}

		void set_price(double& p) {price = p;}

		void set_modele(std::string& m) {modele = m;}

		int get_uuid() { return uuid; }

		void displayLine(int idx) {
			std::cout << "----------------------------------------------------------------------------------------" << std::endl;
			std::cout << "| " << idx << " | " << modele << "   /   " << price << "€  /  " << year << "   " << std::endl;
		}
		//destructor
		~Car() {
			for (int i = 0; i < Car::list.size(); i++) {
				if (Car::list[i].get_uuid() == get_uuid()) {
					Car::list.erase(Car::list.begin() + i); //voir utilisation std::find()
					break; 
				}
			}
		}
};

class User {
	
	private:
		std::string username, password;
		int uuid = 0;
		int type = 0;
		bool connected = false;

	public:
		//constructor
		User() = default;
		User(std::string u, std::string p, int t) : username(u), password(p), type(t) {
			User::list.push_back(this);
			User::id++;
			uuid = id;
		};

		//copy assignment
		User& operator= (User other){ 
			username = other.username;
			password = other.password;
			uuid = other.uuid;
			type = other.type;
			connected = other.connected;
			return *this; 
		}
		static std::vector<User*> list;  // Du le transformer en tableau de pointage plutot qu'objet pour eviter le crash...
		static int id;
		bool checkPassword(std::string input) { return input == password; }
		int get_uuid() { return uuid; }
		std::string getUsername() { return username; }
		int isConnected() { return connected; }
		void setConnected(bool& c) { connected = c; }
		int getType() { return type; }
		void reset() {
			username = "";
			password = "";
			uuid = -1;
			type = 0;
			connected = false;
		}


		//destructor
		~User() {
			for (int i = 0; i < User::list.size(); i++) {
				if ( (*User::list[i]).get_uuid() == get_uuid()) {
					User::list.erase(User::list.begin() + i); //voir utilisation std::find()
					break;
				}
			}
		}
};


// attention a ne pas le mettre dans le header
User checkAuth();
int displayMenu(User u);
void list();
// les variable static doivent etre defini en dehors du code OU initiliser avec le keyword inline
std::vector<User*> User::list;
std::vector<Car> Car::list;
int Car::id = 0;
int User::id = 0;

int main() {
	User u1 ("Admin", "admin", 1);
	User u2 ("User", "user", 2);
	User u = checkAuth();
	int choice;

	choice = displayMenu(u);

	if (choice == 1) {
		//list();
		std::cout << "list";
	} else if (choice == 2) {
		std::cout << "Administration";
	}

	return 0;
}

void list() {
	system("cls");
	std::cout << "Bonjour, Voici les modèles disponibles : " << std::endl << std::endl;
	int i = 0;
	for (Car c : Car::list) {
		c.displayLine(i);
		i++;
	}
}

int displayMenu(User u) {
	std::string input;
	int choice;
	bool next = false;

	std::cout << "Bonjour !" << std::endl;

	do {
		system("cls");
		std::cout << "1 : Voir les voitures disponibles " << std::endl;
		if (u.getType() == 1) {
			std::cout << "2 : Admin" << std::endl;
		}

		std::getline(std::cin, input);
		std::stringstream(input) >> choice;

		if (choice != 1 && (choice != 2 || (choice == 2 && u.getType() == 2))) {
			std::cout << "Choix non valide.";
		}
		else {
			next = true;
		}
	} while (!next);


	return choice;

}

User checkAuth() {

	std::string username, password;
	User currentUser;
	int code = 0;

	do {
		system("cls");
		//affichage des erreurs
		if (code == 1) {
			std::cout << "Identifiant non reconnu" << std::endl;
		}else if (code == 2) {
			std::cout << "Echec de l'authentification." << std::endl << std::endl;
		}

		std::cout << "Username : " << std::endl;
		std::cin >> username;

		for (User * u : User::list) {
			if ((*u).getUsername() == username) {
				currentUser = *u;
			}
		}

		if (currentUser.getType() != 0) {
			code = 2;
			std::cout << "Password : " << std::endl;
			std::cin >> password;

			if (currentUser.checkPassword(password)) {
				code = 3;
			}else {
				currentUser.reset();
			}
		} else {
			code = 1;
		}

	} while (code != 3);


		return currentUser;
}