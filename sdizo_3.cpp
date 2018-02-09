// sdizo_3.cpp : Defines the entry point for the console application.
//

//Program byl pisany samodzielnie
//Podczas jego pisania korzystalem z materialow zawartych na stronach:
//www.pl.wikibooks.org
//www.eduinf.waw.pl
//http://www.cplusplus.com
//www.cpp0x.pl

//Autor:
//Filip Baszak



//Przyfatne informacje:
//gestosc - stosunek wierzcholkow do krawedzi
#include "stdafx.h";
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <list>
#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>


using namespace std;


//Musimy rozwiazac problem dyskretnego problemu plecakowego oraz asymetrycznego problemu komijawozera
//Dodatkowo 
//Potrzebujemy 2 klasy ktore beda reprezentowaly problem
//Dodatkwoo przyda³aby sie klasa MENU
//Oraz klasa ktora bedzie generowala dane(albo dwie klasy)
//const int MAXINT = 2147483647;

struct Item { //struktura elementow
	int size;
	int value;
};

class DKP { //klasa zajmuj¹ca sie problemem dyskretnego problemu plecakowego
public:
	DKP(); //konstruktor 
	Item **items; //tablica w ktorej przechowujemy liste przedmiotow
	ifstream file; //plik z danymi wejsciowymi
	void doData(); //metoda produkujaca pseudolosowe elementy
	void doData(int s, int i); //metoda produkujaca pseudolosowe elementy
	void print(); //metoda wypisujace elementy i ich opisy
	int itemsNumber; //zmienna w ktorej zapisana jest liczba elementow
	int packSize; //zmienna w ktorej zapisany jest rozmiar plecaka
	void createTab(); //metoda tworzaca liste elementow z pliku
	void menu(); //metoa zarzadzajaca klasa
	void zachlanny(); //algorytm zachlanny
	void dynamiczny(); //algorytm dynamiczny
	void zupelny(); //przeglad zupelny
	void kombinations(int *z, int z_kolumna, int *r, int k, int r_kolumna, int powtorzen, int &v, int *b); //metoda pomocnicza do przegladu zupelnego
	int silnia(int n); //metoda pomocnicza do przegladu zupelnego
	int liczba_kombinacji(int n, int k); //metoda pomocnicza do przegladu zupelnego
};

DKP::DKP() {
	items = NULL;
	itemsNumber = 0;
	packSize = 0;
	createTab();
	//menu();
}

