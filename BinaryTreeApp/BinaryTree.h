#include "stdafx.h"
#include "Node.h"
#include <iostream>

template <typename T>
class BinaryTree
{
private:
	Node<T>* m_head;
	int m_size;

	//creates a new Node, recursively loops through and adds it in
	Node<T>* BTInsert(Node<T>* m_head, const T& newVal)
	{
		//if no head node has been created yet, create one
		if (m_head == NULL)
		{
			//FOR DEBUG - std::cout<<"CREATING:"<<newVal<<" in "<<this->m_head<<std::endl;
			Node<T>* newNode = new Node<T>(newVal);;
			m_head = newNode;
		}
		//less than goes to left
		else if ( newVal < m_head->m_value )
		{
			m_head->left = BTInsert(m_head->left, newVal);
			m_head->left->parent = m_head;
		}
		//greater than goes to right
		else
		{
			m_head->right = BTInsert(m_head->right, newVal);
			m_head->right->parent = m_head;
		}

		return m_head;
	}

	//Returns the found node if one is found
	Node<T>* BTSearch(Node<T>* currentNode, T searchVal)
	{
		while(currentNode != NULL)
		{
			//Check if we've found the node
			if (currentNode->m_value == searchVal)
			{
				return currentNode;
			}
			//if the new value is lower than the current value, go left
			else if (searchVal < currentNode->m_value)
			{
				currentNode = currentNode->left;
			}
			else	//if the new value is higher than the current value, go right
			{
				currentNode = currentNode->right;
			}
		}

		return NULL;
	}

	// Finds the rightmost node on the left branch to swap, swaps the value
	// Used when two children exist for a node that we want to delete
	Node<T>* findRightmostNodeToSwap(Node<T>* head, Node<T>* remove)
	{
		//if the right most node is empty, then we have reached the right most node of the left branch
		//copy this value into the node we want to remove (delete node?)
		if (head->right == NULL)
		{
			remove->m_value = head->m_value;
			return head->left;
		}
		else
		{
			head->right = findRightmostNodeToSwap(head->right, remove);
			return head;
		}
	}

	//Unlinks the parent node if it exists
	void BTUnlinkParent(Node<T>* nodeToUnlink)
	{
		if (nodeToUnlink->parent != NULL)
		{
			//unlink the left child from the parent
			if (nodeToUnlink->parent->left == nodeToUnlink)
			{
				nodeToUnlink->parent->left = NULL;
			}
			else //unlink the right child from the parent
			{
				nodeToUnlink->parent->right = NULL;
			}
		}
	}

	//Takes in a parent and child, links the parent to the child
	void BTLinkToParent(Node<T>* child, Node<T>* node)
	{
		//Don't link if the parent and grandparent don't exist
		if (node != NULL && node->parent != NULL)
		{
			//if the node is on the left of the parent
			if (node->parent->left == node)
			{
				node->parent->left = child;

				//Can link a parent to null child, but not null child to parent
				if (child != NULL)
				{
					child->parent = node->parent;
				}
			}
			else	//node is on the right of the parent
			{
				node->parent->right = child;

				//Can link a parent to null child, but not null child to parent
				if (child != NULL)
				{
					child->parent = node->parent;
				}
			}
		}
	}

	//Returns the leftmost node (smallest value node) given a head
	Node<T>* BTFindFurthestNode(Node<T>* head, bool goingLeft)
	{
		//We've gone as far as we can go down the left
		if ( (head->left == NULL  && goingLeft )   ||
			 (head->right == NULL && !goingLeft)	)
		{
			return head;
		}
		else
		{
			//keep going left or right
			if (goingLeft)
			{
				BTFindFurthestNode(head->left, goingLeft);
			}
			else
			{
				BTFindFurthestNode(head->right, goingLeft);
			}
		}
	}

