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
// - mettre pointeur la ou variable utilisé que dans scope (ex: creation voiture)
// - rendre cUser global si possible (rendre accessible pour inputController egalement)

void displayOptions(Menu menu);
static User cUser;

int main() {

	do {
		system("cls");
		displayOptions(connexionMenu);

	} while (!listenAndRedirect(connexionMenu, cUser));

	return 0;
}


int displayMenu() {
	
	do {
		system("cls");
		displayOptions(mainMenu);

	} while (!listenAndRedirect(mainMenu, cUser));

	return 0;
}

void displayOptions(Menu menu) {

	for (int i = 0; i < menu.optionList.size(); i++)
	{
		if (menu.optionList[i].type <= cUser.getType() && !menu.optionList[i].hide) {
			std::cout << menu.optionList[i].selection << " : " << menu.optionList[i].name << std::endl;
		}
	}
}

int carList() {
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
		std::cout << "------------------------------------------------------" << std::endl << std::endl;

		displayOptions(carListMenu);

	} while (!listenAndRedirect(carListMenu, cUser));

	return 0;
}

//creation voiture
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

	std::cout << "Annee : " << std::endl;
	getline(std::cin, input);
	std::stringstream(input) >> year;
	std::cout << std::endl << std::endl;

	std::cout << "Prix : " << std::endl;
	getline(std::cin, input);
	std::stringstream(input) >> price;
	std::cout << std::endl << std::endl;

	std::string query = "INSERT INTO CAR (modele, price, cyear) VALUES ('" + modele + "', '" + std::to_string(price) + "', '" + std::to_string(year) + "') ;";

	if (executeQuery(query) == SQLITE_OK) {
		std::cout << "Appuyer sur n'importe quelle touche pour continer...";
		std::cin.ignore();
	}

	return 0;
}

//suppression voiture
int carDelete() {
	std::string input;

	system("cls");
	std::cout << "------- Suppression d'une voiture -------" << std::endl << std::endl;

	std::cout << "Entrez l'identifiant de la voiture a supprimer : " << std::endl;
	getline(std::cin, input);
	std::cout << std::endl << std::endl;

	std::string query = "DELETE FROM CAR where id = " + input + ";";

	if (executeQuery(query) == SQLITE_OK) {
		std::cout << "Appuyer sur n'importe quelle touche pour continer...";
		std::cin.ignore();
	}

	return 0;
}


int checkAuth() {

	Records records;
	std::string username, password;
	int code = 0;
	std::string query = "SELECT username, password, type from user";
	records = selectQuery(query);

	do {
		system("cls");
		std::cout << "------- Connexion -------" << std::endl << std::endl;
		//affichage des erreurs
		if (code == 1) {
			std::cout << "Identifiant non reconnu" << std::endl << std::endl;
		}else if (code == 2) {
			std::cout << "Echec de l'authentification." << std::endl << std::endl;
		}

		std::cout << "Username : " << std::endl;
		std::cin >> username;

		
		for (auto& record : records) {
			int i = 0;
			for (int i = 0; i < record.size(); i++)
			{
				if (i == 0 && record[i] == username) {
					cUser.setUsername(record[i]);
					cUser.setPassword(record[i+1]);
					cUser.setType(std::stoi(record[i+2]));
				}
			}
		}

		if (cUser.getType() != 0) {
			code = 2;
			std::cout << "Password : " << std::endl;
			std::cin >> password;

			if (cUser.checkPassword(password)) {
				displayMenu();
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