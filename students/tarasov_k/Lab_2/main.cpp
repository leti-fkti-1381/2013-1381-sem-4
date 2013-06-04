#include <iostream>
#include <cstdio>

using namespace std;

int stepNumber  = 0;
const int x_dim = 4;
const int y_dim = 4;
const int dx[8] = {2,1,-1,-2,-2,-1,1,2};
const int dy[8] = {1,2,2,1,-1,-2,-2,-1};
int gameBoard[x_dim][y_dim];

void printBoard()
{
	cout<<"Gameboard: "<<endl;
	for (int x = 0; x < x_dim; x++)
	{
		for (int y = 0; y < y_dim; y++)
			cout<<((0 == gameBoard[x][y])? '#' : 'K')<<"  ";
		cout<<endl<<endl;
	} 
}

void printSteps()
{
	cout<<endl;
	for (int x = 0; x < x_dim; x++)
	{
		for (int y = 0; y < y_dim; y++)
			cout<<gameBoard[x][y]<<"  ";
		cout<<endl<<endl;
	} 
}

bool canMoveTo(int x, int y)
{
	if ((x >= 0) && (x < x_dim) && (y >= 0) &&  (y < y_dim) && (gameBoard[x][y] == 0))
		return true;
	return false;
}

void process (int x, int y)
{
	gameBoard[x][y] = stepNumber++;

	printBoard();
	for (int i = 0; i < 8; i++)          
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (canMoveTo(nx, ny))
		{
			cout<<"current move: ("<<y<<","<<x<<") - ("<<ny<<","<<nx<<")"<<endl;
			process(nx, ny);
		}
	}
}

void main()
{
	int x;
	int y; 
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			gameBoard[y][x] = 0;
		}
	}

	cout<<"Enter knight coords:"<<endl<<"x:";
	cin>>x;
	cout<<"y:";
	cin>>y;
	cout<<endl;
	gameBoard[x][y] = 1;

	process(x, y);

	printSteps();

	getchar();
	getchar(); 
}