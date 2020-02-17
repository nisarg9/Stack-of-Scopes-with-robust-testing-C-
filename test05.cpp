//CurScope testing
//Cheking if exception is handled in curScope when zero scope
//and when scope is persent, top scope becomes correct scope

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(5)initially empty")
{
	symtable<string, string> table;
	
	try
	{
	  table.curScope();  //checks curScope method, handles exception if no scope is exists
	  REQUIRE(false);
	}
	catch(runtime_error e)
	{
		REQUIRE(true);
		cout << "Runtime error: " << e.what() << endl;
	}
	
    table.enterScope("Global");
	table.enterScope("G2");
	
	string a = table.curScope().Name;
	REQUIRE(a == "G2"); //checks if curScope's name is properly updated
	
}