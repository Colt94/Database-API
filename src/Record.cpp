#include <iostream>
#include "Record.h"

using namespace std;

Record::Record() {
	
}

Record::Record(int size)
{
	for (int i = 0; i < size; ++i)
	{
		entries.push_back("");
	}
}

Record::~Record()
{
	
}

int Record::size()
{
	return entries.size();
}

void Record::set(int entry, string value)
{
	entries.at(entry) = value;
}

string Record::get(int entry)
{
	return entries.at(entry);
}

void Record::addNullEntry()
{
	entries.push_back("");
}

void Record::eraseEntry(int index)
{
	entries.erase(entries.begin() + index);
}

Record operator +(Record r1, Record r2) 
{

	Record r3(r1.size() + r2.size());
	int i = 0;
	for (i; i < r1.size(); i++)
		r3.set(i, r1.get(i));
	
	for (int j = 0; j < r2.size(); j++)
		r3.set((i + j), r2.get(j));

	return r3;
}