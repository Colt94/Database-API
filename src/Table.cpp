#include "Table.h"
#include "Record.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <new>


Table::Table()
{
	key = "";
	std::cout << "Empty table object will be created" << std::endl;
}

Table::Table(std::vector<std::string> &_attributes) {
	
	key = "";

	//Check for duplicate attribute names
	int dupeFound = 0;
	std::vector<std::string> temp = _attributes;
	std::sort(temp.begin(), temp.end());

	for (int i = 0; i < (temp.size() - 1); i++) {
		if (temp[i] == temp[i + 1]) {
			dupeFound = 1;
			break;
		}
	}
	if (dupeFound == 0) {
		attributes = _attributes;
	}
	else {
		std::cout << "Error: List contains duplicate attribute names " << std::endl;
	}
	//std::cout << "A new table with given attributes will be created here" << std::endl;
}

Table::~Table()
{
	if (tablePointer != NULL) {
		delete tablePointer;
	}
	//std::cout << "Deletes a table" << std::endl;
}

void Table::add_attribute(std::string _attribute) {
	//Check if attribute name already exists in table
	int nameMatch = 0;
	int i = 0;
	if (attributes.size() == 0) {
		attributes.push_back(_attribute);
	}
	else {
		for (i; i < attributes.size(); i++) {
			if (_attribute == attributes[i]) {
				nameMatch = 1;
				break;
			}
		}
		if (nameMatch == 0) {
			attributes.push_back(_attribute);

			//initialize all entries under new attribute to NULL
			for (int i = 0; i < records.size(); i++) {
				records[i].addNullEntry();
			}
		}
		//std::cout << "A new attribute will be added to the table" << std::endl;
	}
}

void Table::delete_attribute(std::string _attribute) {

	//check if attribute being deleted is the key attribute
	int column = 0;
	if (key == _attribute) {
		std::cout << "Error: cannot delete key attribute " << std::endl;
	}
	else {
		for (column; column < attributes.size(); column++) {
			if (_attribute == attributes[column])
				break;
		}
		if (records.size() > 0) {
			for (int j = 0; j < records.size(); j++) {
				records[j].eraseEntry(column);
			}
		}
			attributes.erase(attributes.begin() + column);
	}
	//std::cout << "The attribute given will be deleted from the table" << std::endl;
}

void Table::add_record(Record _record) {

	if (_record.size() != attributes.size()) {
		std::cout << "Error:  record size must equal the number defined attributes in the table" << std::endl;
	}
	else {
		int dupKeyEntry = 0;
		if (_record.size() != attributes.size()) {
			int sizeDiff = _record.size() - attributes.size();
			for (int i = 0; i < sizeDiff; i++)
				_record.addNullEntry();
		}

		if (key != "") {
			for (int i = 0; i < records.size(); i++) {
				if (_record.get(keyIndex) == records[i].get(keyIndex)) {
					dupKeyEntry = 1;
				}
			}
			if (dupKeyEntry == 1)
				std::cout << "Error: Key column (" << key << ") contains an entry matching that of the record being added " << std::endl;
			else
				records.push_back(_record);
		}
		else {
			records.push_back(_record);
		}
	}
}

Table::recordIterator Table::begin() {

	return records.begin();
}

Table::recordIterator Table::end() {

	return records.end();
}

void Table::assign_key(std::string _attribute) {
	//If attribute being assign a key value that has non-unique entries then an error is thrown.

	std::vector<std::string> keyVector(records.size());
	std::vector<Record> recordArray(records.size());
	
	int keyFound = 0;
	int dupEntries = 0;
	int keyPosition = 0;

	for (keyPosition = 0; keyPosition < attributes.size(); keyPosition++) {
		if (_attribute == attributes[keyPosition]) {
			keyFound = 1;
			break;
		}
	}
	if (keyFound == 0)
		std::cout << "Error: Could not find given attribute name" << std::endl;
	else {
		//If table is empty, no need to check for duplicates and make a new table
		if (records.size() == 0) {
			key = _attribute;
			keyIndex = keyPosition;
		}
		else {
			//grab keys entries for all records and store in temporaray vector
			int i = 0;
			for (auto it = records.begin(); it != records.end(); it++) {
				keyVector[i] = it->get(keyPosition); 
				i++;
			}
			//sort vector of key entries to make comparison easier
			std::sort(keyVector.begin(), keyVector.end());
			for (int j = 0; j < (keyVector.size() - 1); j++) {
				if (keyVector[j] == keyVector[j + 1]) {
					dupEntries = 1;
					break;
				}
			}
			if (dupEntries == 1) {
				std::cout << "Error: Duplicate key entries found. Cannot make attribute (" << _attribute << ") a key" << std::endl;
			}
			//assign key and key position
			else {
				key = _attribute;
				keyIndex = keyPosition;
			}
		}
	}
}

const std::vector<std::string> &Table::get_attributes() const {
	
	return attributes;
}

int Table::get_table_size() {

	return records.size();
	//std::cout << "The ammount of attributes(columns) will be returned" << std::endl;
}

double Table::count_entries(std::string _attribute) {

	int found = 0;
	int i = 0;
	int entryCount = 0;
	//std::cout << "Function will count all non-null entires under attribute name" << std::endl;
	/*Check is attribute name exist in table*/
	for (i; i < attributes.size(); i++) {
		if (attributes[i] == _attribute) {
			found = 1;
			break;
		}
	}
	if (found == 1) {
		for (auto it = records.begin(); it != records.end(); it++) {
			if(it->get(i) != "") //vector
				entryCount++;
		}
	}
	else {
		std::cout << "Error: attribute not found." << std::endl;
		return 0;
	}
	return entryCount;
}

