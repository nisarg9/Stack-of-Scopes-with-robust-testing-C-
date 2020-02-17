#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(3)insert and lookup")
{
	symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
	
  table.insert("k","int");	
  
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
 
  string symbol;
  
  REQUIRE(table.lookup("k", symbol, symtable<string, string>::ScopeOption::CURRENT));
  REQUIRE(symbol == "int");   //checks for correct symbol for two similar named keys
}