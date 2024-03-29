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

void test1()
{
	Trie *t = new Trie();

	t->addKeywordRange("[ aaa , ccc ]");
	assert( t->isKeywordValid("aa") == 0);
	assert( t->isKeywordValid("aaa")  == 1);

	t->addKeywordRange("[ aaa , ddd )");
	assert( t->isKeywordValid("ddd")  == 0); // due to ) on end range.

	t->addKeywordRange("[ aaa , ddd ]");
	assert( t->isKeywordValid("ddd")  == 1); // due to ] on end range.

	t->addKeywordRange("[ Aaa , Dgh ]");
	t->addKeywordRange("[ Cfg , EEE ]");
	t->addKeywordRange("[ zzz , yyy ]"); // invalid

	t->addKeywordRange("[ ppp , rrr ]");

	//t->print();

	assert( t->isKeywordValid("ppp")  == 1);
	assert( t->isKeywordValid("rrr")  == 1);
	assert( t->isKeywordValid("qqq")  == 1);

	assert( t->isKeywordValid("Dgh")  == 1);
	assert( t->isKeywordValid("EEE")  == 1);
	assert( t->isKeywordValid("zzz")  == 0); // due to invalid entry

	t->delKeywordRange("[ aaa , bbb ]");
	t->delKeywordRange("[ Aaa , Aab ]");
	t->delKeywordRange("[ Czh , Eee ]");
	t->delKeywordRange("[ zzz , yyy ]"); // invalid range
	t->delKeywordRange("[ zzz , yyy]"); // invalid input

	// After deletion
	assert( t->isKeywordValid("aa")  == 0);
	assert( t->isKeywordValid("ccc")  == 1);
	assert( t->isKeywordValid("Dgh")  == 0);
	assert( t->isKeywordValid("EEE")  == 0);
	assert( t->isKeywordValid("zzz")  == 0); // due to invalid entry

	delete t;
}

void test2()
{
	Trie *t = new Trie();

	t->addKeywordRange("[ aaa , ccc ]");
	t->addKeywordRange("[ eee , ggg ]");

	//t->print();

	assert( t->isKeywordValid("bbb")  == 1);
	assert( t->isKeywordValid("ddd")  == 0);

	t->addKeywordRange("[ aaa , ccc ]");
	t->addKeywordRange("[ bbb , eee ]");

	assert( t->isKeywordValid("ddd")  == 1);
	assert( t->isKeywordValid("bbb")  == 1);

	delete t;
}

int main()
{
	//test1();
	test2();

	std::cout << "all tests passed" << std::endl;
	return 0;
}
