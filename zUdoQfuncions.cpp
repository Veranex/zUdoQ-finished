/**
* zUdoQ
* Witaj!
* Nie wiem dok�adnie kto, ani kiedy, przegl�da ten projekt, wi�c od razu napisz�, �e jest to m�j pierwszy tak skomplikowany program w c++.
* W�o�y�em sporo pracy w dok�adne opisanie wszystkiego w kodzie, ale je�li pojawi�y si� jakie� niejasno�ci to prosz� �mia�o do mnie pisa� na adres mh303176@student.polsl.pl lub maciek.henkel@gmail.com
* Jak napisa�em, wcze�niej nigdy nie zrealizowa�em tak du�ego projektu, w zwi�zku z tym nie jest on zapewne najlepiej zoptymalizowany, jednak koniec ko�c�w program dzia�a szybko, a to najwa�niejsze
* Mi�ego korzystania i sukces�w w rozwi�zywaniu sudoku :)
**/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


#pragma comment(lib, "winmm.lib")

using namespace std;
//**********************************PRZYPISANIE KLAWISZOM NAZW DO ICH WARTO�CI KODU ASCII***
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define s 115
#define ESCAPE 27
#define ZERO 48
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define SIX 54
#define SEVEN 55
#define EIGHT 56
#define NINE 57
//****************************************************************STRUKTURY I ICH FUNKCJE***
struct punkt
{
	int x, y;
	punkt* poprzedni, *nastepny;
};
punkt* add(int x, int y, punkt* ostatni)
{
	punkt* nowy = new punkt;
	nowy->x = x;
	nowy->y = y;
	nowy->poprzedni = ostatni;
	if(ostatni!=nullptr) ostatni->nastepny = nowy;
	return nowy;
}
int getx(punkt* ostatni,int n)
{
	punkt* pomoc=ostatni;
		for (int i = 0; i < n; i++)
		{
			pomoc = pomoc->poprzedni;
		}

	return pomoc->x;
}
int gety(punkt* ostatni, int n)
{
	punkt* pomoc = ostatni;
		for (int i = 0; i < n; i++)
		{
			pomoc = pomoc->poprzedni;
		}

	return pomoc->y;
}
int count(punkt* ostatni)
{
	int n = 0;
	while(ostatni != nullptr)
	{
		n++;
		ostatni = ostatni->poprzedni;
	}
	return n;
}
int isEmpty(punkt* ostatni)
{
	if (ostatni == nullptr)
		return true;
	return false;
}
punkt* pop(punkt* ostatni)
{
	punkt* poprzedni;
	if (ostatni == nullptr) return nullptr;
	poprzedni = ostatni->poprzedni;
	delete ostatni;
	return poprzedni;
}
//*********************************************************************DEKLARACJE FUNKCJI***
int start();
int SPlayerMenu();
int BoardCreator(int sudoku[9][9], int x, int y);
int SaveFile(int sudoku[9][9], int save, int gck, int x, int y);
int Game(int save, int x, int y);
int Exit();
void Generator();
punkt* Checker(int sudoku[9][9]);
string SaveNumber(int save);
string SaveNumberOriginal(int save);
void Win(int kolor);
void LOGO();
void Error(int k, int l, int i, int j, punkt*& punkt, int sudoku[9][9]);
void Word();
//**********************************************************************DEFINICJE FUNKCJI***
// 
// 
// 
// 
//****************************************************************************MENU G��WNE***
int start()
{
	int Sinta = 0;
	int sudoku[9][9]{};
	punkt* ostatni = Checker(sudoku);
	setlocale(LC_CTYPE, "Polish"); //B�dzie si� przewija� przez ca�y program, wy�wietla polskie znaki
	LOGO();
	cout << endl << endl << endl
		<< "1. Uruchom gr�\n"
		<< "2. Wygeneruj nowe plansze\n"
		<< "3. Instrukcja i informacje o programie\n"
		<< "4. Stw�rz nowe plansze\n"
		<< "5. Aby wyj�� wci�nij escape\n";
	while (1)
	{
		switch (Sinta=_getch()) //Przewija si� przez ca�y program. Dzi�ki tej funkcji nie trzeba wciska� ENTER aby wprowadzi� zmienn�, jest ona zczytywana bezpo�rednio z klawiatury
		{
		case ONE:
			system("cls");
			return SPlayerMenu();
			break;
		case TWO:
			system("cls");
			Generator();
			break;
		case THREE:
			system("cls");
			Word();
			break;
		case FOUR:
			system("cls");
			return BoardCreator(sudoku,4,4);
			break;
		case ESCAPE:
			Exit();
			break;
		default:
			system("cls");
			cout << "Nie ma takiej opcji :c" << endl;
			return start();
			break;
		}
	}
}
//********************************************************************MENU WYBORU PLANSZY***
int SPlayerMenu()
{
	setlocale(LC_CTYPE, "Polish");
	cout << "Wyb�r planszy:\n"
		<< "plansze �atwe:\n"
		<< "1. \n"
		<< "2. \n"
		<< "3. \n"
		<< "plansze �rednie\n"
		<< "4. \n"
		<< "5. \n"
		<< "6. \n"
		<< "plansze trudne\n"
		<< "7. \n"
		<< "8. \n"
		<<"-----------------------------------------------------------------------\n"
		<<"Plansze stworzone na potrzeby test�w i prezentacji mo�liwo�ci aplikacji\n"
		<<"-----------------------------------------------------------------------\n"
		<<"Plansza pokazuj�ca wszystkie mo�liwe b��dy\n"
		<< "9. \n"
		<<"plansza pokazuj�ca ekran zwyci�stwa\n"
		<< "10. \n"
		<< "Aby wr�ci� do menu g��wnego wci�nij ESCAPE\n";
	int Sintb = 0;
	while (1)
	{
		switch (Sintb = _getch())  //Wybiera jeden z 10 dost�pnych zapis�w gry
		{
		case ONE:
			system("cls");
			Game(Sintb,4,4);
			break;
		case TWO:
			system("cls");
			Game(Sintb,4,4);
			break;
		case THREE:
			system("cls");
			Game(Sintb,4,4);
			break;
		case FOUR:
			system("cls");
			Game(Sintb,4,4);
			break;
		case FIVE:
			system("cls");
			Game(Sintb,4,4);
			break;
		case SIX:
			system("cls");
			Game(Sintb,4,4);
			break;
		case SEVEN:
			system("cls");
			Game(Sintb,4,4);
			break;
		case EIGHT:
			system("cls");
			Game(Sintb,4,4);
			break;
		case NINE:
			system("cls");
			Game(Sintb,4,4);
			break;
		case ZERO:
			system("cls");
			Game(Sintb,4,4);
			break;
		case ESCAPE:
			system("cls");
			start();
		default:
			system("cls");
			cout << "Nie ma takiej opcji :c" << endl;
			SPlayerMenu();

		}
	}
	return 0;
}
//***********************************************************************TWORZENIE PLANSZ***
int BoardCreator(int sudoku[9][9], int x, int y)
{
	setlocale(LC_CTYPE, "Polish");
	punkt* ostatni = Checker(sudoku);
	HANDLE Con;								//Zmiana koloru (R�wnie� b�dzie si� przewija� w kodzie wielokrotnie)
	Con = GetStdHandle(STD_OUTPUT_HANDLE);  //To te�
	cout << "    ";
	for (int l = 0; l < 9; l++)				//Generowanie g�rnego rz�du 1-9
	{
		SetConsoleTextAttribute(Con, 11);
		cout << l + 1 << " ";
		if (l % 3 == 2) cout << "  ";
		SetConsoleTextAttribute(Con, 7);
	}
	cout << endl << endl;
	for (int i = 0; i < 9; i++)
	{
		SetConsoleTextAttribute(Con, 11);
		cout << i + 1 << " ";
		SetConsoleTextAttribute(Con, 7);					//Generowanie pionowego rz�du 1-9
		for (int j = 0; j < 9; j++)
		{

			if (j % 3 == 0)
				cout << "  ";
			for (int n=0; n < count(ostatni); n++)
			{
				if(gety(ostatni, n)==i && getx(ostatni, n) ==j)  //Je�li dana kom�rka zapisana jest w li�cie z b��dami zostanie zaznaczona
				{

					SetConsoleTextAttribute(Con, 0xC7);
				}
			}
			if (i == y && j == x)
			SetConsoleTextAttribute(Con, 0xE0);  //Je�li na danej kom�rce znajduje si� "kursor", tj. Je�li to jest kom�rka, na kt�rej obecnie ustaiony jest u�ytkownik, to kom�rka ta zmienia kolor
			cout << sudoku[i][j];
			SetConsoleTextAttribute(Con, 7);
			cout << " ";

		}
		if (i % 3 == 2)
			cout << endl;
		cout << endl;
	}
	int strzalka = 0;                                          //Mechanizm poruszania si� po planszy, bez mo�liwo�ci opuszczenia jej
	while (1)
	{
		switch (strzalka = _getch())
		{
		case KEY_UP:
			if (y == 0)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				BoardCreator(sudoku, x, y);
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			BoardCreator(sudoku, x, y - 1);
			break;
		case KEY_DOWN:
			if (y == 8)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				BoardCreator(sudoku, x, y);
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			BoardCreator(sudoku, x, y + 1);
			break;
		case KEY_LEFT:
			if (x == 0)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				BoardCreator(sudoku, x, y);
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			BoardCreator(sudoku, x - 1, y);
			break;
		case KEY_RIGHT:
			if (x == 8)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				BoardCreator(sudoku, x, y);
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			BoardCreator(sudoku, x + 1, y);
			break;
		case ENTER:                                        //Mechanizm zmiany zawarto�ci km�rki w przedziale 1-9
			int n;
			switch (n = _getch())
			{
			case ONE:
				sudoku[y][x] = 1;
				break;
			case TWO:
				sudoku[y][x] = 2;
				break;
			case THREE:
				sudoku[y][x] = 3;
				break;
			case FOUR:
				sudoku[y][x] = 4;
				break;
			case FIVE:
				sudoku[y][x] = 5;
				break;
			case SIX:
				sudoku[y][x] = 6;
				break;
			case SEVEN:
				sudoku[y][x] = 7;
				break;
			case EIGHT:
				sudoku[y][x] = 8;
				break;
			case NINE:
				sudoku[y][x] = 9;
				break;
			case ZERO:
				sudoku[y][x] = 0;
				break;
			default:
				system("cls");
				cout << "Podaj wartos�� od 1 do 9\n";
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				BoardCreator(sudoku, x, y);
				break;
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			BoardCreator(sudoku, x, y);
			break;
		case s:                                              //Opcja zapisu, pozwalaj�ca zapisa� plansz� tylko wtedy, gdy nie ma w niej b��du
			if (!isEmpty(ostatni))
			{
				system("cls");
				while (!isEmpty(ostatni))
					ostatni = pop(ostatni);
				cout << "Aby zapisa� plik usu� b��dy\n";
				BoardCreator(sudoku, x, y);
			}
			system("cls");
			while (!isEmpty(ostatni))
				ostatni = pop(ostatni);
			cout << "Kt�ry slot chcesz nadpisa�?\n";
			switch (x = _getch())                           //Wyb�r pliku do zapisu
			{
			case ONE:
				x = ONE;
				break;
			case TWO:
				x = TWO;
				break;
			case THREE:
				x = THREE;
				break;
			case FOUR:
				x =FOUR;
				break;
			case FIVE:
				x = FIVE;
				break;
			case SIX:
				x= SIX;
				break;
			case SEVEN:
				x = SEVEN;
				break;
			case EIGHT:
				x = EIGHT;
				break;
			case NINE:
				x = NINE;
				break;
			case ZERO:
				x = ZERO;
				break;
			default:
				system("cls");
				cout << "Podaj warto�� od 1 do 10, gdzie 10 zapisujemy jako 0\n";
				BoardCreator(sudoku, x, y);
			}
			SaveFile(sudoku, x, 0, 0, 0);
			break;
		case ESCAPE:
			system("cls");
			start();
			break;
		}
	}
}
//**************************************************************************ZAPIS PLANSZY***
int SaveFile(int sudoku[9][9], int save, int gck, int x, int y)
{
	fstream plik, original;
	plik.open(SaveNumber(save), ios::out);
	int count = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			plik << sudoku[i][j] << endl;
		}
	}
	plik << endl;
	plik.close();
	if (gck == 1)                                                  //Zmienna "Gra czy Kreator" - gck. Je�li wynosi 1, to funkcja zwr�ci plansz� gry. Autozapis po ka�dym ruchu
		return Game(save,x,y);
	if (gck == 0)                                                  //Je�li zmienna wynosi 0, to nie do��, �e zapisuje plik edytowalny w czasie gry, zapisuje dodatkowo plik z dopiskiem "- origin", 
	{															   //czyli plik zawieraj�cy oryginaln� plansz�.
		original.open(SaveNumberOriginal(save), ios::out);
		int count = 0;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				original << sudoku[i][j] << endl;
			}
		}
		original << endl;
		original.close();
		system("cls");
		return start();
	} 

}
//************************************************************************************GRA***
int Game(int save,int x, int y)
{
	setlocale(LC_CTYPE, "Polish");
	HANDLE Con;
	Con = GetStdHandle(STD_OUTPUT_HANDLE);
	fstream plik, plik2;
	int sudoku[9][9], sudoku2[9][9], countA = 0, SintA{};
	plik2.open(SaveNumberOriginal(save), ios::in);
	plik.open(SaveNumber(save), ios::in);
	int strzalka = 0;
	if (plik.is_open() && plik2.is_open())
	{
		for (int i = 0; i < 9; i++)									//Pobranie z pliku sudoku oraz jego kopii w stanie zgodnym z zapisem z kreatora. Dzi�ki temu wiem, kt�re kom�rki nie mog� ulec zmianie
		{
			for (int j = 0; j < 9; j++)
			{
				plik2 >> sudoku2[i][j];
				plik >> sudoku[i][j];
			}
		}
		plik2.close();
		plik.close();
	}
	else
	{
		system("cls");
		cout << "To miejsce zapisu jest puste\n";
		return SPlayerMenu();
	}
	punkt* ostatni = Checker(sudoku);
	int counter = 0;								//Mechanizm zwyci�stwa. Gracz wygrywa, je�li program nie wykryje b��du i je�li na planszy nie b�dzie �adnego pustego pola (z warto�ci� 0)
	if (count(ostatni) == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (sudoku[i][j] == 0)
					counter++;
				if (counter > 0)
					break;
			}
		}
	}
	if (counter == 0 && count(ostatni) == 0)										
	{
		int win=1;
		PlaySound(TEXT("Win.wav"), NULL, SND_LOOP | SND_ASYNC);
		int i = 10;
		while (countA<100)
		{
			Win(i);
			i++;
			countA += 1;
			if (i > 15) i = 10;
		}
		SetConsoleTextAttribute(Con, 7);
		switch (SintA = _getch())
		default:
			system("cls");
			start();
	}													// Koniec mechanizmu zwyci�stwa
	cout << "    ";
	for (int l = 0; l < 9; l++)
	{
		SetConsoleTextAttribute(Con, 11);
		cout << l + 1 << " ";
		if (l % 3 == 2) cout << "  ";
		SetConsoleTextAttribute(Con, 7);
	}
	cout << endl << endl;
	for (int i = 0; i < 9; i++)
	{
		SetConsoleTextAttribute(Con, 11);
		cout << i + 1<<" ";
		SetConsoleTextAttribute(Con, 7);
		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				cout << "  ";
			if (sudoku[i][j] == sudoku2[i][j] && sudoku[i][j] != 0)
				SetConsoleTextAttribute(Con, 0x0A);							//Je�li kom�rka pokrywa si� z t� sam� kom�rk� z "oryginalnej" planszy, to zostanie to zaznaczone
			for (int n = 0; n < count(ostatni); n++)
			{
				if (gety(ostatni, n) == i && getx(ostatni, n) == j)         //Je�li program wykryje b��d, to go zaznaczy
				{
					SetConsoleTextAttribute(Con, 0xC7);
				}
				if (gety(ostatni, n) == i && getx(ostatni, n) == j && sudoku[i][j]==sudoku2[i][j] && sudoku[i][j]!=0)       //Je�li b��d zwi�zany jest z kom�rk� z "oryginalnej" planszy, to kom�rka zgodna z
				{																											//oryginaln� plansz� zostanie zaznaczona w inny spos�b
					SetConsoleTextAttribute(Con, 0xCA);
				}
			}
			if (i == y && j == x)
				SetConsoleTextAttribute(Con, 0xE0);
			cout << sudoku[i][j];
			SetConsoleTextAttribute(Con, 7);
			cout << " ";
		}
		if (i % 3 == 2)
			cout << endl;
		cout << endl;
	}
	while (!isEmpty(ostatni))
		ostatni = pop(ostatni);
	while (1)
	{
		switch (strzalka = _getch())
		{
		case KEY_UP:
			if (y == 0)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				Game(save, x, y);
			}
			system("cls");
			Game(save, x, y - 1);
			break;
		case KEY_DOWN:
			if (y == 8)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				Game(save, x, y);
			}
			system("cls");
			Game(save, x, y + 1);
			break;
		case KEY_LEFT:
			if (x == 0)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				Game(save, x, y);
			}
			system("cls");
			Game(save, x - 1, y);
			break;
		case KEY_RIGHT:
			if (x == 8)
			{
				system("cls");
				cout << "Nie mo�esz wyj�� poza plansz� :)\n";
				Game(save, x, y);
			}
			system("cls");
			Game(save, x + 1, y);
			break;
		case ENTER:
			if (sudoku[y][x] == sudoku2[y][x] && sudoku[y][x] != 0)           //Mechanizm zabraniaj�cy zmiany warto�ci w kom�rce z "oryginalnej" planszy
			{
				system("cls");
				cout << "Nie mo�esz zmieni� oryginalnie zapisanej kom�rki\n";
				Game(save, x, y);
			}
			switch (sudoku[y][x] = _getch())
			{
			case ONE:
				sudoku[y][x] = 1;
				break;
			case TWO:
				sudoku[y][x] = 2;
				break;
			case THREE:
				sudoku[y][x] = 3;
				break;
			case FOUR:
				sudoku[y][x] = 4;
				break;
			case FIVE:
				sudoku[y][x] = 5;
				break;
			case SIX:
				sudoku[y][x] = 6;
				break;
			case SEVEN:
				sudoku[y][x] = 7;
				break;
			case EIGHT:
				sudoku[y][x] = 8;
				break;
			case NINE:
				sudoku[y][x] = 9;
				break;
			case ZERO:
				sudoku[y][x] = 0;
				break;
			default:
				system("cls");
				cout << "Podaj liczb� od 0 do 9\n";
				Game(save, x, y);
				break;
			}
			system("cls");
			SaveFile(sudoku, save, 1, x, y);
			break;
		case ESCAPE:
			system("cls");
			start();
			break;
		}
	}
}
//******************************************************************NUMER PLIKU DO ZAPISU***
string SaveNumber(int save)
{
	while (1)
	{
		switch (save)
		{
		case ONE:
			return "tablica1.txt";
			break;
		case TWO:
			return "tablica2.txt";
			break;
		case THREE:
			return "tablica3.txt";
			break;
		case FOUR:
			return "tablica4.txt";
			break;
		case FIVE:
			return "tablica5.txt";
			break;
		case SIX:
			return "tablica6.txt";
			break;
		case SEVEN:
			return "tablica7.txt";
			break;
		case EIGHT:
			return "tablica8.txt";
			break;
		case NINE:
			return "tablica9.txt";
			break;
		case ZERO:
			return "tablica10.txt";
			break;
		default:
			cout << "Podaj numer od 1 do 10 jako numer miesjca do zapisu\n";
			return SaveNumber(save);
			break;
		}
	}

}
//********************************NUMER PLIKU DO SPRAWDZENIA KT�RE KOM�RKI MO�NA ZMIENIA�***
string SaveNumberOriginal(int save)
{
	while (1)
	{
		switch (save)
		{
		case ONE:
			return "tablica1 - Origin.txt";
			break;
		case TWO:
			return "tablica2 - Origin.txt";
			break;
		case THREE:
			return "tablica3 - Origin.txt";
			break;
		case FOUR:
			return "tablica4 - Origin.txt";
			break;
		case FIVE:
			return "tablica5 - Origin.txt";
			break;
		case SIX:
			return "tablica6 - Origin.txt";
			break;
		case SEVEN:
			return "tablica7 - Origin.txt";
			break;
		case EIGHT:
			return "tablica8 - Origin.txt";
			break;
		case NINE:
			return "tablica9 - Origin.txt";
			break;
		case ZERO:
			return "tablica10 - Origin.txt";
			break;
		}
	}

}
//********************************************************SPRAWDZANIE POPRAWNO�CI PLANSZY***
punkt* Checker(int sudoku[9][9])
{
	punkt* punkt = nullptr;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int l = 0; l < 9; l++)
			{
				if (sudoku[i][l] == sudoku[i][j] && sudoku[i][l] != 0 && l != j)			//Sprawdzenie w pionie
				{
					punkt = add(l, i, punkt);												//Co ciekawe, dodanie dw�ch punkt�w wydaje si� niekonieczne, bo przez ten drugi i tak przejdzie p�tla,
					punkt = add(j, i, punkt);												//ale okazuje si�, �e wtedy ten fragment programu si� wywala
				}
				if (sudoku[l][j] == sudoku[i][j] && sudoku[l][j] != 0 && l != i)			//Sprawdzenie w poziomie
				{
					punkt = add(j, l, punkt);
					punkt = add(j, i, punkt);
				}
			}
			if (i < 3)																		//Sprawdzenie w kwadratach
			{
				if (j < 3)
				{
					for (int k=0; k < 3; k++)
					{
						for (int l=0; l < 3; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if(j>=3 && j<6)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if(j>=6)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
			}
			if (i>=3 && i < 6)
			{
				if (j < 3)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if (j >= 3 && j < 6)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if (j > 6)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
			}
			if (i > 6)
			{
				if (j < 3)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if (j >= 3 && j < 6)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
				if (j > 6)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
							{
								Error(k, l, i, j, punkt, sudoku);
							}
						}
					}
				}
			}
		}
	}

	return punkt;
}
//*************************************************************ZAPISYWANIE B��DU DO LISTY***
void Error(int k, int l, int i, int j, punkt* &punkt, int sudoku[9][9])
{

	if (sudoku[k][l] == sudoku[i][j] && sudoku[k][l] != 0 && (k != i || l != j))
	{
		punkt = add(l, k, punkt);
		punkt = add(j, i, punkt);
	}
}
//***********************************************************************GENERATOR PLANSZ***
//Ta funkcja jest sprawna, natomiast wygenerowanie przez ni� sprawnej planszy ma bardzo ma�y procent szans na powodzenie. Nadal jednak sprawdza si� lepiej ni� losowanie plansz dop�ki si� nie trafi.
void Generator()
{
	int Sinta{}, ri, rj, sudoku3D[9][9][10]{}, sudoku[9][9], elim{}, counter=1, counter0{};
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 1; k < 10; k++)
				sudoku3D[i][j][k] = k;   //wpisanie do k-tej kom�rki warto�ci r�wnej k (dla kom�rki k=3 b�dzie to warto�� 3)
		}
	}

	while (counter != 0)
	{
		counter = 0;	//ile zer zosta�o
		counter0 = 0;	//ile warto�ci zaj�tych
		ri = rand() % 9;
		rj = rand() % 9;
		cout << "i" << ri << "j" << rj;
		cout << endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (sudoku3D[i][j][0] == 0)				//Sprawdzenie, czy na planszy s� jeszcze puste pola
				{
					counter += 1;
					counter0 = 0;
					for (int k = 1; k < 10; k++)		//Sprawdzenie ilo�ci potencjalnych warto�ci do wpisania w dan� kom�rk�
					{
						if (sudoku3D[i][j][k] == 0)
							counter0=counter0+1;
					}
					if (counter0 == 9)					//Je�li w dan� kom�rk� nie mo�na wpisa� �adnej z 9 liczb, nast�puje generowanie od nowa
					{
						Generator();
					}
				}
			}
		}
		if (sudoku3D[ri][rj][0] == 0)
		{
			for (int k = 9; k > 0; k--)
			{
				if (sudoku3D[ri][rj][k] != 0)			//Wspiane w wylosowan� kom�rk� mo�liwie najmniejszej warto�ci
				{
					sudoku3D[ri][rj][0] = k;
					elim = k;
				}
			}
			for (int i = 0; i < 9; i++)					//Usuwanie wpisanej uprzednio warto�ci z listy potencjalnych warto�ci p�l w tej samej kolumnie/wierszu/kwadracie
			{
				sudoku3D[i][rj][elim] = 0;
			}
			for (int j = 0; j < 9; j++)
			{
				sudoku3D[ri][j][elim] = 0;
			}
			if (ri < 3)																		//Zerowanie w kwadratach
			{
				if (rj < 3)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj >= 3 && rj < 6)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj >= 6)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
			}
			if (ri >= 3 && ri < 6)
			{
				if (rj < 3)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj >= 3 && rj < 6)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj > 6)
				{
					for (int k = 3; k < 6; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
			}
			if (ri > 6)
			{
				if (rj < 3)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj >= 3 && rj < 6)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 3; l < 6; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
				if (rj > 6)
				{
					for (int k = 6; k < 9; k++)
					{
						for (int l = 6; l < 9; l++)
						{
							if (ri == k && rj == l)
								continue;
							else
								sudoku3D[k][l][elim] = 0;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = sudoku3D[i][j][0];
			cout << sudoku[i][j];
		}
	}
	cout << "W kt�rym miejscu zapisu chcesz stworzy� now� plansz� (od 1 do 8)?\n";
	int rng;
	switch (Sinta = _getch())
	{
	case ONE:
		rng = rand() % 30 + 10;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 1, 0, 4, 4);
		break;
	case TWO:
		rng = rand() % 30 + 10;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 2, 0, 4, 4);
		break;
	case THREE:
		rng = rand() % 30 + 10;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 3, 0, 4, 4);
		break;
	case FOUR:
		rng = rand() % 40 + 30;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 4, 0, 4, 4);
		break;
	case FIVE:
		rng = rand() % 40 + 30;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 5, 0, 4, 4);
		break;
	case SIX:	
		rng = rand() % 40 + 30;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 6, 0, 4, 4);
		break;
	case SEVEN:	
		rng = rand() % 60 + 40;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 7, 0, 4, 4);
		break;
	case EIGHT:	
		rng = rand() % 60 + 40;
		for (int k = 0; k < rng; k++)
		{
			ri = rand() % 9;
			rj = rand() % 9;
			sudoku[ri][rj] = 0;
		}
		SaveFile(sudoku, 8, 0, 4, 4);
		break;
	}
}
void Word()
{
	int x;
	cout << "Witaj!\n"
		<< "Nie wiem dok�adnie kto, ani kiedy, przegl�da ten projekt, wi�c od razu napisz�, �e jest to m�j pierwszy tak skomplikowany program w c++.\n"
		<< "W�o�y�em sporo pracy w dok�adne opisanie wszystkiego w kodzie, ale je�li pojawi�y si� jakie� niejasno�ci to prosz� �mia�o do mnie pisa� na adres mh303176@student.polsl.pl lub maciek.henkel@gmail.com\n"
		<< "Jak napisa�em, wcze�niej nigdy nie zrealizowa�em tak du�ego projektu, w zwi�zku z tym nie jest on zapewne najlepiej zoptymalizowany, jednak koniec ko�c�w program dzia�a szybko, a to najwa�niejsze\n"
		<< "Mi�ego korzystania i sukces�w w rozwi�zywaniu sudoku : )\n"
		<< "Zasady gry w sudoku: \n"
		<< "Celem gry jest uzupe�nienie planszy 9 na 9 liczbami od 1-9 w taki spos�b, aby nie powtarza�y si� w rz�dach, kolumnach, ani ma�ych kwadratach 3x3\n"
		<< "W tej grze wprowadzi�em nast�puj�ce oznaczenia kolorystyczne: \n"
		<< "Kolor bia�y - warto�ci w tych kom�rkach mo�esz swobodnie zmienia�\n"
		<< "Kolor zielony - to s� kom�rki z pierwotnie wprowadzonymi liczbami, ich nie mo�esz zmienia�\n"
		<< "Podkre�lenie czerwone - b��d. W zale�no�ci od koloru tekstu jest to b��d zwi�zany albo z warto�ci� pierwotn� albo z warto�ci� wpisan� przez gracza\n";
	switch (x = _getch())
		default:
			system("cls");
			start();
}
//**************************************************************************WYJ�CIE Z GRY***
int Exit()
{
	int k;
	cout << "Czy na pewno chcesz wyj��? [TAK-ENTER\\NIE-ESCAPE]\n";
	switch (k = _getch())
	{
	case ENTER:
		exit(0);
	case ESCAPE:
		system("cls");
		return start();
		break;
	default:
		cout << "Wprowad� prosz� ENTER lub ESCAPE\n";
		return Exit();
		break;
	}
}
//*****************************************************************************WORD ART-Y***
//Wygrana
void Win(int kolor)
{
	HANDLE Con;
	Con = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Con, kolor);
	system("cls");
	cout << " __                 __      __          __       _______          _________                _               _____        __               _                __" << endl
		<< "|  |               |  |     \\ \\        / /      /  ___  \\        /  _____  \\              / \\             |     \\      |  |             / \\              |  |" << endl
		<< "|  |               |  |      \\ \\      / /      /  /   \\  \\       |  |    \\  \\            /   \\            |  |\\  \\     |  |            /   \\             |  |" << endl
		<< "|  |               |  |       \\ \\    / /      /  /     |__|      |  |     |  |          /  _  \\           |  | \\  \\    |  |           /  _  \\            |  |" << endl
		<< "|  |               |  |        \\ \\  / /       |  |               |  |     |  |         /  / \\  \\          |  |  \\  \\   |  |          /  / \\  \\           |  |" << endl
		<< "|  |               |  |         \\ \\/ /        |  |               |  |____/  /         /  /   \\  \\         |  |   \\  \\  |  |         /  /   \\  \\          |  |" << endl
		<< "\\  \\              /  /           |  |         |  |   ______      |   ___   /         /  /_____\\  \\        |  |    \\  \\ |  |        /  /_____\\  \\         |__|" << endl
		<< " \\  \\    ____    /  /            |  |         |  |  |  __  |     |  |   \\  \\        /  _________  \\       |  |     \\  \\|  |       /  _________  \\ " << endl
		<< "  \\  \\  /    \\  /  /             |  |         \\  \\  |_| /  /     |  |    \\  \\      /  /         \\  \\      |  |      \\  \\  |      /  /         \\  \\        __ " << endl
		<< "   \\  \\/  /\\  \\/  /              |  |          \\  \\____/  /      |  |     \\  \\    /  /           \\  \\     |  |       \\    |     /  /           \\  \\      |  |" << endl
		<< "    \\___ /  \\____/               |__|           \\________/       |__|      \\__\\  /__/             \\__\\    |__|        \\___|    /__/             \\__\\     |__|" << endl;
	Sleep(100);
}
//logo zUdoQ
void LOGO()
{
		cout << " __                 __                         _           _________" << endl
		<< "|  |               |  |                       | \\         /  _____  \\" << endl
		<< "|  |               |  |                       |  \\       /  /     \\  \\" << endl
		<< "|  |               |  |     __________________|   \\     |  |       |  |" << endl
		<< "|  |               |  |    |                       \\    |  |       |  |" << endl
		<< "|  |               |  |    |                        |   |  |       |  |" << endl
		<< "\\  \\              /   /    |__________________     /    |  |    __ |  |" << endl
		<< " \\  \\            /   /                        |   /     |  |    \\ \\|  |" << endl
		<< "  \\  \\          /   /                         |  /       \\  \\____\\/  /" << endl
		<< "   \\  \\________/   /                          |_/         \\________ /\\" << endl
		<< "    \\____________ /                                                 \\_\\" << endl;
}
