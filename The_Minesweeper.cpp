#include <iostream>
#include <cstdbool>
#include <Windows.h>
#include <conio.h>

#include "Window.h"

using namespace std;

const int dimension = 10;
int Board[dimension][dimension];

const int Plot = -2;
const int Mine = -1;
int k = 0;//количество мин

int complexity = 1; //это для кол-ва мин на поле
int quantity = 10;

int CheckMine(int i, int j) {
	int sum = 0;
	for (int y = i - 1; y <= i + 1; ++y) {
		for (int x = j - 1; x <= j + 1; ++x) {
			// Проверяем границы доски
			if (y >= 0 && y < 10 && x >= 0 && x < 10) {
				// Исключаем текущую клетку
				if (y != i || x != j) {
					if (Board[y][x] == Mine) {
						sum++;
					}
				}
			}
		}
	}
	return sum;
}

int random(int start, int end) {
	int pos = rand() % (end - start + 1) + start;
	return pos;
}

void ComplectationMine(int probability) {
	bool check = false;
	int k = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Board[i][j] = Plot;
		}
	}

	while (k < quantity) {
		k = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Board[i][j] == Mine) {
					k++;
					continue;
				}
			}
		}
		if (k == quantity) {
			break;
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (k == quantity) {
					break;
				}
				int N = random(0, 10);
				if (N < probability && N >= 0) {
					Board[i][j] = Mine;
					k++;
					if (k == quantity) {
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board[i][j] == Plot) {
				Board[i][j] = CheckMine(i, j);
			}
		}
	}
}

int main(){
	//cout << "Введите сложность" << endl;
	//cin >> complexity;
	if (complexity == 1) {
		quantity = 10;
	}
	if (complexity == 2) {
		quantity = 40;
	}
	int probability = quantity / 10;
	ComplectationMine(probability);
	//cout << endl;
	int BoardCopy[dimension][dimension];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			BoardCopy[i][j] = Plot;
		}
	}
	int ChoiseLen = 0;
	int ChoiseColomn = 0;

	Window window;

	while (true) {
		system("cls");
		int k = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == ChoiseLen && j == ChoiseColomn) { cout << ">"; }
				else { cout << " "; }
				if (BoardCopy[i][j] == Mine) {
					cout << "X|";
					continue;
				}
				if (BoardCopy[i][j] == Plot) {
					cout << " |";
					k++;
				}
				else {
					cout << BoardCopy[i][j] << "|";
				}
			}
			cout << endl;
		}
		if (k == 0) {
			cout << "	Вы победили!" << endl;
			return 0;
		}
		//window.win(BoardCopy, ChoiseLen, ChoiseColomn);

		int key = _getch();
		if (key == 72) {
			ChoiseLen--;
			if (ChoiseLen < 0) {
				ChoiseLen = 9;
			}
		}
		if (key == 80) {
			ChoiseLen++;
			if (ChoiseLen > 9) {
				ChoiseLen = 0;
			}
		}

		if (key == 75) {//left
			ChoiseColomn--;
			if (ChoiseColomn < 0) {
				ChoiseColomn = 9;
			}
		}
		if (key == 77) {//Right
			ChoiseColomn++;
			if (ChoiseColomn > 9) {
				ChoiseColomn = 0;
			}
		}
		if (key == 13) {
			if (Board[ChoiseLen][ChoiseColomn] == Mine) {
				cout << "Вы проиграли!" << endl;
				return 0;
			}
			else {
				BoardCopy[ChoiseLen][ChoiseColomn] = Board[ChoiseLen][ChoiseColomn];
			}
		}
		if (key == VK_TAB) {//выделить для себя, что там мина
			BoardCopy[ChoiseLen][ChoiseColomn] = Mine;
		}
	}
}