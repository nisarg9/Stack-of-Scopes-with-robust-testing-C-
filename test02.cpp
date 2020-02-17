#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("(2)testing insert scope"){
    
    symtable<string, string>  table;
    string symbol;
    
    table.enterScope("global");
    table.enterScope("current");
    
    table.insert("i", "int");   //testing insert with two same varibale name with different symbol(type)
    table.insert("j", "double");
    
    REQUIRE(table.size() == 2);
    REQUIRE(table.numscopes() == 2);
    
    REQUIRE(table.lookup("i", symbol, symtable<string, string>::ScopeOption::CURRENT));   //tests lookup in current
      
}