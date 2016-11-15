// BinaryTreeApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Print.h"
#include "BinaryTree.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	//create a function pointer for printing
	void (*printFP)(int);
	printFP = &PrintClass::PrintFunc<int>;		//instantiate the print function so that the template code is created to avoid linking errors

	//randomize our results
	srand (time(NULL));
	int newVal = rand()%100;		//new random value from 0 - 99, will first be used as head node
	int midVal;

	//create a new binary tree on the stack
	BinaryTree<int> testTree(newVal);
	std::cout<<"Creating binary tree with: "<<newVal<<std::endl;

	//fill binary tree with 100 random numbers
	for (int i = 0; i<100; i++)
	{
		newVal = rand()%100;
		testTree.Insert( newVal );
		std::cout<<"Adding: "<<newVal<<std::endl;
		
		//Randomly select a value in the middle for use later
		if (i == 50)
		{
			midVal = newVal;
		}
	}

	//Size should be 101 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl<<std::endl;
	std::cout<<"Head of tree is  "<<testTree.GetHead()<<std::endl;
	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	std::cout<<"BST: ";
	testTree.ExecuteForEachNode(printFP);
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
	testTree.ExecuteForEachNode(printFP);
	std::cout<<std::endl;

	std::cout<<"Let's delete: "<< newVal <<std::endl;
	testTree.Delete(newVal);

	//Size should be 99 at this point
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.ExecuteForEachNode(printFP);
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
	testTree.ExecuteForEachNode(printFP);
	std::cout<<std::endl;

	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	testTree.Insert(1);
	std::cout<<"Tree currently has "<<testTree.GetSize()<<"Nodes"<<std::endl;
	std::cout<<"BST: ";
	testTree.ExecuteForEachNode(printFP);
	std::cout<<std::endl;

	std::cout<<"Biggest Node: "<<testTree.GetBiggest()<<"  Smallest Node: "<<testTree.GetSmallest()<<std::endl;

	system("pause");

	return 0;
}

