//Checks for Runtime error on exit scope

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(4)Run time error exitScope")
{
	symtable<string, string> table;
	
	try
	{
	  table.exitScope();   //checks runtime error is exitscope is entered when no scope is present
	  REQUIRE(false);
	}
	catch(runtime_error e)
	{
		REQUIRE(true);
		cout << "Runtime error: " << e.what() << endl;;
	}
	
}