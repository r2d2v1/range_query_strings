Range Query on Strings 
Vijay Rajakumar

mail@vijayrajakumar.com

1. Maintain the range sets in a Trie.  At each TrieNode, maintain if the Node and subTrie is valid.

2. ADD:For a given range [R_a, R_b]
a. add keywords R_a and R_b.
b. Then, do a pre-order traversal from R_a to R_b and set all nodes to valid.

3. DELETE: For a given range [R_a, R_b]
a. add keywords R_a and R_b. If keywords all ready exist, no op.
b. Then, do a pre-order traversal from R_a to R_b and set all nodes to invalid.

4. CHECK VALID:
a. For a given keyword, get the largest prefix already in the Trie.
b. Check if all the TrieNodes representing the "path of this largest prefix" are valid.

5. Open Set and Close set. 
a. [,( condition belongs Range_Start.  ],) belongs to Range_End.
b. Condition can be put into the Trie, in the pre-order traversal steps 2b and 3b.
