// Implementation file for AVL search tree

#include "Dictionary.h"
#include<cmath>
#include <algorithm>
#include <vector>
#include <array>
#include <iostream>

//implement a prime number generator for table size
const int startSize = 7;
static int slotsFilled = 0;
static string* table = new string[startSize];
static int size;

static vector<string> temp;
int tableResize(int tablesize)
{
	cout << "Resizing table";
	tablesize = tablesize *2;
		for(int i = 2; i < tablesize; i++)
		{
				if(tablesize % i == 0) //if our new size isn't prime, increment
				{
					tablesize++;
					i = 1;
				}
		}
		slotsFilled = 0; //Reset the slots filled
		string* tempTable;
		tempTable = new string[tablesize];  //create a temporary table and initialize each value.
		for (int i = 0; i < tablesize; i++)
		{
			tempTable[i] = " ";
		}
		while (!temp.empty())
		{
			temp.pop_back();
		}
		for (int i = 0; i < size; i++) //Store each value in the old table into a temporary array
		{
			if (table[i] != " ") //if the value at this point exists, put it into the temp array
			{
				temp.push_back(table[i]);
			}
		}
		delete[] table;
		table = tempTable;
		//delete[] tempTable;
		cout << " to " << tablesize << "\n";
	return tablesize;
		
}
int Hash(string key, int tableSize) //given the key and tablesize, this funtion will return the slot on the table the number will occupy
{
	int hashVal = 0;
	for( char ch : key)
	{
		hashVal = 37 * hashVal + ch;
	}
	return  (abs(hashVal) % tableSize);
}
int max(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

Dictionary::Dictionary()
{
	cout << "Initializing dictionary\n";
  size = startSize;
  for (int i = 0; i < size; i++)
  {
	  table[i] = " ";
  } 
}
Dictionary::~Dictionary()
{

}

void Dictionary::AddEntry(string anEntry)
{
	//cout << "attempting to add entry\n";
	int slot =  Hash(anEntry, size);  //calculates the slot
	//cout << "The slot is " << slot << "\n";
	bool added = false;
	int failureCount = 0;
	while (added == false && slot < size)
	{
		if ((table[slot] == " ")) // if the slot is unoccupied
		{
			table[slot] = anEntry; // puts a value into the table
			slotsFilled++;
			//cout << "slot " << slot << " filled.  Failure count " << failureCount << "\n";
			if (slotsFilled + 1 >= (.50 * size)) //if the table is going to be too small, resize
			{
				size = tableResize(size);
				int tempSize = temp.size();
				for (int i = 0; i < tempSize; i++) //add if value in the temp array to the new table
				{
					AddEntry(temp[i]);
					cout << "Finished Resizing to " << size << "\n";
				}
			}
			added = true;
			break;
		}
		else
		{
			failureCount++;
			if ((slot + failureCount * failureCount) < size) // or it will increment the slot in the table
			{
				slot = (slot + failureCount * failureCount);
			}
			else
			{
				slot = (slot + failureCount * failureCount) - size;
				while (slot >= size)
				{
					slot = slot - size;//will wrap around to beginning if needed
				}
			}
		}
	}
}
bool Dictionary::FindEntry(string key)
{
	//cout << "Attempting to find entry\n";
	bool found = false;
	for(int i = 0 ; i < size ; i++)
	{
			if(table[i] == key)
			{
				found = true;
				break;
			}
	}
	
  return found;
}
