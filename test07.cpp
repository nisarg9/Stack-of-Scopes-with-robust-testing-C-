//Insert

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(7)Insert")
{
	symtable<string, string> table;
	//int i;
	
	table.enterScope("Global");
	table.enterScope("G2");
		
	table.insert("i", "char"); //checks insert and size
	table.insert("i","int");
	REQUIRE(table.size() == 1);
}	