#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <exception>
#include <sqlite3.h>
#include <map>
#include "SqliteDatabase.h"
#include "InputController.h"
#include "App.h"
#include "User.h"


// TODO : 
// - ajout et suppresion des voitures
// - ajouter option deconnexion/retour 
// - mettre pointeur la ou variable utilisé que dans scope (ex: creation voiture)
// - ajouter quitter a main menu
// - validation choix en fonction du type de compte

void displayOptions(Menu menu);
int User::id = 0;
static User cUser;
std::vector<User*> User::list;


int main() {
	User u1 ("Admin", "admin", 2);
	User u2 ("User", "user", 1);

	if (checkAuth() == 0) {
		displayMenu();
	};

	return 0;
}


int displayMenu() {
	bool next = false;

	do {
		system("cls");
		displayOptions(mainMenu);

	} while (!listenAndRedirect(mainMenu));

	return 0;
}

void displayOptions(Menu menu) {

	for (int i = 0; i < menu.optionList.size(); i++)
	{
		if (menu.optionList[i].type <= cUser.getType()) {
			std::cout << menu.optionList[i].selection << " : " << menu.optionList[i].name << std::endl;
		}
	}
}

int carList() {

	bool ret;
	bool next = false;

	do {
		system("cls");
		std::cout << "Bonjour, Voici les modeles disponibles : " << std::endl << std::endl;
		std::string query = "SELECT * FROM car;";
		Records records = selectQuery(query);

		for (auto& record : records) {
			int i = 0;
			std::cout << "------------------------------------------------------" << std::endl;
			for (auto& line : record) {
				std::cout << line << (i + 1 < record.size() ? ", " : "");
				i++;
			}
			std::cout << std::endl;
		}

		displayOptions(carListMenu);

	} while (!listenAndRedirect(carListMenu));

	return 0;

}

//creation d'une voiture
int carForm() {

	system("cls");
	std::cout << "------- Creation d'une voiture -------" << std::endl << std::endl;
	std::string input;
	std::string modele;
	int year;
	float price;

	std::cout << "Nom du modele : " << std::endl;
	getline(std::cin, modele);
	std::cout << std::endl << std::endl;

	std::cout << "Année : " << std::endl;
	getline(std::cin, input);
	std::stringstream(input) >> year;
	std::cout << std::endl << std::endl;

	std::cout << "Prix : " << std::endl;
	getline(std::cin, input);
	std::stringstream(input) >> price;
	std::cout << std::endl << std::endl;

	std::string query = "INSERT INTO CAR (modele, price, cyear) VALUES ('" + modele + "', '" + std::to_string(price) + "', '" + std::to_string(year) + "') ;";

	return executeQuery(query);
}


int checkAuth() {

	std::string username, password;
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
				cUser = *u;
			}
		}

		if (cUser.getType() != 0) {
			code = 2;
			std::cout << "Password : " << std::endl;
			std::cin >> password;

			if (cUser.checkPassword(password)) {
				code = 3;
			}else {
				cUser.reset();
			}
		} else {
			code = 1;
		}

	} while (code != 3);

	return 0;

}