	//Removes a deleted node from memory, updates size and head node if necessary
	void BTDelete(Node<T>* delNode)
	{
		//FOR DEBUG - std::cout<<"DELETE:"<<delNode->m_value<<" in "<< m_head <<std::endl;

		if (delNode == m_head)	//reassign the head and delete
		{
			//Set the parent to the left node if it exists
			if (delNode->left != NULL)
			{
				m_head = delNode->left;
				m_head->parent = NULL;
				
				delete delNode;
			}
			else if (delNode->right != NULL)
			{
				//Set parent to the right node if it exists and there's no left node
				m_head = delNode->right;
				m_head->parent = NULL;

				delete delNode;
			}
			else	//if that was the only node in the tree, set it to NULL after deleting
			{
				delete delNode;

				m_head = NULL;
			}
		}
		else	//regular node deletion . . . just delete it
		{
			delete delNode;
		}

		//always update size when we delete a node
		m_size--;
	}

	//Traverse the whole binary tree and execute the supplied function at each node
	void BTTraverse(Node<T>* node, void (*function)(T) )
	{
		if (node != NULL)
		{
			BTTraverse(node->left, function);
			//Execute supplied function for node
			function(node->m_value);
			BTTraverse(node->right, function);
		}
		else
		{
			return;
		}
	}

	//Starts at smallest, traverses through whole tree looking for index.  nodeCount should always be declared zero
	Node<T>* BTTraverseInOrderTo(Node<T>* node, const int& index, int& nodeCount) const
	{
		Node<T>* returnMe = NULL;
		if (index < GetSize() && index >= 0)
		{
			if (node != NULL)
			{
				returnMe = BTTraverseInOrderTo(node->left, index, nodeCount);
				
				//If we've already found the value, stop recursing and return it
				if (returnMe != NULL)
				{
					return returnMe;
				}
				//If this is the value, return it
				else if (nodeCount == index)
				{
					return node;
				}
				nodeCount++;

				returnMe = BTTraverseInOrderTo(node->right, index, nodeCount);
			}
			else	//node we're examining is NULL
			{
				return returnMe;
			}
		}

		return returnMe;
	}

	//Starts at head, traverses through whole tree looking for index.  nodeCount should always be declared zero
	Node<T>* BTTraversePreOrderTo(Node<T>* node, const int& index, int& nodeCount) const
	{
		Node<T>* returnMe = NULL;
		if (index < GetSize() && index >= 0)
		{
			if (node != NULL)
			{
				//If we've already found the value, stop recursing and return it
				if (returnMe != NULL)
				{
					return returnMe;
				}
				//If this is the value, return it
				else if (nodeCount == index)
				{
					return node;
				}
				nodeCount++;

				returnMe = BTTraversePreOrderTo(node->left, index, nodeCount);

				//if we've already found the value, stop recursing
				if (returnMe == NULL)
				{
					returnMe = BTTraversePreOrderTo(node->right, index, nodeCount);
				}
			}
			else	//node we're examining is NULL
			{
				return returnMe;
			}
		}

		return returnMe;
	}

	//Creates a new node in current tree for each value stored in src
	void BTCopyValuesFromTree(const BinaryTree& src)
	{
		//Copy each value from the src tree into the current tree
		for (int i = 0; i < src.GetSize(); ++i)
		{
			T newVal = src.GetAt(i, PRE_ORDER);
			Insert(newVal);
		}
	}

	//Deletes all nodes in the tree
	void BTDeleteAllNodes()
	{
		while (GetSize() > 0 && m_head != NULL)
		{
			//Find a node
			Node<T>* delNode = BTFindFurthestNode(m_head, false);

			//Delete
			Delete(delNode->m_value);
		}
	}

public:

	enum traversalType {IN_ORDER, PRE_ORDER};

	T GetHead()
	{
		if (m_head != NULL)
		{
			return m_head->m_value;
		}
		else
		{
			throw std::string("NO VALUE FOUND");
		}
	}

	//constructors
	BinaryTree()						//default constructor, no nodes
	{
		m_head = NULL;
		m_size = 0;
	}				
	BinaryTree(T initVal)				//construct BT with first node
	{
		//initialize the head node to the value passed in
		//FOR DEBUG - std::cout<<"CREATING:"<<initVal<<" in "<<this->m_head<<std::endl;
		m_head = new Node<T>(initVal);
		m_size = 1;
	}		
	BinaryTree (const BinaryTree& src)	//copy constructor
	{
		m_head = NULL;
		m_size = 0;

		BTCopyValuesFromTree(src);
	}
	//destructor - deletes all nodes starting from the smallest
	~BinaryTree()
	{
		BTDeleteAllNodes();
	}

