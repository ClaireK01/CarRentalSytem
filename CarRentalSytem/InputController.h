#include <vector>
#include <string>
#include "SqliteDatabase.h"
#include "App.h"


#ifndef INPUTCONTROLLER_HPP
#define INTPUTCONTROLLER_HPP

struct MenuOption { 
	int (*func)(); 
	int type;
	std::string name; 
	std::string selection; 
	bool hide;
	MenuOption(std::string n, int(*f)(), std::string s, int t, bool h = false) : func(f), type(t), name(n), selection(s), hide(h){};
};

struct Menu { 
	std::vector <MenuOption> optionList;
	Menu(std::vector <MenuOption> l) : optionList(l){};
};

static MenuOption listCar("Voir les voiture", carList, "S", 1);
static MenuOption addCar("Ajouter une voiture", carForm, "A", 2);
static MenuOption deleteCar("Supprimer une voiture", carDelete, "D", 2);
static MenuOption back("Retour", NULL, "R", 1);
static MenuOption leave("Quitter", NULL, "Q", 0);
static MenuOption unlog("Se deconnecter", NULL, "U", 1);
static MenuOption admin("Gestion BDD", menu, "999", 2, true);
static MenuOption connexion("Se connecter", checkAuth, "L", 0);


static Menu connexionMenu({connexion, leave});
static Menu mainMenu({listCar, addCar, deleteCar, unlog, admin});
static Menu carListMenu({addCar, deleteCar, back});

bool listenAndRedirect(Menu m, User cUser);
bool redirect(std::string choice, Menu m, User cUser);

#endif