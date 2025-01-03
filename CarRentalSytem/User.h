#pragma once
#include <iostream>
#include <string>
#include <conio.h> 
#include <vector> 

class User {

private:
	std::string username, password;
	int type = 0;

public:
	//constructor
	User() = default;
	User(std::string u, std::string p, int t) : username(u), password(p), type(t) {};

	bool checkPassword(std::string input) { return input == password; }
	void setPassword(std::string p) { password = p; }
	std::string getUsername() { return username; }
	void setUsername(std::string u) { username = u; }
	int getType() { return type; }
	void setType(int t) { type = t; }
	void reset() {
		username = "";
		password = "";
		type = 0;
	}

	//destructor
	~User() {}
};