void DKP::menu() {
	int liczba;
	short exit = 0;
	short choise;
	//int index = 0;
	int number = 0;
	while (exit == 0) {
		if (exit == 1) break;
		cout << "Co chcesz zrobic?\n";
		cout << "1. Wczytaj dane z pliku. \n";
		cout << "2. Wygeneruj dane. \n";
		cout << "3. Przeglad zupelny. \n";
		cout << "4. Algorytm zachlanny. \n";
		cout << "5. Algorytm dynamiczny. \n";
		cout << "6. Wypisz liste elementow. \n";
		cout << "7. Wroc do poprzedniego menu. \n";
		cout << "8. Testy. \n";
		cin >> choise;
		if (!cin) {
			cin.clear();
			cin.ignore();
		}
		switch (choise) {

		case 1:
		{
			cout << "Wczytuje dane z pliku: 'dane.txt'" << endl;
			createTab();
			cout << endl;
			break;
		}

		case 2:
		{
			doData();
			break;
		}
		case 3:
		{
			cout << endl;
			if (items == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			zupelny();
			break;
		}
		case 4:
		{
			cout << endl;
			if (items == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			zachlanny();
			break;
		}
		case 5:
		{
			cout << endl;
			if (items == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			dynamiczny();
			break;
		}
		case 6:
		{
			cout << endl;
			if (items == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			print();
			break;
		}
		case 7:
		{
			if (items == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			delete[] items;
			exit = 1;
			break;
		}
		case 8:
		{
			//tests erased


			break;
		}
		default:
		{
			cout << "Wybrales zla opcje!\n";
		}

		}
	}
}

void DKP::doData() {
	int Inu;
	int size;
	cout << "Podaj wage plecaka: ";
	cin >> size;
	cout << "Podaj ilosc elementow: ";
	cin >> Inu;
	int index;
	int v=0;
	int s=0;
	ofstream plik("dane.txt");
	if (plik) {
		plik << size << " " << Inu << endl;;
		srand(time(NULL));
		for (int i = 0; i < Inu; i++) {
			s = (rand() % size) + 0;
			v = (rand() % 50) + 0;
			while (s == 0 || v == 0) {
				s = (rand() % size) + 0;
				v = (rand() % 50) + 0;
			}
			plik << s << " " << v << endl;

		}

	}
	else {
		cout << "B£¥D: nie mo¿na otworzyæ pliku." << endl;
	}
	plik.close();
}

void DKP::doData(int su, int i) {
	int Inu=i;
	int size=su;
	int index;
	int v = 0;
	int s = 0;
	ofstream plik("dane.txt");
	if (plik) {
		plik << size << " " << Inu << endl;;
		srand(time(NULL));
		for (int i = 0; i < Inu; i++) {
			s = (rand() % size) + 0;
			v = (rand() % 50) + 0;
			while (s == 0 || v == 0 || s>size) {
				s = (rand() % size) + 0;
				v = (rand() % 50) + 0;
			}
			plik << s << " " << v << endl;

		}

	}
	else {
		cout << "B£¥D: nie mo¿na otworzyæ pliku." << endl;
	}
	plik.close();
}

void DKP::createTab() {
	string x;
	string y;
	Item *help;
	string line;
	istringstream iss;
	string path = "dane.txt";
	file.open(path.c_str());
	if (file.good()) {
		getline(file, line);
		istringstream iss(line);
		iss >> x;
		iss >> y;
		packSize = stoi(x);
		itemsNumber = stoi(y);
		items = new Item*[itemsNumber];
		int counter = 0;
		int v;
		int s;

		while (counter<itemsNumber) {
			getline(file, line);
			istringstream iss(line);
			iss >> x;
			iss >> y;

			s = stoi(x);
			v = stoi(y);
			help = new Item;
			help->size = s;
			help->value = v;

			items[counter] = help;
			counter++;
		}
		cout << "Udalo sie utworzyc tablice elementow. \n";
	}
	else {
		cout << "Nie udalo sie utworzyc tablicy elementow ;c";
		exit(100);
	}
	file.close();
}

void DKP::print() {
	for (int i = 0; i < itemsNumber; i++) {
		cout << "Element " << i + 1 << " waga: " << items[i]->size << " || wartosc: " << items[i]->value << endl;
	}
	cout << "Waga plecaka: " << packSize << endl;
}

int DKP::silnia(int n) {
	return (n>1) ? n*silnia(n - 1) : 1;
}

int DKP::liczba_kombinacji(int n, int k) {
	return silnia(n) / (silnia(k)*silnia(n - k));
}

void DKP::kombinations(int *z, int z_kolumna, int *r, int k, int r_kolumna, int powtorzen, int &v, int *b) {
	//cout << "Wchodzi do kombinations z k rownym" << k << endl;
	int temp_powtorzen = powtorzen;
	int temp_z_kolumna = z_kolumna;
	short weigth = 0;
	short value = 0;
	// wyswietl kombinacje
	if (r_kolumna>(k - 1)) {
		for (int i = 0; i < k; i++) {
			cout << r[i];
		}
		cout << endl;
		//porownujemy z najlepszym poprzednim rozwiazaniem
		for (int i = 0; i < k; i++) {
			weigth += items[r[i]]->size;
			value += items[r[i]]->value;
		}
		if (value > v && weigth <= packSize) {
			v = value;
			for (int i = 0; i < k; i++) {
				b[i] = r[i];
			}
		}
		return;
	}

	for (int j = 0; j <= powtorzen; ++j) {
		r[r_kolumna] = z[z_kolumna + j];
		kombinations(z, ++temp_z_kolumna, r, k, r_kolumna + 1, temp_powtorzen--, v, b);
	}
}

void DKP::zupelny() {
	int *z, *r;
	int *best;
	int value = 0;
	int change = 0;
	int *out;
	//r = new int[1];
	//best = new int[1];
	//delete best;
	//delete r;
	z = new int[itemsNumber];
	for (int i = 0; i < itemsNumber; i++) {
		z[i] = i;
	}
	out = new int[0];
	for (int i = 1; i < itemsNumber; i++) {
		change = value;
		r = new int[i];
		best = new int[i];
		kombinations(z, 0, r, i, 0, itemsNumber - i, value, best);
		delete r;
		if (value > change) {
			delete out;
			out = new int[i];
			for (int j = 0; j < i; j++) {
				out[j] = best[j];
			}
		}
		delete best;
	}
	/*for (int i = 0;out[i]<abs(itemsNumber); i++) {
		cout << out[i] << ", ";
	}*/
	cout << endl;
	cout << "Najwieksza mozliwa wartosc: " << value << endl;
	delete out;
	delete z;
}

void DKP::zachlanny() {

	double help1;
	double help2;
	Item *help;
	for (int j = 0; j < itemsNumber;) {
		for (int i = j; i < itemsNumber;) {
			help1 = items[j]->value / items[j]->size;
			help2 = items[i]->value / items[i]->size;
			if (help2>help1) {
				help = new Item;
				help->size = items[i]->size;
				help->value = items[i]->value;
				items[i]->size = items[j]->size;
				items[i]->value = items[j]->value;
				items[j]->size = help->size;
				items[j]->value = help->value;
				delete help;
			}
			i++;
		}
		j++;
	}
	int weigth = 0;
	int counter = 0;
	int counter2 = 0;
	Item *out;
	out = new Item[0];
	while (1) {
		if (((weigth + items[counter]->size) <= packSize) && (items[counter]->size<packSize)) {
			Item *help;
			help = new Item[counter2];
			for(int i = 0; i < counter2; i++) {
				help[i] = out[i];
			}
			delete[] out;
			out = new Item[counter2 + 1];
			for (int i = 0; i < counter2 + 1; i++) {
				out[i] = help[i];
			}
			out[counter2].size = items[counter]->size;
			out[counter2].value = items[counter]->value;
			counter2++;
			weigth += items[counter]->size;
			delete help;
		}
		counter++;
		if (counter >= itemsNumber) {
			break;
		}
	}
	cout << endl;
	weigth = 0;
	cout << "Oto elementy ktore mamy w plecaku: \n";
	for (int i = 0; i < counter2; i++) {
		cout << "Element " << i + 1 << " : waga - " << out[i].size << " || wartosc - " << out[i].value << endl;
		weigth += out[i].value;
	}
	cout << "Laczna wartosc elementow: " << weigth << endl;
	delete out;
}

void DKP::dynamiczny() {

	int W = packSize;
	short **A;
	A = new short*[itemsNumber];
	for (int i = 0; i < itemsNumber; i++) {
		A[i] = new short[packSize];
	}
	for (int j = 0; j < itemsNumber; j++) {
		for (int i = 0; i < packSize; i++) {
			A[j][i] = 0;
		}
	}
	for (int i = 1; i < itemsNumber; i++) {
		for (int j = 0; j < packSize; j++) {
			A[i][j] = A[i - 1][j];
			if ((j >= 1) && (A[i][j - 1]>A[i][j])) {
				A[i][j] = A[i][j - 1];
			}
			if ((j >= items[i]->size) && ((A[i - 1][j - items[i]->size] + items[i]->value)>A[i][j])) {
				A[i][j] = A[i - 1][j - items[i]->size] + items[i]->value;
			}
		}
	}
	//Wynik naszych obliczen jest w tablicy dynamicznej A[itemsNumber][maxW]
	cout << "Dla wielkosci plecaka: " << packSize << " , najwieksza wartosc to: " << A[itemsNumber-1][packSize-1] << endl;
}

class TSP { //klasa zarzadzajaca problemem
public:
	TSP(); //konstruktor
	int **matrix; //macierz sasiedzctwa
	int *vertic; //tablica wierzcholkow
	ifstream file; //plik z danymi wejsciowymi
	void doData(); //metoda tworzaca pseudolosowy zbior krawedzi
	void doData(int su); //metoda tworzaca pseudolosowy zbior krawedzi
	int vertices; //zmienna w ktorej zapisana jest ilosc wierzcholkow
	void createMatrix(); //metoda tworzaca maceirz z pliku
	void menu(); //metoda zarzadzajaca klasa
	void print(); //metoda wypisujaca elementy
	void zachlanny(); //algorytm zachlanny
	void zupelny(); //przeglad zupelny
	void kombinations(int poz, int *path, bool *v, int &va, int n, int *best); //metoda pomocnicza przegladu zupelnego
	int checkValue(int *path); //metoda pomocnicza przegladu zupelnego
};

TSP::TSP() {
	matrix = NULL;
	vertices = 0;
	createMatrix();
	//menu();
}

void TSP::menu() {
	int liczba;
	short exit = 0;
	short choise;
	//int index = 0;
	int number = 0;
	while (exit == 0) {
		if (exit == 1) break;
		cout << "Co chcesz zrobic?\n";
		cout << "1. Wczytaj dane z pliku. \n";
		cout << "2. Wygeneruj dane. \n";
		cout << "3. Przeglad zupelny. \n";
		cout << "4. Algorytm zachlanny. \n";
		//cout << "5. Algorytm dynamiczny. \n";
		cout << "6. Wypisz liste elementow. \n";
		cout << "7. Wroc do poprzedniego menu. \n";
		cout << "8. Testy. \n";
		cin >> choise;
		if (!cin) {
			cin.clear();
			cin.ignore();
		}
		switch (choise) {

		case 1:
		{
			cout << "Wczytuje dane z pliku: 'dane2.txt'" << endl;
			createMatrix();
			cout << endl;
			break;
		}

		case 2:
		{
			doData();
			break;
		}
		case 3:
		{
			cout << endl;
			if (matrix == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			zupelny();
			break;
		}
		case 4:
		{
			cout << endl;
			if (matrix == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			zachlanny();
			break;
		}
		/*case 5:
		{
			cout << endl;
			if (matrix == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			cout << "Podaj maksymalna wage: \n";
			cin >> number;
			//dynamiczny(number, items);
			number = 0;
			break;
		}*/
		case 6:
		{
		cout << endl;
		if (matrix == NULL) {
			cout << "Lista elementow jest pusta! \n";
			cout << "Wczytaj dane!\n";
			break;
		}
		print();
		break;
		}
		case 7:
		{
			if (matrix == NULL) {
				cout << "Lista elementow jest pusta! \n";
				cout << "Wczytaj dane!\n";
				break;
			}
			for (int i = 0; i < vertices; i++) {
				delete matrix[i];
			}
			delete[] matrix;
			exit = 1;
			break;
		}
		case 8:
		{
			//tests erased
			break;
		}
		default:
		{
			cout << "Wybrales zla opcje!\n";
		}

		}
	}
}

void TSP::doData() {
	int Inu;
	int size;
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> size;
	int index;
	int s = 0;
	ofstream plik("dane2.txt");
	if (plik) {
		plik << size << endl;;
		srand(time(NULL));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				s = (rand() % 10) + 1;
				if (j == i) {
					s = 0;
				}
				plik << s << " ";
			}
			plik << endl;

		}

	}
	else {
		cout << "B£¥D: nie mo¿na utworzyæ pliku." << endl;
	}
	plik.close();
}

void TSP::createMatrix() {
	string *x;
	string line;
	istringstream iss;
	string path = "dane2.txt";
	file.open(path.c_str());
	if (file.good()) {
		getline(file, line);
		istringstream iss(line);
		x = new string[1];
		iss >> x[0];
		vertices = stoi(x[0]);
		vertic = new int[vertices];
		for (int i = 0; i < vertices; i++) {
			vertic[i] = i;
		}
		matrix = new int*[vertices];
		for (int i = 0; i < vertices; i++) {
			matrix[i] = new int[vertices];
		}
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				matrix[i][j] = 0;
			}
		}
		x = new string[vertices];
		int counter = 0;
		int *y;
		y = new int[vertices];
		while (counter<vertices) {
			getline(file, line);
			istringstream iss(line);
			for (int i = 0; i < vertices; i++) {
				iss >> x[i];
			}
			for (int i = 0; i < vertices; i++) {
				y[i]=stoi(x[i]);
			}
			for (int i = 0; i < vertices; i++) {
				matrix[counter][i] = y[i];
			}
			counter++;
		}
		cout << "Udalo sie utworzyc tablice elementow. \n";
	}
	else {
		cout << "Nie udalo sie utworzyc tablicy elementow ;c";
		exit(100);
	}
	file.close();
}

void TSP::doData(int su) {
	int size = su;
	int index;
	int s = 0;
	ofstream plik("dane2.txt");
	if (plik) {
		plik << size << endl;;
		srand(time(NULL));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				s = (rand() % 10) + 1;
				if (j == i) {
					s = 0;
				}
				plik << s << " ";
			}
			plik << endl;

		}

	}
	else {
		cout << "B£¥D: nie mo¿na utworzyæ pliku." << endl;
	}
	plik.close();
}

void TSP::print() {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			cout << "w " << i << " -- W " << j << " == " << matrix[i][j] << endl;
		}
	}
}

