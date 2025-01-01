#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <map>
#include "InputController.h"


bool listenAndRedirect(Menu menu) {
	std::string input;
	getline(std::cin, input);

	return redirect(input, menu);

}

bool redirect(std::string choice, Menu menu) {

	bool found = false;

	for (int i = 0; i < menu.optionList.size(); i++)
	{
		if (menu.optionList[i].selection == choice) {
			menu.optionList[i].func();
			found = true;
			break;
		}
	}

	return found;
}