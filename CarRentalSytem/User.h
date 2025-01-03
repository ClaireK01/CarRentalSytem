#pragma once
#include <iostream>
#include <string>
#include <conio.h> 
#include <vector> 

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
	void setUsername(std::string u) { username = u; }
	void setPassword(std::string p) { password = p; }
	void setType(int t) { type = t; }
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
			if ((*User::list[i]).get_uuid() == get_uuid()) {
				User::list.erase(User::list.begin() + i); //voir utilisation std::find()
				break;
			}
		}
	}
};