int TSP::checkValue(int *path) {
	int out = 0;
	for (int i = 0; i < vertices-1; i++) {
		out = out + matrix[path[i]][path[i+1]];
	}
	return out;
}

void TSP::kombinations(int poz, int *path, bool *v, int &va, int n, int *best) {
	bool *v2;
	v2 = new bool[vertices];
	for (int i = 0; i < vertices; i++) {
		v2[i] = v[i];
	}
	for (int i = 0; i < vertices; ) {
		for (int j = 0; j < vertices; j++) {
			v[j] = v2[j];
			
		}
		if (!v2[i]) {
			path[vertices - poz] = i;
			if (poz == 1) {
				if (checkValue(path) < va) {
					va = checkValue(path);
					for (int i = 0; i < vertices; i++) {
						best[i] = path[i];
					}
				}
				/*for (int i = 0; i < vertices; i++) {
					cout << path[i];
				}
				cout << endl;*/
				delete v2;
				return;
			}
			
			v[i] = true;
			//v2[i] = true;
			kombinations(poz-1,path,v,va,n,best);
		}
		i++;
	}
	delete v2;
}

void TSP::zupelny() {
	bool *visited;
	visited = new bool[vertices];
	for (int j = 0; j < vertices; j++) {
		visited[j] = false;
	}
	int *best;
	best = new int[vertices];
	for (int i = 0; i < vertices; i++) {
		best[i] = -1;
	}
	int *path;
	path = new int[vertices];
	for (int i = 0; i < vertices; i++) {
		path[i] = -1;
	}
	int value = 999999999;
	for (int i = 0; i < vertices; i++) {
		visited[i] = true;
		path[0] = i;
		kombinations(vertices-1, path, visited, value, i, best);
		for (int x = 0; x < vertices; x++) {
			visited[x] = false;
		}
	}
	cout << "Najmniejszy koszt podrozy to: " << value << endl;
	cout << "Sciezka to: \n";
	for (int i = 0; i < vertices; i++) {
		cout << best[i] << " - ";
	}
	cout << endl;
	delete path;
	delete best;
	delete visited;
}

