#include "stdafx.h"
#include <iostream>

class PrintClass
{
public:
	/*
	static void PrintFunc(int printMe)
	{
		std::cout<<" "<<printMe;
	}*/

	template <typename T>
	static void PrintFunc(T printMe)
	{
		std::cout<<" "<<printMe;
	}
};