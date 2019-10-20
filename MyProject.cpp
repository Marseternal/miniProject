#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>

//password generator

using namespace std;

unsigned int lenght;		//password length from 1 to 100
bool fGenerator = true;		//password generator flag
unsigned int t;			//character selection variable

vector <unsigned char> Letters 
{ 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m' };// Let=1
vector <unsigned char> Numbers  { '1','2','3','4','5','6','7','8','9','0' }; // Num=2
vector <unsigned char> Symbols  { '!','@','#','$','%','^','&','*','(',')','-','=','+','/','~','?','<','>' }; // Sym=3
vector <unsigned char> voidVector;			//empty array / buffer
vector <unsigned char> randVector;			//an array with a random set of characters i.e. password will be here

enum types {Let = 1, Num, Sym = 3, LetNum = 12, LetSym, NumSym = 23, LetNumSym = 123, }; //for case

void typeSymbols();				//selection of the types of characters the password will consist of

void UnionVectors123(); 
void UnionVectors12();
void UnionVectors13();
void UnionVectors23();	/*functions of combining vectors with different types of characters*/
void UnionVectors1();
void UnionVectors2();
void UnionVectors3();

void randPassword();			//random array character filling function
void WritePassword();			//function to write passwords to a text fil

int main()
{
	while (!fGenerator == false)
	{
		srand((unsigned int)time(NULL));
		cout << "Enter type symbols" << endl;
		cout << "1-letters, 2-numbers, 3-symbols, 12 let&num, 13-let&sym, 23-num&sym, 123-let&num&sym; 0 - exit" << endl;
		cin >> t;
		typeSymbols();	
		if (!fGenerator == false)			//if an exception is caught in typeSymbols(), then the program will exit,							
		{										//ignoring subsequent code
			cout << "Enter 0 < lenght <= 100" << endl;
			cin >> lenght;
			if (lenght <= 100 && lenght > 0)
			{
				randPassword();					//filling and displaying the password in the console
				cout << "Write down?\ty/n" << endl;	
				WritePassword();				  //function to write a password in a notebook
				voidVector.clear();				  //clear buffer for new password
				randVector.clear();				  //cleaning vector with password
			}
			else
			{
				cout << "Error. Only 0 < lenght <= 100" << endl;
				fGenerator = false;
			}
		}
	}
	return 0;
}

void UnionVectors123()
{
	copy(Letters.begin(), Letters.end(), back_inserter(voidVector));
	copy(Numbers.begin(), Numbers.end(), back_inserter(voidVector));
	copy(Symbols.begin(), Symbols.end(), back_inserter(voidVector));
}
void UnionVectors12()
{
	copy(Letters.begin(), Letters.end(), back_inserter(voidVector));
	copy(Numbers.begin(), Numbers.end(), back_inserter(voidVector));
}
void UnionVectors13()
{
	copy(Letters.begin(), Letters.end(), back_inserter(voidVector));
	copy(Symbols.begin(), Symbols.end(), back_inserter(voidVector));
}
void UnionVectors23()
{
	copy(Numbers.begin(), Numbers.end(), back_inserter(voidVector));
	copy(Symbols.begin(), Symbols.end(), back_inserter(voidVector));
}
void UnionVectors1()
{
	copy(Letters.begin(), Letters.end(), back_inserter(voidVector));
}
void UnionVectors2()
{
	copy(Numbers.begin(), Numbers.end(), back_inserter(voidVector));
}
void UnionVectors3()
{	
	copy(Symbols.begin(), Symbols.end(), back_inserter(voidVector));
}

void randPassword()
{
	for (unsigned char i = 0; i < lenght; i++)
	{
			randVector.push_back(voidVector[rand() % voidVector.size()]);
			cout << randVector[i];
	}
	cout << endl;
}

void WritePassword()
{
	char w = 0;
	while (w != 'y' && w != 'n') //"yes" or "no" 
	{	
		cin >> w;
	}
	if (w == 'y')
	{
		string str = "Passwords.txt";
		ofstream fout;
		fout.open(str, ofstream::app); 
		if (!fout.is_open()) 
			cout << "Error! File is not found" << endl;
		else
			for (auto el : randVector)
			{
					fout << el;
			}
		fout << endl;
		fout.close();
	}
	else if (w == 'n')
	{
		cout << "skip" << endl;
	}
}

void typeSymbols()
{
	try
	{ 
		switch (t) 
		{
		case Let: UnionVectors1();	break;
		case Num: UnionVectors2();	break;
		case Sym: UnionVectors3();	break;
		case LetNum: UnionVectors12();	break;
		case LetSym: UnionVectors13();	break;
		case NumSym: UnionVectors23();	break;
		case LetNumSym: UnionVectors123(); break;
		case 0: fGenerator = false; break; //exit from the program 
		default: throw 1;
		};
	}
	catch (int a)
	{
		cout << "Error % " << a << " Use only 1, 2, 3" << endl;
		fGenerator = false;
	}
}


