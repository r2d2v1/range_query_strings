//============================================================================
// Name        : StringRange.cpp
// Author      : Vijay
// Version     :
// Copyright   : 
// Description : "mail@vijayrajakumar.com"
//============================================================================

#include <iostream>
#include "Trie.h"

using namespace std;

int main()
{
	Trie *t = new Trie();

	t->addkeywordRange("[ aaa , ccc ]");
	t->addkeywordRange("[ Aaa , Dgh ]");
	t->addkeywordRange("[ Cfg , EEE ]"); // invalid

	std::cout << t->isKeywordValid("aa") << std::endl;

	delete t;

	std::cout << "hello" << std::endl;
	return 0;
}
