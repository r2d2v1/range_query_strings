#ifndef __TRIE_H__
#define __TRIE_H__

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <cassert>

using std::vector;

class TrieNode
{

public:
	//char character; // redundant
	TrieNode *children[128]; // ASCII is 0-127 characters rite
	bool valid; // node and subtree is invalid

	TrieNode()
	{
		for (unsigned i = 0; i < 128; i++)
			this->children[i] = NULL;

		this->valid = false;
	};

	virtual ~TrieNode()
	{
		for (unsigned i = 0; i < 128; i++)
		{
			if ( this->children[i] != NULL)
				delete this->children[i];
		}
	};

	static int8_t getIndex(char character)
	{
		return (int8_t)character;
	}

	static bool isValidIndex(int index)
	{
		return (index >= 0) && (index < 128);
	}

	TrieNode* getChildNode(char character)
	{
		if (isValidIndex(getIndex(character)))
			return this->children[getIndex(character)];
		else
			return NULL;
	}

	TrieNode* setNodeValid()
	{
		this->valid = true;
	}

	TrieNode* addChildNode(char character)
	{
		if (isValidIndex(getIndex(character)))
			return this->children[getIndex(character)] = new TrieNode();
	}

	void print() const
	{
		for (unsigned i = 0; i < 128; i++)
		{
			if ( this->children[i] != NULL)
				if (this->children[i]->valid);
					std::cout << (char)i <<  std::endl;
				this->children[i]->print();

		}
	}
};

class Trie
{
private:
	TrieNode *root;

public:

	Trie()
	{
		this->root = new TrieNode();
		this->root->valid = true;
	};

	virtual ~Trie()
	{
		if (this->root != NULL)
			delete this->root;
	};

	/**
	 * insert the keyword into the trie
	 * If the keyword is empty, returns 0, as empty srting is not a valid input string.
	 */
	TrieNode* addKeyword(const std::string &keyword)
	{
		///corner case to check invalid empty string
		if ( keyword.size() == 0 )
			return NULL;

		TrieNode *node = this->root;

		char *charIterator = (char *) keyword.c_str();

		while (*charIterator)
		{
			assert (node != NULL);
			//std::cout << *charIterator << std::endl;

			TrieNode *childNode = node->getChildNode(*charIterator);
			if (childNode == NULL)
			{
				node = node->addChildNode(*charIterator);
			}

			++charIterator;
		}
		//std::cout << "---" << std::endl;
		return node;
	};

	bool isKeywordValid(const std::string &keyword) const
	{
		bool returnValue = false;

		if ( keyword.size() == 0 )
			return returnValue;

		TrieNode *node = this->root;
		char *charIterator = (char *) keyword.c_str();

		while ( node!= NULL && node->valid && *charIterator)
		{
			std::cout << *charIterator << std::endl;
			TrieNode *childNode = node->getChildNode(*charIterator);
			if (childNode == NULL)
			{
				returnValue = true;
				break;
			}
			node = childNode;
			++charIterator;
		}

		if (not charIterator)
			returnValue = true;

		return returnValue;
	}

	bool setValidFromRangeAToRangeB(TrieNode *range_a, TrieNode *range_b)
	{

		TrieNode *range_a = this->addKeyword(rangeA);
		TrieNode *range_b = this->addKeyword(rangeB);
	}

	bool addkeywordRange(const std::string &in)
	{
		std::stringstream str(in);
		std::string open, rangeA, comma, rangeB, close;
		str >> open >> rangeA >> comma >> rangeB >> close;

		TrieNode *range_a = this->addKeyword(rangeA);
		TrieNode *range_b = this->addKeyword(rangeB);

		this->setValidFromRangeAToRangeB(range_a, range_b);
	}

	void print() const
	{
		this->root->print();
	}
};

#endif //__TRIE_H__