std::string Table::min(std::string _attribute) {

	int column = 0;
	int found = 0;

	for (column; column < attributes.size(); column++) {
		if (_attribute == attributes[column]) {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		std::cout << "Error: attribute not found" << std::endl;

		return "";
	}
	else {
		std::string minValue = records[0].get(column);
		for (auto it = records.begin()++; it != records.end(); it++) {
			if (it->get(column) < minValue)// vector
				minValue = it->get(column); //vector

		}
		return minValue;
	}
	//std::cout << "Function will return the minimum value under given attribute name" << std::endl;

}

std::string Table::max(std::string _attribute) {

	int column = 0;
	int found = 0;

	for (column; column < attributes.size(); column++) {
		if (_attribute == attributes[column]) {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		std::cout << "Error: attribute not found" << std::endl;

		return "";
	}
	else {
		//std::string maxValue = records.begin()->second.get(column); <--map
		std::string maxValue = records[0].get(column); //vector
		for (auto it = records.begin(); it != records.end(); it++) {
			if (it->get(column) > maxValue)// vector
				maxValue = it->get(column); //vector
		}
		return maxValue;
	}

}

Table * cross_join(Table &_table1, Table &_table2) {

	//std::cout << "Function will perform a cross-join operation between two tables" << std::endl;
	std::vector<std::string> columns1 = _table1.get_attributes();
	std::vector<std::string> columns2 = _table2.get_attributes();

	//put all attributes in column1 vector
	for (int i = 0; i < columns2.size(); i++)
		columns1.push_back(columns2[i]);

	Table *outTable = new Table();
	//add attributes from both tables to new table
	for (int j = 0; j < columns1.size(); j++) {
		outTable->add_attribute(columns1[j]);
	}
	for (auto it1 = _table1.begin(); it1 != _table1.end(); ++it1) {
		for (auto it2 = _table2.begin(); it2 != _table2.end(); ++it2) {
			Record r = *it1 + *it2;
			outTable->add_record(r);
		}
	}
	return outTable;
}

std::string Table::getKey() {
	
	return key;
}

Table * natural_join(Table &_table1, Table &_table2) {

	int keyMatch = 0;
	std::vector<std::string> columns1 = _table1.get_attributes();
	std::vector<std::string> columns2 = _table2.get_attributes();
	std::vector<std::tuple<int, int, std::string>> columnMatches;

	if (_table2.getKey() == "") {
		std::cout << "Error: Table2 does not have a key" << std::endl;
		return &_table1;
	}
	for (int i = 0; i < columns1.size(); i++) {
		if (columns1[i] == _table2.getKey()) {
			keyMatch = 1;
			break;
		}
	}
	if (keyMatch == 0) {
		std::cout << "Error: Table2 key column does not match any columns from table1" << std::endl;
		return &_table1;
	}
	else {
		int match = 0;
		for (int i = 0; i < columns1.size(); i++) {
			for (int j = 0; j < columns2.size(); j++) {
				if (columns1[i] == columns2[j]) {
					columnMatches.push_back({ i, j, columns1[i] });
					columns2[j] = "b";// <-- dummy values to indicate the deletion of this index 
					match++;
				}
			}
		}
		if (match == 0) {
			std::cout << "Error: no matching attributes between the two tables. " << std::endl;
			return &_table1;
		}
		else {
			for (int i = 0; i < columns2.size(); i++) {
				if (columns2[i] == "b") {
					columns2.erase(columns2.begin() + i);
					i--;
				}
			}
			std::vector<std::string> atrbts = columns1;
			//for (int i = 0; i < columnMatches.size(); i++) {
				//atrbts.push_back(std::get<2>(columnMatches[i]));
			//}
			//columns1.insert(columns1.end(), columns2.begin(), columns2.end());
			atrbts.insert(atrbts.end(), columns2.begin(), columns2.end());
			Table *outTable = new Table(atrbts);


			int erased = 0;
			for (auto it = _table1.begin(); it != _table1.end(); it++) {
				for (auto it2 = _table2.begin(); it2 != _table2.end(); it2++) {
					for (int i = 0; i < columnMatches.size(); i++) {
						if ((it->get(std::get<0>(columnMatches[i])) == (it2->get(std::get<1>(columnMatches[i]))))) {
							//it2->eraseEntry(std::get<1>(columnMatches[i]));
							erased++;
						}
					}
					if (erased == columnMatches.size()) {
						Record r0(it2->size() - columnMatches.size());
						int shouldAdd = 0; // <-- the entry from table 2 should be added to r0 when this value = 0. This means it is not an entry under a shared attribute.
						int recordIndex = 0; // <-- used for r0 indexing
						for (int j = 0; j < it2->size(); j++) {
							for (int i = 0; i < columnMatches.size(); i++) {
								if (j == std::get<1>(columnMatches[i])) {
									shouldAdd++;
								}
							}
							if (shouldAdd == 0) {
								r0.set(recordIndex, it2->get(j));
								recordIndex++;
							}
							shouldAdd = 0;
						}
						
						Record r1((atrbts.size()));
						r1 = *it + r0;
						outTable->add_record(r1);
					}
					erased = 0;
				}
			}
			return outTable;
		}
	}
}

void Table::printTable() {

	for (int i = 0; i < attributes.size(); i++) {
		std::cout << attributes[i] << "   ";
	}
	std::cout << std::endl;

	auto it = records.begin();
	for (it; it != records.end(); it++) {
		for (int i = 0; i < it->size(); i++) {
			std::cout << it->get(i) << "   ";
		}
		std::cout << std::endl;
	}
}

