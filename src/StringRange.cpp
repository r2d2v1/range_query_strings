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
	t->addKeyword("aaA");

	t->addKeyword("aa");

	t->addKeyword("aBa");

	std::cout << t->addKeyword("aa") << std::endl;

	//t->print();

	std::cout << t->isKeywordValid("aa") << std::endl;


	delete t;

	std::cout << "hello" << std::endl;
	return 0;
}
