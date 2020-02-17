/*symtable.h*/

// 
// << Nisarg Thakkar >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  deque<Scope> table; //table made with deque of Scope
  int Size = 0;   //variable to keep track of size
  int NumScopes = 0;  //keeps track of NumScopes

public:

  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    //
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
    //
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  
  int size() const
  {
	return Size;   //return size, no operation needed.
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  {
    return NumScopes;    //Number of scopes on deque
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  {
	table.push_front(name);    //pushing the entered scope on front of deque, abstraction of stack
	NumScopes++;               //every time scope is entered, numscope is added by one 
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
	if (NumScopes == 0)                     //if no scope exist on deque, run time error is thrown
	  throw runtime_error("Exit Scope");
    
	else
	{
	  Size = Size - table.front().Symbols.size();      //size is being adjusted when we pop the current scope, all of its variables
      table.pop_front();                               //are deducted to keep track of size
	  NumScopes--;                                    //number of scope is deducted by 1 after poping the current scope from front
	}
  }

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
    if (NumScopes == 0)                                 //if no scope exist, run time is error is thrown
	  throw runtime_error("Current Scope");
	  
	else
	{
	  return table.front();      //otherwise front of deque is taken current scope
	}
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
	if(table.front().Symbols.count(key) == 0)      //if the key doesn't exist in current scope, size is added as one
	  Size++;
    
	table.front().Symbols[key] = symbol;         //if key already exist, it's value(symbol) is changed, no need to increase size
	
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
    if (option == ScopeOption::ALL && NumScopes > 0)     //if the scope defined as ALL
	{
      for (int i = 0; i < NumScopes; i++)                //loop through all scopes and find if key exists and if so it's symbol 
	  {                                               // is returned and boolean true is returned, if key not found, false is returned
	    if (table[i].Symbols.count(key) == 1) //if key exist
		{
		  symbol = table[i].Symbols.at(key);
		  return true;
		}
	  }//loop through scopes
	  return false;
	}//scope: all
	
    else if (option == ScopeOption::CURRENT && NumScopes > 0)     //if current scope is defined for lookup function
	{                                                             //just serach in the first element of deque (0 index, front)
	  if (table[0].Symbols.count(key) == 1)  //if key exist       //it's symbol and true returd if found.
		{
		  symbol = table[0].Symbols.at(key);
		  return true;
		}
	  return false;
	}
      
    else if (option == ScopeOption::GLOBAL && NumScopes > 0)    //if scope is global, it's last element(back) of deque is looked into
	{                                                            //if found, its symbol and true is returned
	  if (table[NumScopes - 1].Symbols.count(key) == 1) //if key exists
		{
		  symbol = table[NumScopes - 1].Symbols.at(key);
		  return true;
		}
	  return false;
	}
    return false;     //if we don't get into any of the above condition, it means NumScopes = 0, and no key exists, so return false
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL)      //printing all, current or global scope varibales and its symbols
	{
      output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  
	  for (int i = 0; i < NumScopes; i++)                 //looping through all scopes and printing its contents (symbols)
	  {
	    output << "** " << table[i].Name << " **" << endl;; 
	    for(auto& j: table[i].Symbols)  //for each loop to print map's(Symbols) contents
		{
		  output << j.first << ": " << j.second << endl;
		}
	  }
	 }//scope::ALL
	 
    else if (option == ScopeOption::CURRENT)
	{
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  
	  output << "** " << table[0].Name << " **" << endl;
	  
	    for(auto& j: table[0].Symbols) //printing current scopes contents by accessing first (front) scope
		{
		  output << j.first << ": " << j.second << endl;
		}

	 }//scope::current
    
	else // global:
	{
      output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  
	  output << "** " << table[NumScopes - 1].Name << " **" << endl;
	  
	    for(auto& j: table[NumScopes - 1].Symbols)   ////printing global scopes contents by accessing last (back) scope
		{
		  output << j.first << ": " << j.second << endl;
		}
    }

    
    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