	//assignment operator
	BinaryTree& operator=(const BinaryTree& rhs)
	{
		//ignore self assignments
		if (this == &rhs)
		{
			return (*this);
		}

		//delete old binary tree
		BTDeleteAllNodes();

		//create new binary tree
		BTCopyValuesFromTree(rhs);

		return *this;
	}

	//allow the addition of binary trees - add all nodes from rhs into lhs (this)
	const BinaryTree operator+ (const BinaryTree& rhs)
	{
		//create a copy of the LHS in newTree
		BTCopyValuesFromTree(rhs);

		return *this;
	}

	//Get a particular value at the specified index
	T GetAt(int index, const traversalType trvTyp) const
	{
		Node<T>* retNode = NULL;
		int stupid = 0;

		if (trvTyp == IN_ORDER)
		{
			retNode = BTTraverseInOrderTo(m_head, index, stupid);
		}
		else
		{
			retNode = BTTraversePreOrderTo(m_head, index, stupid);
		}

		return retNode->m_value;
	}

	//Looks for a value in the binary tree
	T& Search(T newVal)
	{
		Node<T>* foundNode = BTSearch(m_head, newVal);

		if (foundNode == NULL)
		{
			throw std::string("NO VALUE FOUND");
		}

		return foundNode->m_value;
	}

	//User just provides a value he or she wants to add
	void Insert(T newVal)
	{
		m_head = BTInsert(m_head, newVal);
		m_size++;
	}

	//Gets the biggest node in the tree
	T GetBiggest()
	{
		int retVal = 0;
		Node<T>* biggest = NULL;
		
		if (NULL != m_head)
		{
			biggest = BTFindFurthestNode(m_head, false);
		}

		if (biggest != NULL)
		{
			retVal =  biggest->m_value;
		}
		return retVal;
	}

	//Gets the smallest node in the tree
	T GetSmallest()
	{
		int retVal = 0;
		Node<T>* smallest = NULL;

		if (NULL != m_head)
		{
			smallest = BTFindFurthestNode(m_head, true);
		}

		if (smallest != NULL)
		{
			retVal = smallest->m_value;
		}
		return retVal;
	}

	//User just provides a value to delete, returns true if it deleted properly
	bool Delete(const T& delVal)
	{
		//Find nodeToDelete
		Node<T>* nodeToDelete = BTSearch(m_head, delVal);

		if (nodeToDelete != NULL)
		{
			//case where there's no child - just call delete, parent will be linked to null
			if (nodeToDelete->left == NULL && nodeToDelete->right == NULL)
			{
				//unlink the parent
				BTUnlinkParent(nodeToDelete);

				//delete Node
				BTDelete(nodeToDelete);
			}
		
			//case where there's only one child - relink child and delete
			// - either the parent.left or the parent.right == nodeToDelete
			// - link in nodeToDelete.left or .right (whichever is not null) to parent.left or .right
			else if ( (nodeToDelete->left != NULL && nodeToDelete->right == NULL) ||
					  (nodeToDelete->right != NULL && nodeToDelete->left == NULL) )
			{
				Node<T>* childToRelink = NULL;
				if (nodeToDelete->left != NULL)
				{
					childToRelink = nodeToDelete->left;
				}
				else
				{
					childToRelink = nodeToDelete->right;
				}

				//link the child to the parent
				BTLinkToParent(childToRelink, nodeToDelete);

				//Delete node
				BTDelete(nodeToDelete);
			}

			//case where there are two children
			//- find the leftmost node of the right side (swapNode)
			//- copy VALUE of this swapNode to the node we want to delete
			//- swapNode can have a right child, but not a left child (he's the left most).  If no child, just delete this node.
			//- if swapNode has a child, relink the child to nextNumNode's parent, then delete swapNode
			else
			{
				Node<T>* swapNode = BTFindFurthestNode(nodeToDelete->right, true);
				nodeToDelete->m_value = swapNode->m_value;
				BTLinkToParent(swapNode->right, swapNode);
				
				//delete Node
				BTDelete(swapNode);
			}
		}

		return false;
	}

	void ExecuteForEachNode(void (*function)(T) )
	{
		BTTraverse(m_head, function);
	}

	const int& GetSize() const
	{
		return m_size;
	}
};