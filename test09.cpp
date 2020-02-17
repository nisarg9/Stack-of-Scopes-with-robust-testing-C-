//lookup for from 1000000 elemnts to check for complexity

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(9) insert 1000000 and lookup for complexity"){
    
    symtable<string, string>  table;
	string symbol;
        
    table.enterScope("global");
	table.insert("g", "double");
	
    table.enterScope("current");
    
    table.insert("i", "int");
    table.insert("j", "double");
    
       
    REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(symbol == "int");
	
	REQUIRE(table.lookup("j", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(symbol != "int");
	
	REQUIRE(!table.lookup("g", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::ALL));
    REQUIRE(symbol == "double");  
	
	REQUIRE(table.lookup("g", symbol, symtable<string, string>::ScopeOption::GLOBAL));
    REQUIRE(symbol == "double");
	
	for (int i =0; i < 1000000; i++)
		table.insert(to_string(i), "int");
		
	REQUIRE(table.lookup("65678", symbol, symtable<string, string>::ScopeOption::ALL));
}	