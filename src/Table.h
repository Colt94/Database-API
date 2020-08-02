#pragma once
#include "Record.h"
#include <iostream>
#include <vector>
#include <map>


class Table
{
	
	private:	
		std::vector<std::string> attributes;
		//std::map<std::string, Record> records;
		std::vector<Record> records;
		std::string key;
		int keyIndex;
		Table *tablePointer = NULL;
	public:
		Table();
		Table(std::vector<std::string> &_attributes);
		~Table();

		void add_attribute(std::string _attribute);
		void delete_attribute(std::string _attribute);
		void add_record(Record _record);

		const std::vector<std::string> &get_attributes() const;
		int get_table_size();

		//typedef std::map<std::string, Record>::iterator recordIterator;
		typedef std::vector<Record>::iterator recordIterator;
		recordIterator begin();
		recordIterator end();

		Record& find_record(std::string key);
		void assign_key(std::string _attribute);

		double count_entries(std::string _attribute);
		std::string min(std::string _attribute);
		std::string max(std::string _attribute);

		std::string getKey();
		void printTable();


		friend Table * cross_join(Table &_table1, Table &_table2);
		friend Table * natural_join(Table &_table, Table &_table2);
		
};

//friend Table * cross_join(Table &_table1, Table &_table2);
//friend Table * natural_join(Table &_table, Table &_table2);
