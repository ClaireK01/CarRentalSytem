#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <exception>
#include "SqliteDatabase.h"


// TODO : 
// - finir mettre cUser en valeur static
// - finir option delete - visible sur la page, mode delete si selectionner (selection puis suppression)
// - enlever duplicata display options
// - ajout et suppresion des voitures
// - ajouter option deconnexion/retour 

class Car {
	private:
		std::string modele;
		double price;
		int year, uuid;

	public :
		static int id;

		//constructor
		Car(std::string m, double p, int y) : modele(m), price(p), year(y) {
			Car::id = Car::id + 1;
			uuid = id;
		}

		void set_year(int& y) {year = y;}

		void set_price(double& p) {price = p;}

		void set_modele(std::string& m) {modele = m;}

		int get_uuid() { return uuid; }

		void displayLine(int idx) {
			std::cout << "----------------------------------------------------------------------------------------" << std::endl;
			std::cout << "| " << idx << " | " << modele << "   /   " << price << " euros  /  " << year << "   " << std::endl;
		}
		//destructor
		~Car() {}
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

		static std::vector<User*> list;  // Du transformer en tableau de pointage plutot qu'objet pour eviter le crash...
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
void displayOptions(std::vector<std::string> array);
void displayMenuAdministration();
// les variable static doivent etre defini en dehors du code OU initiliser avec le keyword inline
std::vector<User*> User::list;
int Car::id = 0;
int User::id = 0;
static User cUser;
//Faire une valeur static currentUser

//int main() {
//	User u1 ("Admin", "admin", 1);
//	User u2 ("User", "user", 2);
//
//	User u = checkAuth();
//	displayMenu(u);
//
//	return 0;
//}

void list() {

	system("cls");
	std::cout << "Bonjour, Voici les modeles disponibles : " << std::endl << std::endl;
	int i = 1;

	if (cUser.getType() == 1) {
		std::cout << std::endl << std::endl;
		std::cout << "X / Supprimer un modèle";
		
	}
}

int displayMenu(User u) {
	std::string input;
	int choice;
	bool next = false;
	std::vector<std::string> options = { "Voir les voitures" };
	if (u.getType() == 1) {
		options.push_back("Administration");
	}

	do {
		//duplicata de code
		system("cls");
		displayOptions(options);
		std::getline(std::cin, input);
		std::stringstream(input) >> choice;

		if ((choice < options.size() || choice > options.size() || (choice == 2 && u.getType() == 2) ) && !(choice == 999 && u.getType() == 1) ) {
			std::cout << "Choix non valide.";
		} else {
			next = true;
		}
	} while (!next);


	if (choice == 1) {
		list();
	}else if (choice == 2) {
		displayMenuAdministration();
		/*std::cout << "Administration";*/
	}
	else if (choice == 999) {
		menu();
	}


	return 0;

}

void displayMenuAdministration() {
	std::string input;
	int choice;
	bool next = false;
	std::vector<std::string> options = { "Ajouter une voiture", "Supprimer une voiture" };

	do {
		system("cls");
		displayOptions(options);
		std::getline(std::cin, input);
		std::stringstream(input) >> choice;

		if (choice < options.size() || choice > options.size()) {
			std::cout << "Choix non valide.";
		}else {
			next = true;
		}
	} while (!next);


	if (choice == 1) {
		//lancer formulaire
	}else if(choice == 2) {
		list();
	}

}

void displayOptions(std::vector<std::string> array) {

	std::cout << "Bonjour !" << std::endl << std::endl;

	for (int i = 0; i < array.size(); i++)
	{
		std::cout << i + 1 << " : " << array[i] << std::endl;
	}

}

User checkAuth() {

	std::string username, password;
	User currentUser;
	int code = 0;

	do {
		system("cls");
		//affichage des erreurs
		if (code == 1) {
			std::cout << "Identifiant non reconnu" << std::endl << std::endl;
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

//creation d'une voiture
void carForm() {

	//std::string input;
	std::string modele;
	std::string year;
	std::string price;

	std::cout << "Nom du modèle : " << std::endl;
	getline(std::cin, modele);
	std::cout << std::endl << std::endl;

	std::cout << "Année : " << std::endl;
	std::cin >> year;
	getline(std::cin, price);
	std::cout << std::endl << std::endl;

	std::cout << "Prix : " << std::endl;
	getline(std::cin, year);
	std::cout << std::endl << std::endl;

	std::string query = "INSERT INTO car(modele, price, year) VALUES(" + modele + ", " + price + ", " + year + ");";

	executeQuery(query);

}