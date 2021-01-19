
#include "state.h"
#include <iomanip>  //need to use formatting manipulators
#include <string>

using namespace std;
/***********************

FUNCTION HEADER

******************************************************************************************************************
Name:  Default Constructor
Pre-Conditon: The count, capacity, and the dynamic array (pop_DB) have not been initialized.
Post-Condition: The count, capacity, and the dynaic array (pop_DB) have been initialized.
Description:  The function initiailizes the state (private data) of the class state_class. It reads the data stored in the datafile "census2020_data.txt"
			  into the dynamic array, pop_DB.  Initially, count is set to 0, capacity to 5, and pop_DB is allocated 5 cells.  If pop_DB become full,
			  double_size is called, which doubles the capacity of pop_DB.

**********************************************************************************************************************************************************/
state_class::state_class()
{
	//intially count, capacity, and pop_DB are initialized with the following values:
	count = 0;
	capacity = 5;
	pop_DB = new population_record[capacity];

	population_record p_record;	//purchase order record
	ifstream in;    //declaring an input file stream
	bool checkInputFile = false;	//flag to test for valid input file

	// Open the data file from the current directory
	in.open("census2020_data.txt");

	// check to make sure there was no error opening file
	checkInputFile = in.fail();

	if (checkInputFile)
	{
		std::cout << "Input file did not open correctly" << endl;
		return;
	}


	// We have no errors in the input or output so let's process the file
	// we look through the input file until end-of-file marker
	while (!in.eof())
	{
		//Populate a customer PO Record one line at a time

	/*
		reads the fields
			1) State Name
			2) Population

	*/
		string line;
		getline(in, line);
		int arrSize = 0;
		string * data = splitStatePopulation(line, &arrSize);
		//in >> p_record.state_name;
		//in >> p_record.population;
		p_record.state_name = data[0];
		p_record.population = (double)atoi(data[1].c_str());

		//auto arraySize = getSize(pop_DB);
		if (Is_Full())
			double_size();
		pop_DB[count] = p_record;
		count++;
	}
	in.close();


}


/*****************************************************************************************/
//Name: copy constructor
//Precondition: must have a valid copy reference
//Postcondition: 
//Decription: Reads the data file of population info, 
//pop_DB. If the count become equal to the size the function double_size is called and the memory allocated to pop_DB is doubled.
/**********************************************************************************/
state_class::state_class(const state_class& toCopy)
{		
	std::cout << "copy constructor has been called\n";
	count = toCopy.count;
	capacity = toCopy.capacity;

	// must first initialize 
	pop_DB = new population_record[capacity];
	copyArray(toCopy.pop_DB, capacity, pop_DB);
}

/******************************************************************************************************************************************************
Name: Destructor
Pre-Condition: n/a
Post-Condition pop_DB and other member fields are deallocated
Description: de-allocates all memory allocated to pop_DB.  This should be the last function to be called before the program
//            is exited.
******************************************************************************************************************************************************/
state_class::~state_class()
{	
	pop_DB = { 0 };
	count = 0;
	capacity = 0;
	delete[] pop_DB;
}



/******************************************************************************************************************************/
//Name: double_size
//Precondition: pop_DB is initialized, and has a size > 0
//Postcondition: 
//Decription: doubles the size (capacity) of pop_DB
/******************************************************************************************************************************/
void state_class::double_size()
{
	_ASSERT(pop_DB != NULL);
	_ASSERT(capacity > 0);

	capacity *= 2;
	population_record* temp = new population_record[capacity];

	for (int i = 0; i < count; i++)
	{
		temp[i] = pop_DB[i];
	}

	delete[] pop_DB;
	pop_DB = temp;
}

/******************************************************************************************************************************************************
Name: Add Operator
Pre-Condition: pop_DB must be a valid initialized array
Post-Condition: adds a new entry into the pop_DB array
Description: Add operator overload which adds a new population_record to the array
******************************************************************************************************************************************************/
void state_class::operator+(const population_record& r)
{
	_ASSERT(pop_DB != NULL);

	//place your code here
	// first check for the size
	if (count >= capacity)
	{
		double_size();
	}

	// now create a new record and ask for entries
	population_record newRecord;

	if (r.state_name.empty())
	{
		std::cout << "Please enter in a State:";
		cin >> newRecord.state_name;
	}
	else
	{
		newRecord.state_name = r.state_name;
	}
	
	newRecord.population = r.population;

	// save it to the new element
	pop_DB[count] = newRecord;
	count++;
}


