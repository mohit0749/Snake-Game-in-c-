#include<iostream>
#include<ctime>
#include<conio.h>
#include<cstdio>
#include<stdlib.h>
#include<cctype>
#include<cstring>
#include<Windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#pragma warning(disable:4996)

using namespace std;
bool gameOver;
FILE *fp;
char buf[1024];
int x, y, fx, fy,score=0;
int speed = 100;
const int width = 20,height=20;
int n = 0;
int snakex[100],snakey[100];
enum edir { s = 0, l, r, up, down };
edir dir;
void setup() {
	gameOver = false;
	x = y = fx = fy = score = 0;
	memset(&snakex, 0, sizeof(snakex));
	memset(&snakex, 0, sizeof(snakex));
	dir = s;
	n = 0;
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
	score = 0;

}
void draw() {
	system("cls");
	cout << (char)0xC9;//top left corner char
	for (int i = 1;i <= width;i++) {
		cout << (char)0xCD;//horizontal line char
	}
	cout << (char)0xBB;//top right corner 
	cout << '\n';
	for (int i = 0;i < height;i++) {
		for (int j = 0;j <width;j++) {
			if (j == 0)cout << (char)0xBA;// vertical line char
			if (i == y&&j == x) {
				cout <<"@";
			}
			else if (i == fy&&j == fx)
				cout << 'F';
			else {
				bool print = false;
				for (int k = 0;k < n;k++) {
					if (snakey[k] == i&&snakex[k] == j) {
						cout << "o";
						print = true;
					}
				}
				if (!print)cout << " ";
			}
			if (j == width - 1)cout << (char)0xBA;
		}
		cout << endl;
	}
	cout << (char)0xC8;//bottom left corner
	for (int i = 1;i <= width;i++) {
		cout << (char)0xCD;
	}
	cout << (char)0xBC;//bottom right corner
	cout << "\nScore:" << score << endl;
}
void input() {
	if (_kbhit()) {
		switch (_getch()) 
		{
			case KEY_LEFT:
				dir = l;
				break;
			case KEY_DOWN:
				dir = down;
				break;
			case KEY_UP:
				dir = up;
				break;
			case KEY_RIGHT:
				dir = r;
				break;
			case 'q':
				gameOver = true;
				break;
		}
	}
}
void logic() {
	int prevx = snakex[0];
	int prevy = snakey[0];
	int tmpx, tmpy;
	snakex[0] = x;
	snakey[0] = y;
	for (int i = 1;i < n;i++) {
		tmpx = snakex[i];
		tmpy = snakey[i];
		snakex[i] = prevx;
		snakey[i] = prevy;
		prevx = tmpx;
		prevy = tmpy;
	}
	switch (dir)
	{
	case l:
		x--;
		break;
	case r:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x <0 || y<0 || y>height)gameOver = true;
	if (x == fx&&y == fy) {
		n++;
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
	}
	for (int k = 0;k < n;k++) {
		if (snakey[k] == y&&snakex[k] == x) {
			gameOver = true;
		}
	}
}
void menu();
void play() {
	//gameOver = false;
	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(speed);
		if (gameOver)
		{
			cout << "Game Over\n";
			system("pause");
			fp = fopen("highScore", "r");
			fgets(buf, 1024, fp);
			int tmpscore = 0;
			for (int i = 0;i < strlen(buf);i++) {
				if (isdigit(buf[i])) {
					tmpscore = tmpscore*10 + buf[i] - '0';
					
				}
				
			}
			if (tmpscore < score) {
				fp = fopen("highScore", "w");
				sprintf(buf, "High Score is:%d", score);
				fputs(buf, fp);
				fclose(fp);
			}
		}
	}
}
void defficulty() {
	system("cls");
	cout << "************************************\n";
	cout << "*      1.Easy                      *\n";
	cout << "*      2.Medium                    *\n";
	cout << "*      3.Hard                      *\n";
	cout << "************************************\n";
	switch (_getch()) {
	case '1':
		speed = 100;
		break;
	case '2':
		speed = 50;
		break;
	case '3':
		speed = 0;
	}
}
void highScore() {
	memset(&buf, 0, sizeof(buf));
	fp = fopen("highScore", "r");
	fgets(buf, 1024, fp);
	system("cls");
	fputs(buf, stdout);
	fclose(fp);
	cout << endl;
	system("pause");
}
void menu() {
	char  ch;
	while (1) {
		system("cls");
		cout << "************************************\n";
		cout << "*      1.New Game                  *\n";
		cout << "*      2.Change Defficulty level   *\n";
		cout << "*      3.High Score                *\n";
		cout << "*      4.Exit                      *\n";
		cout << "************************************\n";
		ch = _getch();
		if (ch == '1') {
			play();
		}
		else if (ch == '2') {
			defficulty();
		}
		else if (ch == '3') {
			highScore();
		}
		else if(ch=='4') return;
	}
}
int main() {
	time_t t = time(NULL);
	srand(t);
	menu();
	//system("pause");
	return 0;
}