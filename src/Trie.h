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

	void setValidFromRangeAToRangeB(const TrieNode *range_a, bool &found_a, const TrieNode *range_b, bool &found_b)
	{
		if (found_b)
		{
			std::cout << "f_b"  << std::endl;
			return;
		}
		for (unsigned i =0; i < 128; i++)
		{
			if (this->children[i] != NULL)
			{
				std::cout << (char)i  << std::endl;
				if (not found_a)
				{
					if (this->children[i] == range_a)
					{
						found_a = true;
						std::cout << "f_a"  << std::endl;
					}
				}

				if (found_a && not found_b)
				{
					this->children[i]->valid = true;
					if (this->children[i] == range_b)
					{
						found_b = true;
						std::cout << "f_b"  << std::endl;
						break;
					}
				}

				this->children[i]->setValidFromRangeAToRangeB(range_a, found_a, range_b, found_b);
			}
		}
		return;
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
		bool found_a = false;
		bool found_b = false;
		this->root->setValidFromRangeAToRangeB(range_a, found_a, range_b, found_b);
	}

	bool addkeywordRange(const std::string &in)
	{
		std::stringstream str(in);
		std::string open, rangeA, comma, rangeB, close;
		str >> open >> rangeA >> comma >> rangeB >> close;

		std::cout << "|" << open << "|" << rangeA << "|" << comma << "|" << rangeB << "|" << close << std::endl;

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