/**********************************************************************************************************************************/
//Name: search
//Precondition: PopulationRecordPtr array filled with valid record entries, the count of elements in the array, and a state to search for 
//Postcondition: returns the index number of the found item in the array, otherwise returns -1
//Decription: locates key in pop_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int state_class::Search(const string& key)
{
	_ASSERT(pop_DB != NULL);

	for (int i = 0; i < count; i++)
	{
		
		if (pop_DB[i].state_name == key )
		{
			return i;
		}
	}
	return -1;
}



/********************************************************************************************************************************/
//Name: Remove
//Precondition: PopulationRecordPtr is a valid population_record array, count is the total number of elements in the array, key is the state name to do a lookup and remove.
//Precondition: Valid initialized pop_DB Array
//Postcondition: Removes the found state from the array and decrements the array count
//Decription: remove all occurences of key from pop_DB if it is there.
/*******************************************************************************************************************************/
void state_class::Remove(const string &state)
{
	_ASSERT(pop_DB != NULL);

	int loc = Search(state);
	if (loc != -1)
	{
		for (int j = loc; j < count - 1; j++)
		{
			pop_DB[j] = pop_DB[j + 1];
		}
		count--;
	}
}


/******************************************************************************************************************************************************
Name: Print_ALL_To_File	
Pre-Condition: valid file name to print to
Post-Condition: 
Description: Prints all the states and populations to a file
******************************************************************************************************************************************************/
void state_class::Print_ALL_To_File(const string& filename)
{
	
	//place your code here
	std::cout.setf(ios::fixed);
	std::cout.setf(ios::showpoint);
	std::cout.precision(2);

	ofstream fout;
	bool checkOutputFile = false;	//flag to test for valid input file

	// Open the data file from the current directory
	fout.open(filename);

	// check to make sure there was no error opening file
	checkOutputFile = fout.fail();

	if (checkOutputFile)
	{
		std::cout << "Output file did not open correctly" << endl;
		//return;
	}

	auto _count = 0;
	fout << "***********************************************************************\n\t\tStateName:\tPopulation:\n***********************************************************************\n";
	// Loop through all items in the array
	for (int i = 0; i < count; i++)
	{

		/*
		(The output is in the following order:
		statename population
		*/
		auto p_record = pop_DB[i];

		fout << setw(25)
			<< p_record.state_name << "\t"
			<< setw(5)
			<< (int)p_record.population << "\t"
			<< endl;
		_count++;
	}

	fout << "***********************************************************************" << endl
		<< "\tTotal Records: " << _count << endl
		<< "***********************************************************************" << endl;



	fout.close();
}
/******************************************************************************************************************************************************
Name: Print_ALL
Pre-Condition: n/a
Post-Condition: n/a
Description: Prints all the states names and population to the console
******************************************************************************************************************************************************/
void state_class::Print_ALL()
{
	//place your code here
	print(0, 0);
}


/******************************************************************************************************************************************************
Name: Print_Range
Pre-Condition: valid Minimum and Maximum values to print, pop_DB must be initialized and valid
Post-Condition: n/a
Description: Prints a range of state names and populations with Population Sizes between minimum and maximum (inclusive)
******************************************************************************************************************************************************/
void state_class::Print_Range(const int min, const int max)
{
	auto _count = 0;
	std::cout.setf(ios::fixed);
	std::cout.setf(ios::showpoint);
	std::cout.precision(2);

	for (int i = 0; i < count; i++)
	{
		auto p_record = pop_DB[i];
		if ((p_record.population > (double)min) 
			&& (p_record.population <= (double)max))
		{
			std::cout << setw(25)
				<< p_record.state_name << "\t"
				<< setw(5)
				<< (int)p_record.population << "\t"
				<< endl;
			_count++;
		}
	}

	std::cout << " *************************************************** " << endl
		<< "\tTotal Records: " << _count << endl
		<< " *************************************************** " << endl;
}


