/***********************************************************************

		PROGRAM HEADER 

************************************************************************
* 
* 	Author: Dwight Goins
* 	TOTAL POINTS:  25
* 	DUE DATE:  01/17/2021
* 	COURSE:  COP 3530
* 	Assignment Name:  Assignment#1
* 	Professor:  Dr. Bullard
* 	Description:  The program manages a dynamic array of records.
*   Z#: xx2589
* 
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "state.h"

using namespace std;



int main()
{
	std::cout << "**************************************************************\n";
	std::cout << "TEST 1:  Testing the default constructor, Is_Full, double_size, and Print_ALL\n\n";
	state_class S;
	S.Print_ALL();
	std::cout << "***********************************************************************************\n";
	std::cout << "END OF TEST 1:\n";
	std::cout << "***********************************************************************************\n";
	std::cout << endl << endl << endl;


	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 2:  Testing the Remove, Is_Empty, Search, and Print_ALL\n\n";
	S.Remove("Alabama");
	S.Remove("Florida");
	S.Remove("Wyoming");
	S.Print_ALL();
	std::cout << "***********************************************************************************\n";
	std::cout << "END OF TEST 2:\n";
	std::cout << "***********************************************************************************\n";
	std::cout << endl << endl << endl;

	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 3 Testing operator+, Is_Full, double_size, and Print_ALL\n\n";
	population_record r;
	r.state_name = "Alabama";
	r.population = 1111111;
	S + r;
	r.state_name = "Florida";
	r.population = 99999999;
	S + r;
	r.state_name = "Wyoming";
	r.population = 222222;
	S + r;
	S.Print_ALL();
	std::cout << "***********************************************************************************\n";
	std::cout << "END OF TEST 3: \n";
	std::cout << "***********************************************************************************\n";
	std::cout << endl << endl << endl;


	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 4:  Testing Print_Range\n\n";
	int min = 500000, max = 1500000;
	std::cout << "List of States with Population Sizes between " << min << " and " << max << " inclusive "<<endl << endl;
	S.Print_Range(min, max);
	std::cout << "***********************************************************************************\n";
	std::cout << "END OF TEST 4:\n";
	std::cout << "***********************************************************************************\n";
	std::cout << endl << endl << endl;

	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 5:  Testing State_Count\n\n";
	min = 500000;
	max = 1500000;
	std::cout << "Number of States with Population Sizes between " << min << " and " << max << " (inclusive) equals " << S.State_Count(min, max) << endl;
	std::cout << "***********************************************************************************\n";
	std::cout << "END OF TEST 5:\n";
	std::cout << "***********************************************************************************\n";

	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 6:  copy constructor and Print_ALL\n\n";
	state_class New = S;
	New.Print_ALL();
	std::cout << "END OF TEST 6:\n";
	std::cout << "***********************************************************************************\n";
	
	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 7:  Sort by alphabet and Print_ALL\n\n";
	New.Sort(false);
	New.Print_ALL();
	std::cout << "END OF TEST 7:\n";
	std::cout << "***********************************************************************************\n";
	

	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 7:  Sort by Population and Print_ALL\n\n";
	New.Sort(true);
	New.Print_ALL();
	std::cout << "END OF TEST 7:\n";
	std::cout << "***********************************************************************************\n";


	std::cout << "***********************************************************************************\n";
	std::cout << "TEST 8:  Print_ALL_To_File\n\n";
	New.Print_ALL_To_File("state_data_update.txt");
	std::cout << "END OF TEST 8:\n";
	std::cout << "***********************************************************************************\n";

	return 0;
}
