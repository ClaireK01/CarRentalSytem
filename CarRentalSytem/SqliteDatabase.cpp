#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include <Windows.h>
#include "SqliteDatabase.h"


//int main() {
//
//	menu();
//
//	return 0;
//}

int menu() {

	std::vector < std::string> opt = { "Create database : (" + static_cast<std::string>(dbname) + ")" , "Insert, update or delete", "Select from database", "Quit" };
	int choice;
	bool quit = false;
	sqlite3* DB;

	do {
		system("cls");
		std::cout << "----------- Gestion DB -----------" << std::endl << std::endl;
		std::cout << "Hi ! What do you want to do ? " << std::endl << std::endl;
		for (int i = 0; i < opt.size(); i++)
		{
			std::cout << "[" << i + 1 << "] " << opt[i] << std::endl;
		}

		std::string input;
		getline(std::cin, input);
		std::stringstream(input) >> choice;

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			std::cout << "Please enter a valid option" << std::endl << std::endl;
		}
		else {

			if (choice == 1) {
				createDatabase();
			}
			else if (choice == 2) {
				executeQuery();
			}
			else if (choice == 3) {
				Records records = selectQuery("");
				for (auto& record : records) {
					for (auto& line : record) {
						for (int i = 0; i < line.size(); i++)
						{
							std::cout << line[i];
							i == 0 ? std::cout << " : " : std::cout << std::endl;
						}
					}
					std::cout << std::endl;
				}
			}
			else {
				quit = true;
			}

		}

		if (!quit) {
			std::cout << "Press any key to resume..." << std::endl;
			std::cin.ignore();
		}
		else {
			std::cout << "Bye !" << std::endl;
		}

	} while (!quit);

	return 0;
}

static int createDatabase() {

	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(dir, &DB);

	sqlite3_close(DB);

	if (exit == SQLITE_OK) {
		std::cout << "Database created !" << std::endl << std::endl;
	}
	else {
		std::cout << "Couldn't create the database" << std::endl << std::endl;
	}



	return 0;
};

int executeQuery(std::string query) {

	sqlite3* DB;
	char* errorMessage;

	if (query == "") {
		std::cout << "Enter the request to execute :" << std::endl;
		getline(std::cin, query);
	}

	try {
		int exit = 0;
		exit = sqlite3_open(dir, &DB);
		//dans le cas d'une maj de la db (insert, upstae, delete), pas besoin de callback ou de data a retourner (3eme et 4eme argument)
		exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &errorMessage);
		if (exit != SQLITE_OK) {
			std::cout << "A problem has occured during the exectuion of the query : " << errorMessage << std::endl;
			//liberer le pointeur du message plus utiliser et eviter les leaks
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Le changement a bien été enregistrer";
			sqlite3_close(DB);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}


	return 0;
}

Records selectQuery(std::string query) {

	sqlite3* DB;
	int exit = 0;
	Records records;
	char* errorMessage;

	if (query == "") {
		std::cout << "Enter the SELECT request to execute" << std::endl;
		getline(std::cin, query);
	}


	try {
		int exit = 0;
		exit = sqlite3_open(dir, &DB);
		//dans le cas d'un select : on fait passer un callback qui sera appeller pour chaque resultat. Le 4eme arg servira a faire remonter les données par le biais du callback (1er arg)
		exit = sqlite3_exec(DB, query.c_str(), callback, &records, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cout << "A problem has occured during the exectuion of the query : " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
		}
		else {
			std::cerr << records.size() << " records returned.\n\n";
			sqlite3_close(DB);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

	//on retourne records (remplit dans le callback)
	return records;
}


static int callback(void* p_data, int argc, char** argv, char** azColName) {
	//p_data, qui rappellont le est le tableau passer un 4eme argument, est recuperer, caster en Record *
	Records* records = static_cast<Records*>(p_data);

	try {
		//puis nous pushons les nouvelles donnée dans le tableau
		//records->emplace_back(argv);
		records->emplace_back(argv, argv + argc);
	}
	catch (std::exception& e) {
		std::cout << e.what();
		return 1;
	}

	return 0;
}