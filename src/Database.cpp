#include "Database.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Database::Database() {
	std::cout << "A new database is created\n";
}

void Database::add(Table* tb, std::string tableName) {
	std::cout << "Adds a table\n";
}

void Database::drop(std::string tableName) {
	std::cout << "Drops a table\n";
}

void Database::save(std::string fileName) {
	std::cout << "Exports the database to the given file\n";
}

void Database::load(std::string fileName) {
	std::cout << "Imports a database from the given file\n";
}

std::vector<std::string> Database::listTable() {
	std::cout << "Returns a list of all table names in the database\n";
	return tableNames;
}

std::vector<Table*> Database::getTables() {
	std::cout << "Returns all tables in the database\n";
	return tableList;
}

Table* Database::query(std::string select, std::string from, std::string where) {
	std::cout << "Does the query thing\n";

	

	return &Table();
}

void Database::all_functions() {
	Table* tb = new Table();
	add(tb, "table");
	drop("table");
	save("file");
	load("file");
	listTable();
	getTables();
	query("select", "from", "where");
}

vector<string> Database::selectParser(std::string selectArgs)
{
	vector<string> parsedInput;
	string argument;
	stringstream ss;
	ss << selectArgs;
	while (getline(ss, argument, ' '))
	{
		parsedInput.push_back(argument);
	}
	return parsedInput;
}

vector<string> Database::whereParser(std::string whereArgs)
{
	vector<string> parsedInput;
	return parsedInput;
}