#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

bool GameOver;

const int width = 20;
const int height = 14;

int X, Y, FX, FY, Score, TailX[100], TailY[100], nTail;
enum M { Stop = 0, Up, Down, Left, Right };
M Move;

void SetColor(int Background, int Text) {
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (Background << 4) + Text);

}

void SetUp() {
	GameOver = 0;
	Move = Stop;
	X = width / 2;
	Y = height / 2;
	FX = rand() % (width - 2);
	FY = rand() % height;
	Score = 0;
	
}

void Draw() {
	system("cls");
	SetColor(5, 2);
	cout << "    SCORE:         " << Score <<endl;
	for (int i = 0; i <= width; i++) {
		SetColor(3, 3);
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			if (j == 0 || j == width - 1) {
				SetColor(3, 3);
				cout << "|";
				SetColor(2, 5);
			}
			if (i == Y && j == X) {
				SetColor(4, 7);
				cout << "0";
				SetColor(2, 5);
			}
			else if (i == FY && j == FX) {
				SetColor(5, 1);
				cout << "@";
				SetColor(2, 5);
			}
			else {
				bool print = 0;
				for (int k = 0; k < nTail; k++) {
					if (TailX[k] == j && TailY[k] == i) {
						print = 1;
						SetColor(4, 7);
						cout << "o";
						SetColor(2, 5);
					}
				}
					if (!print)
						cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i <= width; i++) {
		SetColor(3, 3);
		cout << "^";
		SetColor(2, 5);
	}
	cout << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a' :
			if (Move != Right)
				Move = Left;
			break;
		case 's' :
			if (Move != Up)
				Move = Down;
			break;
		case 'd' :
			if (Move != Left)
				Move = Right;
			break;
		case 'w':
			if (Move != Down)
				Move = Up;
			break;
		case 'x':
			GameOver = 1;
			break;
		}
	}
}

void Logic() {
	int PX = TailX[0];
	int PY = TailY[0];
	int P2X, P2Y;
	TailX[0] = X;
	TailY[0] = Y;
	for (int i = 1; i < nTail; i++) {
		P2X = TailX[i];
		P2Y = TailY[i];
		TailX[i] = PX;
		TailY[i] = PY;
		PX = P2X;
		PY = P2Y;
	}
	switch (Move) {
	case Up:
		Y--;
		break;
	case Down:
		Y++;
		break;
	case Left:
		X--;
		break;
	case Right:
		X++;
		break;
	}
	if (Y == FY && X == FX) {
		Score += 10;
		FX = rand() % (width - 2);
		FY = rand() % height;
		nTail++;
	}
	for(int i = 0;  i < nTail; i++)
		if (TailX[i] == X && TailY[i] == Y)
			GameOver = 1;

	if (X > width - 2|| X < 0 || Y > height || Y < 0)
		GameOver = 1;
}

void St() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char a;
	cout << endl;
	cout << "	¶¶¶¶¶```¶¶¶¶``¶¶¶¶¶¶`¶¶``````¶¶¶¶``````¶¶¶¶``¶¶``¶¶``¶¶¶¶``¶¶``¶¶`¶¶¶¶¶" << endl;
	cout << "	¶¶``¶¶`¶¶``¶¶`¶¶`````¶¶`````¶¶``¶¶````¶¶`````¶¶¶`¶¶`¶¶``¶¶`¶¶`¶¶``¶¶```" << endl;
	cout << "	¶¶¶¶¶``¶¶``¶¶`¶¶¶¶```¶¶`````¶¶``¶¶`````¶¶¶¶``¶¶`¶¶¶`¶¶¶¶¶¶`¶¶¶¶```¶¶¶¶`" << endl;
	cout << "	¶¶``¶¶`¶¶``¶¶`¶¶`````¶¶`````¶¶``¶¶````````¶¶`¶¶``¶¶`¶¶``¶¶`¶¶`¶¶``¶¶```" << endl;
	cout << "	¶¶``¶¶``¶¶¶¶``¶¶`````¶¶¶¶¶¶``¶¶¶¶``````¶¶¶¶``¶¶``¶¶`¶¶``¶¶`¶¶``¶¶`¶¶¶¶¶" << endl << endl;
	cout << "	Version 0.2" << endl << endl;
	cout << "	ENTER 'Y' FOR START GAME: ";
	cin >> a;
	if (a == 'Y' || a == 'y')
	{
		SetUp();
		while (!GameOver) {
			Draw();
			Input();
			Logic();
			Sleep(25);
		}
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned>(time(nullptr)));

	St();

	system("pause");
	return 0;
}
