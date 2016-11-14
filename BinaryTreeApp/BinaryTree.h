#include "stdafx.h"
#include "Node.h"
#include <iostream>

template <typename T>
class BinaryTree
{
private:
	Node<T>* m_head;

	static int m_size;

	//creates a new Node, recursively loops through and adds it in
	Node<T>* BTInsert(Node<T>* m_head, T newVal)
	{
		Node<T>* newNode = new Node<T>(newVal);

		//if no head node has been created yet, create one
		if (m_head == NULL)
		{
			m_head = newNode;
		}
		//less than goes to left
		else if ( newNode->m_value < m_head->m_value )
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

	Node<T>* BTDelete(Node<T>* head, T remove)
	{
		//Can't search if there's no tree to search
		if (head == NULL)
		{
			return NULL;
		}
		//We've found the node that should be removed
		else if (head->m_value == remove)
		{
			//If there's no left node, return the right node.  This will replace what we're deleting
			if (head->left == NULL)
			{
				return head->right;
			}
			//if there's no right node, return the left node.  This will replace what we're deleting
			else if (head->right == NULL)
			{
				return head->left;
			}
			//Case where there are two children we find the right most node under the left branch
			else
			{
				head->left = findRightmostNodeToSwap(head->left, head);
				return head;
			}
		}
		else
		{
			//Not at the node we want to delete yet, keep traversing the tree
			//if the value we want to remove is smaller than the value we're currently at, go left
			if (remove < head->m_value)
			{
				head->left = BTDelete(head->left, remove);
			}
			else	//otherwise go right
			{
				head->right = BTDelete(head->right, remove);
			}
		}
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
	void BTRemoveNodeFromMemory(Node<T>* delNode)
	{
		if (delNode == m_head)
		{
			//Set the parent to the left node if it exists
			if (delNode->left != NULL)
			{
				m_head = delNode->left;
			}
			else if (delNode->right != NULL)	//Otherwise set parent to the right node
			{
				m_head = delNode->right;
			}
			else	//if that was the only node in the tree, m_head doesn't exist
			{
				m_head = NULL;
			}
		}

		delete delNode;
		m_size--;
	}

public:

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

	//constructor
	BinaryTree()
	{
		m_head = NULL;
	}
	BinaryTree(T initVal)
	{
		//initialize the head node to the value passed in
		m_head = new Node<T>(initVal);
		m_size++;
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
	bool Delete(T delVal)
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
				BTRemoveNodeFromMemory(nodeToDelete);
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
				BTRemoveNodeFromMemory(nodeToDelete);
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
				BTRemoveNodeFromMemory(swapNode);
			}
		}

		return false;
	}

	void TraverseandPrint()
	{
		Traverse(m_head);
	}

	void Traverse(Node<T>* node)
	{
		if (node != NULL)
		{
			Traverse(node->left);
			Print(node->m_value);
			Traverse(node->right);
		}
		else
		{
			return;
		}
	}

	void Print(const T& printMe)
	{
		std::cout<<" "<<printMe;
	}

	int GetSize()
	{
		return m_size;
	}
};

template <typename T>
int BinaryTree<T>::m_size = 0;