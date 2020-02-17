//add remove size check, after deleteing scope size is getting rediced or not check

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(11) add remove size check"){
    
    symtable<string, string>  table;
	string symbol;
        
    table.enterScope("global");
	table.exitScope();
	
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
	
	table.enterScope("global");
	table.insert("g", "double");
	table.insert("g","int");
	REQUIRE(table.size() == 1);
	REQUIRE(table.numscopes() == 1);
	
	table.exitScope();
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
	
	table.enterScope("global");
	table.enterScope("g2");
	table.enterScope("g3");
	table.enterScope("g4");
	table.insert("g", "double");
	
	REQUIRE(table.size() == 1);
	REQUIRE(table.numscopes() == 4);
	REQUIRE(!table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
	table.exitScope();
	table.exitScope();
	table.exitScope();
	table.exitScope();
	
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
	
	table.enterScope("g3");
	table.insert("g", "double");
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	
}	
	
	
	