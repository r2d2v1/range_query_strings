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

	t->addKeywordRange("[ aaa , ccc ]");
	t->addKeywordRange("[ aaa , ccc ]");
	t->addKeywordRange("[ Aaa , Dgh ]");
	t->addKeywordRange("[ Cfg , EEE ]");
	t->addKeywordRange("[ zzz , yyy ]"); // invalid

	std::cout << "aa:" << t->isKeywordValid("aa") << std::endl;
	std::cout << "aaa:" << t->isKeywordValid("aaa") << std::endl;
	std::cout << "Dgh:" << t->isKeywordValid("Dgh") << std::endl;
	std::cout << "EEE:" << t->isKeywordValid("EEE") << std::endl;
	std::cout << "zzz:" << t->isKeywordValid("zzz") << std::endl; // due to invalid entry


	t->addKeywordRange("[ aaa , bbb ]");
	t->delKeywordRange("[ Aaa , Aab ]");
	t->delKeywordRange("[ Czh , Eee]");
	t->delKeywordRange("[ zzz , yyy ]"); // invalid

	// After deletion
	std::cout << "after deletion" << std::endl;
	std::cout << "aa:" << t->isKeywordValid("aa") << std::endl;
	std::cout << "aaa:" << t->isKeywordValid("aaa") << std::endl;
	std::cout << "Dgh:" << t->isKeywordValid("Dgh") << std::endl;
	std::cout << "EEE:" << t->isKeywordValid("EEE") << std::endl;
	std::cout << "zzz:" << t->isKeywordValid("zzz") << std::endl; // due to invalid entry

	delete t;

	//std::cout << "hello" << std::endl;
	return 0;
}
