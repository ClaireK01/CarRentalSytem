#include <vector>
#include <string>


#ifndef SQLITEDATABASE_HPP
#define SQLITEDATABASE_HPP

//Record : tableau de string (contenant les donnes), Records : tableau de tableau (1 tableaux = 1 ligne de resultat) creer . 
// Note : j'ai rajouter cell, pour faire de "Record" un tableau qui affichera la donnée ET le nom de la colonne, plutot que juste un tableau de string
using Cell = std::vector<std::string>;
using Record = std::vector<Cell>;
using Records = std::vector<Record>;

static const char* dbname = "CarRental.db";
static const char* dir = "C:\\sql_lite\\" + *dbname;
int menu();
static int createDatabase();
static int executeQuery(std::string query = "");
static Records selectQuery(std::string query = "");
static int callback(void* p_data, int argc, char** argv, char** azColName);

#endif#pragma once
