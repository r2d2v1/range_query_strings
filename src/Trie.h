#ifndef __TRIE_H__
#define __TRIE_H__

#include <math.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <sstream>
#include <cassert>

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

	const TrieNode* getChildNode(char character) const
	{
		if (isValidIndex(getIndex(character)))
			return this->children[getIndex(character)];
		else
			return NULL;
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

	const TrieNode* getRightMostNodeInSubTrie() const
	{
		if (this == NULL) return NULL;
		for (unsigned siblingIterator = 127;
				 siblingIterator >= 0;
				--siblingIterator)
		{
			const TrieNode *rightSibling = this->getChildNode(siblingIterator);
			if (rightSibling != NULL)
			{
				rightSibling =  rightSibling->getRightMostNodeInSubTrie();
				return rightSibling;
			}
		}
		return NULL;
	}

	const TrieNode* getLeftMostNodeInSubTrie() const
	{
		for (unsigned siblingIterator = 0;
				siblingIterator < 128;
				++siblingIterator)
		{
			const TrieNode *leftSibling = this->getChildNode(siblingIterator);
			if (leftSibling != NULL)
			{
				leftSibling =  leftSibling->getLeftMostNodeInSubTrie();
				return leftSibling;
			}
		}
		return NULL;
	}

	//  Checks wether range_a and range_b are valid.
	// To pre order traversal of the Trie. Check if range_a is reached before range_b trienode.
	void checkValidRange(const TrieNode *range_a, bool &found_a, const TrieNode *range_b, bool &found_b) const
	{
		// stopping condition for dfs.
		if (found_b)
		{
			//std::cout << "f_b"  << std::endl;
			return;
		}

		// Optimization possible here. Currently the DFS does a sweep of the entire Trie
		// till range_b is reached. Rather sweep only range_a to range_b
		for (unsigned i =0; i < 128; i++)
		{
			if (this->children[i] != NULL)
			{
				//std::cout << (char)i  << std::endl;
				if (not found_a)
				{
					if (this->children[i] == range_a)
					{
						found_a = true;
						//std::cout << "f_a"  << std::endl;
					}
				}

				if (found_a && not found_b)
				{
					//this->children[i]->valid = valid;
					if (this->children[i] == range_b)
					{
						found_b = true;
						//std::cout << "f_b"  << std::endl;
						// stopping condition for dfs.
						break;
					}
				}

				this->children[i]->checkValidRange(range_a, found_a, range_b, found_b);
			}
		}
		return;
	}

	//  To pre order traversal of the Trie. Check if range_a is reached before range_b trienode and set valid bit.
	void setValidFromRangeAToRangeB(const TrieNode *range_a, bool &found_a, const TrieNode *range_b, bool &found_b , bool valid)
	{
		if (found_b)
		{
			//std::cout << "f_b"  << std::endl;
			return;
		}
		for (unsigned i =0; i < 128; i++)
		{
			if (this->children[i] != NULL)
			{
				//std::cout << (char)i  << std::endl;
				if (not found_a)
				{
					if (this->children[i] == range_a)
					{
						found_a = true;
						//std::cout << "f_a"  << std::endl;
					}
				}

				if (found_a && not found_b)
				{
					this->children[i]->valid = valid;
					if (this->children[i] == range_b)
					{
						found_b = true;
						//std::cout << "f_b"  << std::endl;
						break;
					}
				}

				this->children[i]->setValidFromRangeAToRangeB(range_a, found_a, range_b, found_b, valid);
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
	 * If the keyword is empty, returns NULL, as empty string is not a valid input string.
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
				childNode = node->addChildNode(*charIterator);
			}
			node = childNode;
			++charIterator;
		}
		//std::cout << "---" << std::endl;
		return node;
	};

	bool isKeywordValid(const std::string &keyword) const
	{
		// if empty keyword return 0
		if ( keyword.size() == 0 )
			return false;

		TrieNode *node = this->root;
		char *charIterator = (char *) keyword.c_str();

		while ( *charIterator)
		{
			//std::cout << *charIterator << std::endl;
			TrieNode *childNode = node->getChildNode(*charIterator);

			if ( childNode == NULL )
			{
				if (not node->valid) // the sub trie is invalid
					return false;

				bool leftSibling_valid = false;
				bool rightSibling_valid = false;
				//check left siblings
				for (unsigned siblingIterator = TrieNode::getIndex(*charIterator);
						TrieNode::isValidIndex(siblingIterator) && siblingIterator >= 0;
						--siblingIterator)
				{
					TrieNode *leftSibling = node->getChildNode(siblingIterator);
					if (leftSibling != NULL)
					{
						const TrieNode *prevNode = leftSibling->getRightMostNodeInSubTrie();
						if (prevNode != NULL)
							leftSibling_valid = prevNode->valid;
						break;
					}
				}

				//check right siblings
				for (unsigned siblingIterator = TrieNode::getIndex(*charIterator);
						TrieNode::isValidIndex(siblingIterator) && siblingIterator < 128 ;
						++siblingIterator)
				{
					TrieNode *rightSibling = node->getChildNode(siblingIterator);
					if (rightSibling != NULL)
					{
						const TrieNode *nextNode = rightSibling->getLeftMostNodeInSubTrie();
						if (nextNode != NULL)
							rightSibling_valid = nextNode->valid;
						break;
					}
				}

				if (rightSibling_valid && leftSibling_valid) // the prefix in valid range
					return true;
				else
					return false;
			}
			node = childNode;
			++charIterator;
		}
		// check if the keyword path led to a valid trienode
		if ( node->valid)
			return true;
		else
			return false;
	}

	// first run of DFS to check if rangeA is reached before rangeB
	bool checkValidRange(const TrieNode *range_a, const TrieNode *range_b)
	{
		bool found_a = false;
		bool found_b = false;
		this->root->checkValidRange(range_a, found_a, range_b, found_b);

		if (found_a && found_b)
			return true;
		else
			return false;
	}

	//  To pre order traversal of the Trie. Check if range_a is reached before range_b trienode and set valid bit.
	bool setValidFromRangeAToRangeB(const TrieNode *range_a, const TrieNode *range_b, bool valid)
	{
		// first run of DFS to check if rangeA is reached before rangeB
		if (this->checkValidRange(range_a, range_b))
		{
			bool found_a = false;
			bool found_b = false;

			this->root->setValidFromRangeAToRangeB(range_a, found_a, range_b, found_b, valid);
			return true;
		}
		else
			return false;
	}

	bool operationHandler(const std::string &in, bool isAdd)
	{
		// parse input. Each literal must be separated by single whitespace, like [ aaa , bbb ]
		std::stringstream str(in);
		std::string start, rangeA, comma, rangeB, end;
		str >> start >> rangeA >> comma >> rangeB >> end;
		//std::cout << "|" << start << "|" << rangeA << "|" << comma << "|" << rangeB << "|" << end << std::endl;

		bool start_is_open_set = false;
		bool end_is_open_set = true;

		// parsing the brackets.
		if (start.compare("[") == 0)
		{
			start_is_open_set = true;
		}
		else if(end.compare("(") == 0)
		{
			start_is_open_set = false;
		}
		else
		{
			return false;
		}

		if (end.compare("]") == 0)
		{
			end_is_open_set = true;
		}
		else if(end.compare(")") == 0)
		{
			end_is_open_set = false;
		}
		else
		{
			return false;
		}

		// add keywords representing the start and end ranges
		TrieNode *range_a = this->addKeyword(rangeA);
		TrieNode *range_b = this->addKeyword(rangeB);

		bool valid = isAdd;

		// a. by default, set flags like its a open set "[", "]".
		// b. But before setting flags remember the flags of two trienode.
		// c. If its closed set, restore from b.

		bool range_a_valid_flag = range_a->valid;
		bool range_b_valid_flag = range_b->valid;

		// set the valid flags.
		bool operation_passed = this->setValidFromRangeAToRangeB(range_a, range_b, valid);

		if (operation_passed)
		{
			if (not start_is_open_set)
				range_a->valid = range_a_valid_flag;

			if (not end_is_open_set)
				range_b->valid = range_b_valid_flag;
		}

		return operation_passed;
	}

	bool addKeywordRange(const std::string &in)
	{
		return this->operationHandler(in, true);
	}

	bool delKeywordRange(const std::string &in)
	{
		return this->operationHandler(in, false);
	}

	void print() const
	{
		this->root->print();
	}
};

#endif //__TRIE_H__
