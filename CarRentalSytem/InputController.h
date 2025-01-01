#include <vector>
#include <string>
#include "SqliteDatabase.h"
#include "App.h"


#ifndef INPUTCONTROLLER_HPP
#define INTPUTCONTROLLER_HPP

struct MenuOption { 
	int (*func)(); 
	int type;std::string name; 
	std::string selection; 
	MenuOption(std::string n, int(*f)(), std::string s, int t) : func(f), type(t), name(n), selection(s){};
};
struct Menu { 
	std::vector <MenuOption> optionList;
	Menu(std::vector <MenuOption> l) : optionList(l){};
};

static MenuOption listCar("Voir les voiture", carList, "S", 1);
static MenuOption addCar("Ajouter une voiture", carForm, "A", 2);
static MenuOption back("Retour", displayMenu, "R", 1);
static MenuOption admin("Admin", menu, "999", 2);

static Menu mainMenu({ listCar, addCar, admin});
static Menu carListMenu({addCar, back});

bool listenAndRedirect(Menu m);
bool redirect(std::string choice, Menu m);

#endif
#pragma once
