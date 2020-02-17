//checks constructor, size, enterScope and exitScope

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(0)initially empty")
{
	symtable<string, string> table;  //checks constructor
	REQUIRE(table.size() == 0);   //checks size
	//REQUIRE(table.numscopes() == 0);
	
	
	table.enterScope("global");    //checks enterscope and exitScope
	//REQUIRE(table.numscopes() == 1);
	
	table.exitScope();
	REQUIRE(table.numscopes() == 0);  //check numscopes
	
}