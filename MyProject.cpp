#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

unsigned int lenght;		//длина парол€ от 1 до 100
bool fGenerator = true;		// флаг генератора паролей
unsigned int t;				//переменна€ дл€ выбора символов

vector <unsigned char> Letters 
{ 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m' };// Let=1
vector <unsigned char> Numbers  { '1','2','3','4','5','6','7','8','9','0' }; // Num=2
vector <unsigned char> Symbols  { '!','@','#','$','%','^','&','*','(',')','-','=','+','/','~','?','<','>' }; // Sym=3
vector <unsigned char> voidVector;			//пустой массив/буффер
vector <unsigned char> randVector;			// массив с случайным набором символами т.е. пароль будет здесь

enum types {Let = 1, Num, Sym = 3, LetNum = 12, LetSym, NumSym = 23, LetNumSym = 123, }; //дл€ case

void typeSymbols();				//выбор типов символов, из которых будет состо€ть пароль

void UnionVectors123(); 
void UnionVectors12();
void UnionVectors13();
void UnionVectors23();	/*функции объединени€ векторов с разными типами символов*/
void UnionVectors1();
void UnionVectors2();
void UnionVectors3();

void randPassword();			// функци€ заполнени€ массива случайным набором символов
void WritePassword();			// функци€ записи паролей в текстовый файл

int main()
{
	while (!fGenerator == false)
	{
		srand((unsigned int)time(NULL));
		cout << "Enter type symbols" << endl;
		cout << "1-letters, 2-numbers, 3-symbols, 12 let&num, 13-let&sym, 23-num&sym, 123-let&num&sym; 0 - exit" << endl;
		cin >> t;
		typeSymbols();	
		if (!fGenerator == false)			//если поймали исключение в typeSymbols(), то произойдЄт выход из программы								
		{										//игнориру€ последующий код
			cout << "Enter 0 <= lenght <= 100" << endl;
			cin >> lenght;
			if (lenght <= 100 && lenght > 0)
			{
				randPassword();							//заполнение и вывод парол€ в консоль
				cout << "Write down?\ty/n" << endl;	
				WritePassword();					    //функци€ записи парол€ в блокнот (по желанию)
				voidVector.clear();					    //очистка буффера дл€ нового парол€
				randVector.clear();						//очистка вектора с паролем
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
	while (w != 'y' && w != 'n') //"да" или "нет" или бесконечный цикл
	{	
		cin >> w;
	}
	if (w == 'y')
	{
		string str = "Passwords.txt";
		ofstream fout;
		fout.open(str, ofstream::app); //писать поверх других данных в файле
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
		case 0: fGenerator = false; break; //выход из программы 
		default: throw 1;
		};
	}
	catch (int a)
	{
		cout << "Error % " << a << " Use only 1, 2, 3" << endl;
		fGenerator = false;
	}
}


