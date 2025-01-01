#include <vector>
#include <string>


#ifndef SQLITEDATABASE_HPP
#define SQLITEDATABASE_HPP

//Record : tableau de string (contenant les donnes), Records : tableau de tableau (1 tableaux = 1 ligne de resultat) creer . 
// Note : j'ai rajouter cell, pour faire de "Record" un tableau qui affichera la donnée ET le nom de la colonne, plutot que juste un tableau de string
using Record = std::vector<std::string>;
using Records = std::vector<Record>;

static const char* dbname = "CarRental.db";
static const char* dir = "C:\\sql_lite\\CarRental.db";
int menu();
static int createDatabase();
int executeQuery(std::string query = "");
Records selectQuery(std::string query = "");
static int callback(void* p_data, int argc, char** argv, char** azColName);

#endif#pragma once
