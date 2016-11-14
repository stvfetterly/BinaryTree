#include "stdafx.h"

template <typename T>
class Node
{
public:
	T m_value;
	Node* left;
	Node* right;
	Node* parent;

	//constructor
	Node()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	Node(T initVal)
	{
		m_value = initVal;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};
