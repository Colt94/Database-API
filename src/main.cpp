#include "Database.h"
#include "Table.h"
#include "Record.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

int main() {

	
	
	vector<string> a0 = { "Name", "SSN","School","Date"};
	vector<string> a1 = {"School", "Date","City", "SSN"};

	Record r0(4), r1(4), r2(4);

	Record r3(4), r4(4), r5(4);

	r0.set(0, "Joe Smith");
	r0.set(2, "Rice");
	r0.set(1, "123");
	r0.set(3, "2019");

	r1.set(0, "Jill Smith");
	r1.set(2, "LSU");
	r1.set(1, "345");
	r1.set(3, "2005");

	r2.set(0, "Sam Jones");
	r2.set(2, "Texas A&M");
	r2.set(1, "567");
	r2.set(3, "2001");

	r3.set(0, "Texas A&M");
	r3.set(2, "College Station");
	r3.set(3, "567");
	r3.set(1, "2001");

	r4.set(0, "Rice");
	r4.set(2, "Houston");
	r4.set(3, "123");
	r4.set(1, "2019");

	r5.set(0, "LSU");
	r5.set(2, "Baton Rouge");
	r5.set(3, "345");
	r5.set(1, "2005");

	
	Table table1(a0);
	Table table2(a1);
	//table1.assign_key("Model");
	//vec = table1.get_attributes();
	//for (int i = 0; i < vec.size(); i++)
		//cout << vec[i] << " ";

	//table1.assign_key("Model");
	//table2.assign_key("Seats");

	table1.add_record(r0);
	table1.add_record(r1);
	table1.add_record(r2);

	table2.add_record(r3);
	table2.add_record(r4);
	table2.add_record(r5);

	//table1.add_attribute("Color");
	//table2.assign_key("Seats");
	Table * table3;
	table2.assign_key("School");
	table3 = natural_join(table1, table2);
	//table3 = NULL;

	//int count = table3->count_entries("Paint");
	//string min = table3->min("Paint");
	//string max = table3->max("Paint");
	//cout << "Min: " << min << endl;
	//cout << "Max: " << max << endl;

	//cout << count << endl;

	//table3->delete_attribute("Seats");
	table3->printTable();
	Database db;
	//db.add(table3, "table3");
	//db.save("test1");
	db.load("test");
	db.save("test2");
	delete table3;
	
	

	
	system("pause");
	return 0;
}