void TSP::zachlanny() {
	int value = 0;
	bool *visited;
	bool run = true;
	int min = 999999999;
	visited = new bool[vertices];
	for (int i = 0; i < vertices; i++) {
		visited[i] = false;
	}
	int *path;
	path = new int[vertices];
	for (int i = 0; i < vertices; i++) {
		path[i] = -1;
	}
	int counter = 0;
	int counter2 = 0;

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if ((matrix[i][j] < min) && (i!=j)) {
				min = matrix[i][j];
				path[counter] = i;
				path[counter + 1] = j;
				value = min;
			}
		}
	}
	visited[path[counter]] = true;
	visited[path[counter + 1]] = true;
	counter++;
	int vHelp = 0;
	while (run) {
		min = 999999999;
		for (int i = 0; i < vertices; i++) {
			if ((matrix[path[counter]][i]<min) && !visited[i]) {
				min = matrix[path[counter]][i];
				path[counter + 1] = i;
				vHelp = matrix[path[counter]][i];
			}
		}
		counter++;
		visited[path[counter]] = true;
		value += vHelp;
		for (int i = 0; i < vertices; i++) {
			if (visited[i]) {
				counter2++;

			}
		}
		//cout << "Odwiedzonych wierzcholkow: " << counter << endl;
		if (counter2 == (vertices)) {
			run = false;
		}
		counter2 = 0;
	}
	cout << "Najmniejszy koszt podrozy to: " << value << endl;
	cout << "Sciezka to: \n";
	for (int i = 0; i < vertices; i++) {
		cout << path[i] << " - ";
	}
	cout << endl;
	delete path;
	delete visited;
}

