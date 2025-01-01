#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <exception>
#include <sqlite3.h>
#include <map>
#include "User.h"


#ifndef APP_HPP
#define APP_HPP

// les variable static doivent etre defini en dehors du code OU initiliser avec le keyword inline
// attention a ne pas le mettre dans le header
int checkAuth();
int carList();
int carForm();
int displayMenu();

#endif
#pragma once