/******************************************************************************************************************************************************
Name: State_Count
Pre-Condition: valid Minimum and Maximum values to print, pop_DB must be initialized and valid
Post-Condition: n/a
Description: return the number of state names with Population Sizes between minimum and maximum (inclusive)
********************************************************************************************************************************************************/
int state_class::State_Count(const int min, const int max)
{
	//place your code here
	auto _count = 0;
	
	for (int i = 0; i < count; i++)
	{
		auto p_record = pop_DB[i];
		if ((p_record.population > (double)min)
			&& (p_record.population <= (double)max))
		{
			_count++;
		}
	}

	return _count;
}

/******************************************************************************************************************************************************
Name: Sort
Pre-Condition: pop_DB is initialized and valid
Post-Condition: pop_DB is sorted in alphabetical order or by population size
Description: 
******************************************************************************************************************************************************/
void state_class::Sort(bool byPopulation = false)
{
	//place your code here
	if (!byPopulation)
	{
		sortByState();
	}
	else
	{
		sortByPopulation();
	}
}


/******************************************************************************************************************************************************
Name: SortByState
Pre-Condition: pop_DB is initialized and valid
Post-Condition: pop_DB is sorted in alphabetical order by state name ascending
Description: Bubble sorts the pop_DB array in alphabetical order by state name ascending
******************************************************************************************************************************************************/
void state_class::sortByState()
{
	bool swap = false;
	population_record temp;

	do
	{
		swap = false;
		for (int i = 0; i < count; i++)
		{
			for (int j = i+1; j < count; j++)
			{
				if (pop_DB[i].state_name > pop_DB[j].state_name)
				{
					//swap
					swap = true;
					temp = pop_DB[i];
					pop_DB[i] = pop_DB[j];
					pop_DB[j] = temp;
				
				}

				if (swap) break;
			}

			if (swap) break;
		}
	} while (swap);
}

/*****************************************************************************
Name: SortByPopulation
Pre-Condition: pop_DB is initialized and valid
Post-Condition: pop_DB is sorted by population size ascending
Description: Bubble Sorts the pop_DB array by population size ascending
******************************************************************************************************************************************************/
void state_class::sortByPopulation()
{
	bool swap = false;
	population_record temp;

	do
	{
		swap = false;
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (pop_DB[i].population  > pop_DB[j].population)
				{
					//swap
					swap = true;
					temp = pop_DB[i];
					pop_DB[i] = pop_DB[j];
					pop_DB[j] = temp;

				}

				if (swap) break;
			}

			if (swap) break;
		}
	} while (swap);
}

/*******************************************************************************************/
//Name: print
//Precondition: valid PopulationRecordPtr array, optionally valid minimum/maximum range of the count of the total number of elements in the array
//Postcondition: prints /displays all the records to the console.
//Decription: prints every field of every order_record in INV formatted to the screen.
/***************************************************************************************************************************/
void state_class::print(const int min=0, const int max=0)
{
	std::cout.setf(ios::fixed);
	std::cout.setf(ios::showpoint);
	std::cout.precision(2);
		
	/********************************************/
	//check for min and max values
	auto _min = min;
	auto _max = max;
	auto _count = 0;
	if (_min <= 0 && _max <= 0)
	{
		_max = count;
	}
		int i = 0;

		std::cout << "\tStateName:\t\tPopulation:\n";
		// Loop through all items in the array
		for (i = _min; i < _max; i++)
		{

			/*
			(The output is in the following order: 
			statename population
			*/
			auto p_record = pop_DB[i];

			std::cout << setw(25)
				<< p_record.state_name << "\t"
				<< setw(5)
				<< (int)p_record.population << "\t"
				<< endl;
			_count++;
		}

		std::cout << " *************************************************** " << endl
			<< "\tTotal Records: " << _count << endl
			<< " *************************************************** " << endl;
	
}


