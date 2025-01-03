#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <map>
#include "InputController.h"


bool listenAndRedirect(Menu menu, User cUser) {
	std::string input;
	getline(std::cin, input);

	return redirect(input, menu, cUser);
}

bool redirect(std::string choice, Menu menu, User cUser) {

	bool stop = false;

	for (int i = 0; i < menu.optionList.size(); i++)
	{
		if (menu.optionList[i].selection == choice) {
			if (menu.optionList[i].func != NULL) {

				if (menu.optionList[i].type <= cUser.getType()) {
					menu.optionList[i].func();
				}

			} else {
				stop = true;
			}

			break;
		}
	}


	return stop;
}