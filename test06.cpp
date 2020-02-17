//CurScope, Enter and Exit Scope, and NumScope

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(6)enter, exit and current scope interactions and numscope function")
{
	symtable<string, string> table;
	
	table.enterScope("Global");
	table.enterScope("G2");
	REQUIRE(table.numscopes() == 2);
	
	string a = table.curScope().Name;
	REQUIRE(a == "G2");
	REQUIRE(a != "Global"); //checks interactions between different functions
	
	table.exitScope();
	string b = table.curScope().Name;
	REQUIRE(b == "Global");
	REQUIRE(table.numscopes() == 1);
}	