/****************************************************************************************************************************/
//Name: getSize
//Precondition: valid order_record array with at least 1 entry.
//Postcondition: returns the number of elements in the array based on the byte size of the array
//Decription: gets the length of the INV array
//            is exited.
/***************************************************************************************************************************/
int state_class::getSize(const population_record record[])
{
	return  (sizeof(record) / sizeof(record[0])) | 1;
}



/******************************************************************************************************************************/
//Name: CopyArray
//Precondition: source Order_record array must be valid and contain at least 1 order record element. Destination array must be a valid order_record empty array big enough to hold all the elements from the source. size is the number of elements in the source array.
//Postcondition: Source array elements are copied into destination array elements with the exact same indices
//Decription: doubles the size (capacity) of INV
/******************************************************************************************************************************/
void state_class::copyArray(const population_record src[], int size, PopulationRecordPtr& dest)
{
	for (int i = 0; i < size; i++)
	{
		memcpy(&dest[i], &src[i], sizeof(population_record));
	}
}


/****************************************************************************************************************************/
//Name: splitStatePopulation
//Precondition: a line containing spaces representing State Name and population values
//Postcondition: returns an array of the State Name and the Population, size of the array
//Decription: takes a line containing state names and spaces and splits it into an array of the state name and population.
/***************************************************************************************************************************/

string* state_class::splitStatePopulation(const string& line, int* size)
{

	_ASSERT(size != NULL);
	string* result = new string[2];
	*size = 2;

	const char * cstr = line.c_str();
	auto strSize = line.length() ;

	char* str =  (char*)calloc(strSize, sizeof(char));
	for (size_t i = 0; i < strSize; i++)
	{
		memcpy(&str[i], &cstr[i], sizeof(char));
	}
	//terminate string
	str[strSize] = '\0';

	const char* delim = " ";
	char* next_token;
	char * token = strtok_s(str,  delim, &next_token);
	int tokenCount = 0;

	while (token) {
		// check to see if string
		// converts to a number
		auto population = atoi(token);
		if (population > 0)
		{
			// string converts to a number so set that in the population
			result[1] = string(token);
		}
		else
		{
			// string doesn't conver to a number so we
			// need a way to get all the tokens and set that
			// to the string of the first element
			// of result - so let's first count how many
			tokenCount++;
			
		}
		token = strtok_s(NULL, delim, &next_token);
	}

	// now we know how many so let's do it again 
	// reset the str value:	
	str = (char*)calloc(strSize, sizeof(char));
	for (size_t i = 0; i < strSize; i++)
	{
		memcpy(&str[i], &cstr[i], sizeof(char));
	}
	str[strSize] = '\0';

	// let's get the token again
	token = strtok_s(str, delim, &next_token);
	string* tokensToCatenate = new string[tokenCount];
	size_t* phraseLengths = new size_t[tokenCount];

	tokenCount = 0;
	while (token) {
		// check to see if string
		// converts to a number
		auto population = atoi(token);
		if (population == 0)
		{
			tokensToCatenate[tokenCount] = token;
			auto s = string(token);
			phraseLengths[tokenCount] = s.length() ;

			tokenCount++;
			
		}
		token = strtok_s(NULL, delim, &next_token);
	}
	
	// now let's rebuild the state name 
	int stateNameSize = 0;
	for (int i = 0; i < tokenCount; i++)
	{
		// first let's get the size of the string for the state name
		stateNameSize += phraseLengths[i] ;
	}

	stateNameSize += tokenCount-1;
	char* stateName = new char[stateNameSize];

	// index count
	auto ndxcount = 0;

	// now let's build the actual state name
	for (int i = 0; i < tokenCount; i++)
	{
		// first let's get the size of the string for the state name
		auto phrase = tokensToCatenate[i];
		auto prevSize = i == 0 ? 0: phraseLengths[i - 1];
		auto size = phraseLengths[i];
		for (size_t j = 0; j < size; j++)
		{
			stateName[ndxcount++] = phrase[j];
		}
		stateName[ndxcount++] = ' ';
	}

	stateName[stateNameSize] = '\0';
	string s_stateName = string(stateName);
	result[0] = s_stateName;

	return result;
}