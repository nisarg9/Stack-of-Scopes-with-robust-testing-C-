//lookup for all three scope option and dump function
//

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(8)lookup"){
    
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
	
	
	
	table.dump(std::cout); /*
	table.dump(std::cout, symtable<string, string>::ScopeOption::CURRENT);
	table.dump(std::cout, symtable<string, string>::ScopeOption::GLOBAL); */
}