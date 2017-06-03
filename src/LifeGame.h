/*
 * LifeGame.h
 *
 *  Created on: Jun 3, 2017
 *      Author: root
 */
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#ifndef SRC_LIFEGAME_H_
#define SRC_LIFEGAME_H_

class Position{
public:
	int x;
	int y;

	Position(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

};

class LifeGame
{
public:
	LifeGame()
	{
		scale = 0;
		all_space = 0;
		refresh_interval = 1.0;
	}

	bool SetScale()
	{
		cout<<"please input the scale of the ground" <<endl;
		scale = 4;

	}

	void SetOriginalCells()
	{
		cout<<"please input the original cell num" <<endl;
		Position pos1(1 , 1);
		Position pos2(1, 2);
		Position pos3(2, 2);
		Position pos4(0, 2);

		originalCells.push_back(pos1);
		originalCells.push_back(pos2);
		originalCells.push_back(pos3);
		originalCells.push_back(pos4);
	}

	void Initializaiton()
	{
		all_space = new bool*[scale];
		for(int i = 0; i < scale; i++)
		{
			all_space[i] = new bool[scale];
		}

		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				all_space[i][j] = false;
			}
		}
		cout<<"originalCEll num" << originalCells.size() << endl;
		for(int i = 0; i < originalCells.size(); i++)
		{
			all_space[originalCells[i].x][originalCells[i].y] = true;
		}
	}

	void RefreshNextState()
	{
		bool ** nextState;
		nextState = new bool*[scale];
		for(int i = 0; i < scale; i++)
		{
			nextState[i] = new bool[scale];
		}

		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				nextState[i][j] = false;
			}
		}



		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0; j < scale; j++)
			{
				nextState[i][j] = CalculateCellNextState(i, j);
			}
		}

		delete [] all_space;
		all_space = nextState;
	}

	void MainLogic()
	{
		SetScale();
		SetOriginalCells();
		Initializaiton();

		int i = 6;
		while(i--)
		{
			sleep(refresh_interval);
			PaintAllSpace();
			RefreshNextState();
		}
	}

	void PaintAllSpace()
	{
		char alive = '1';
		char dead = '0';
		system("clear");
		//cout<<"============================================="<<endl;
		for(int i = 0 ; i < scale ; i ++)
		{
			for(int j = 0; j < scale; j++)
			{
				if(all_space[i][j])
				{
					cout << alive << ' ';
				}
				else
				{
					cout << dead << ' ';
				}
			}
			cout << endl;
		}
	}

	bool CalculateCellNextState(int x, int y)
	{
		int cells_around = AroundCellCount(x, y);
		if(all_space[x][y])
		{
			if(cells_around  < 2)
			{
				return false;
			}
			else if(cells_around == 2 || cells_around == 3)
			{
				return true;
			}
			else if(cells_around > 3)
			{
				return false;
			}
		}
		else
		{
			if(cells_around == 3)
			{
				return true;
			}
		}
	}

	int AroundCellCount(int x, int y)
	{
		int num = 0;
		int board = scale - 1;
		for(int i = x - 1 ; i <= x + 1; i++)
		{
			if(i < 0 || i > board)
			{
				continue;
			}

			for(int j = y - 1; j <= y + 1; j++)
			{
				if(j < 0 || j > board || (i == x && j == y) )
				{
					continue;
				}
				num += all_space[i][j] ? 1 : 0;
			}
		}
		return num;
	}

	int scale;
	vector<Position> originalCells;
	bool **all_space;
	float refresh_interval;
};



#endif /* SRC_LIFEGAME_H_ */
