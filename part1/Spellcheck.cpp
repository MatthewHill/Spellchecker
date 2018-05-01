
#include "Dictionary.h"
#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;
void ScreenPrint(string value[], int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
	{
		//printf("%s \n", value[i]);
		cout << value[i] << "\n";
	}
}
int main(int argc, char *argv[])
{
	if (argc == 1) {
		cout << "No command line argument given.\n"
			"Please provide the input file name as an argument.\n";
		return -1;
	}
Dictionary myDictionary;
ifstream inputDic;
string inputDicName("Dict.txt");
inputDic.open(inputDicName);
string input;
if (inputDic.is_open()) {
	while (inputDic >> input) {
			// adds each input to your dictionary
			//input.erase(remove(input.begin(), input.end(), '\n'), input.end()); //scrub input on \n characters
		if(myDictionary.FindEntry(input) == false)
			{
			myDictionary.AddEntry(input);
			}
		}
		inputDic.close();
	}
	else {
		cout << "Unable to open " << endl;
		return -1;
		}
vector<string> vector;
ifstream inputFile;
ofstream outputFile;
string inputFileName(argv[1]);
string outputFileName = inputFileName;
inputFile.open(inputFileName);
outputFileName.append("_spellChecked.txt");
string entry;
if (inputFile.is_open()) {
		while (inputFile >> entry) {
			  string tempEntry = "";
			  locale loc;
			  int entryLength = entry.length();
			  for (int i=0; i <entryLength; ++i)
			  {
				tempEntry += tolower(entry[i],loc);
			  }
			  entry = tempEntry;
			 // adds each entry to your data structure
			vector.push_back(entry);
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open " << endl;
		return -1;
	}
	const int vectorsize = vector.size();
	string arr[vectorsize];
	int arrSize = sizeof(arr) / sizeof(arr[0]);
	printf("Array has  %d  Elements. \n", arrSize);
	copy(vector.begin(), vector.end(), arr);
	printf("Starting Array: \n");
	ScreenPrint(arr, arrSize);
	for(int i = 0; i < arrSize; i++)
	{
		if(myDictionary.FindEntry(arr[i])== false)
		{
			bool found = false;
			while (found == false)
			{
				//try to find word
				cout << arr[i] << " on line " <<  i+1 <<" was not found ";
				string missSpell = arr[i];
				int wordSize = arr[i].size();
				//add one letter at any position
				string alphabet[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
				for(int j = 0; j < 26; j++)
				{
					for(int position = 0; position <= wordSize; position++)
					{
						missSpell.insert(position,alphabet[j]);
						if(myDictionary.FindEntry(missSpell) == true)
						{
							arr[i] = missSpell;
							cout << "and was changed to "<< missSpell << "\n";  //if the word is found break the loop
							found = true;
							break;
						}
						missSpell = arr[i]; //reset the word for the next change
					}
				}
				if(myDictionary.FindEntry(missSpell) == true)
						{
							found = true;
							break;
						}
				//remove one letter at any position
				string remove = "";
				for(int position = 0; position < wordSize; position++)
				{
					missSpell.replace(position,1,remove);
					if(myDictionary.FindEntry(missSpell) == true)
						{
							arr[i] = missSpell;
							cout << "and was changed to "<< missSpell << "\n";  //if the word is found break the loop
							found = true;
							break;
						}
						missSpell = arr[i]; //reset the word for the next change
				}
					if(myDictionary.FindEntry(missSpell) == true)
						{
							found = true;
							break;
						}
				//exchange adjacent characters
				for(int position = 0; position < wordSize-1; position++)
				{
					swap(missSpell[position], missSpell[position+1]);
					if(myDictionary.FindEntry(missSpell) == true)
						{
							arr[i] = missSpell;
							cout << "and was changed to "<< missSpell << "\n";  //if the word is found break the loop
							found = true;
							break;
						}
						missSpell = arr[i]; //reset the word for the next change
				}
				//swap the first and last letters of the word
				
				swap(missSpell[0], missSpell[wordSize - 1]);
				if (myDictionary.FindEntry(missSpell) == true)
				{
					arr[i] = missSpell;
					cout << "and was changed to " << missSpell << "\n";  //if the word is found break the loop
					found = true;
				}
				missSpell = arr[i]; //reset the word for the next change
				if(myDictionary.FindEntry(arr[i]) == false)
				{
					cout << "and was not able to be corrected\n";
					found = true;
				}
			}
		}
	}
}