class Dane {
public:
	short items;
	short size;
	void doData();

};

void Dane::doData() {
	short s=0;
	short v=0;
	ofstream plik("dane.txt");
	if (plik) {
		srand(time(NULL));
		plik << size << " " << items << endl;;
		srand(time(NULL));
		for (int i = 0; i < items; i++) {
			s = (rand() % size) + 0;
			v = (rand() % 50) + 0;
			while (s == 0 || v == 0) {
				s = (rand() % size) + 0;
				v = (rand() % 50) + 0;
			}	
			plik << s << " " << v << endl;
		}
	}
	else {
		cout << "B£¥D: nie mo¿na utworzyæ pliku." << endl;
	}
	plik.close();
}



class Menu { //Klasa zarzadzajaca glownym Menu programu

public:
	unsigned short option;

	Menu();
	void AskForOption() {
		while (true) {//Nasze glowne menu
			cout << "Witaj w programie uzytkowniku.\n";
			cout << "Wpisz numer polecenia: \n";
			cout << "Problemy: \n";
			cout << "1. Dyskretny problem plecakowy. STRUKTURA GOTOWA.\n";
			cout << "2. ASYMETRYCZNY PROBLEM KOMIWOJAZERA. STRUKTURA GOTOWA.\n";
			//cout << "5. Wygeneruj nowe dane. \n";
			//cout << "9. Rozpocznij testy.\n";
			cout << "Aby wyjsc wpisz cokolwiek innego. \n";
			cin >> option;
			if (!cin) {
				cin.clear();
				cin.ignore();
			}
			switch (option) {
			case 1://Dyskretny problem plecakowy(DKP - discreate knapsack problem)
			{
				DKP sack;
				sack.menu();
				
				break;
			}
			case 2://Asymetryczny problem komiwojazera
			{
				TSP seller;
				seller.menu();
				break;
			}

			/*case 5://Stworzmy inne dane
			{
				Dane data;
				cout << "Ile przedmiotow utworzyc?\n";
				cin >> data.items;
				cout << "Wielkosc plecaka?\n";
				cin >> data.size;
				data.doData();
				break;
			}*/

			default:
				cout << "Zla opcja.";
				exit(1000);
				break;
			}
		}
	}


};
Menu::Menu() {
	option = 0;
}
int main()
{
	Menu menu;
	menu.AskForOption();
	return 0;
}

