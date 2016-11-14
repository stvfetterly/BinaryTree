// BinaryTreeApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	//srand (time(NULL));

	//create a new binary tree on the stack
	int newVal = rand()%100;
	//int newVal = 20;
	int midVal;
	BinaryTree<int> testTree(newVal);

	//Tree created successfully
	std::cout<<"Creating binary tree with: "<<newVal<<std::endl;


	//fill binary tree with 100 random numbers
	for (int i = 0; i<100; i++)
	{
		newVal = rand()%100;
		/*newVal = newVal + (2*i) + 5;
		if (i%2)
		{
			newVal = newVal - (i*i);
		}*/
		testTree.Insert( newVal );
		std::cout<<"Adding: "<<newVal<<std::endl;
		if (i == 5)
		{
			midVal = newVal;
		}
	}

	//Size should be 11 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl<<std::endl;
	std::cout<<"Head of tree is  "<<testTree.GetHead()<<std::endl;
	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	std::cout<<"BST: ";
	testTree.TraverseandPrint();
	std::cout<<std::endl;

	//Test for a search that probably won't work
	try
	{
		std::cout<<"Looking for "<<35<<std::endl;

		int foundVal = testTree.Search(35);
		std::cout<<"Found "<<foundVal<<std::endl;
	}
	catch (const std::string& e)
	{
		std::cout<<e<<std::endl;
	}

	//Test for a search that definately will work
	try
	{
		std::cout<<"Looking for "<<newVal<<std::endl;

		int foundVal = testTree.Search(newVal);
		std::cout<<"Found "<<foundVal<<std::endl;
	}
	catch (const std::string& e)
	{
		std::cout<<e<<std::endl;
	}

	std::cout<<"Let's delete: "<< midVal <<std::endl;
	testTree.Delete(midVal);

	//Size should be 100 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.TraverseandPrint();
	std::cout<<std::endl;

	std::cout<<"Let's delete: "<< newVal <<std::endl;
	testTree.Delete(newVal);

	//Size should be 99 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.TraverseandPrint();
	std::cout<<std::endl;

	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	//Loop through all entries in the tree and delete from the biggest to smallest
	for (int i = testTree.GetSize(); i > 0; i--)
	{
		int delVal = testTree.GetBiggest();
		testTree.Delete( delVal );
		std::cout<<"Deleting: "<<delVal<<std::endl;
	}

	//Size should be 0 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.TraverseandPrint();
	std::cout<<std::endl;

	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	testTree.Insert(1);
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.TraverseandPrint();
	std::cout<<std::endl;

	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	system("pause");
	return 0;
}

