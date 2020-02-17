//checks if global scope option is properly working my entering exiting and inserting and looking up in variety of combination

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(10) check global"){
    
    symtable<string, string>  table;
	string symbol;
        
    table.enterScope("global");
	table.insert("g", "double");
	table.insert("g","int");
	
    table.enterScope("current");
	table.insert("g","char");
	
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(symbol == "int");
	REQUIRE(!table.lookup("a", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.size() == 2);
	
	table.enterScope("new");
	table.insert("g","char");
	
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(symbol == "int");
	
	table.exitScope();
	table.exitScope();
	table.exitScope();
	
	REQUIRE(table.numscopes() == 0);
	
	REQUIRE(!table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	
    
    
}	
