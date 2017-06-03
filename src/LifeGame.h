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
#include <string>
#include <cstring>

#include <set>

using namespace std;

#ifndef SRC_LIFEGAME_H_
#define SRC_LIFEGAME_H_

vector<string> split(string& str,const char* c);



class Position{
public:
	int x;
	int y;
	Position()
	{
		x = 0;
		y = 0;
	}

	Position(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	bool operator<(const Position& p1) const
	{
		if(p1.x == x && y == p1.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}


};


class LifeGame
{
public:

	LifeGame()
	{
		scale = 0;
		all_space = 0;
		default_space = 0;
		refresh_interval = 1.0;
	}

	void RandomGenerateOriginalCells(int num)
	{
		srand((unsigned int)time(0));
		int x;
		int y;
		while(originalCells.size() < num)
		{
			x = rand()%scale;
			y = rand()%scale;
			Position pos(x, y);
			originalCells.insert(pos);
		}

	}
	void InitFromFile(char* content[], int lineNum)
	{
		cout<<"begin initialization ...."<<endl;
		string str = content[0];
		vector<string> strs = split(str, " ");

		scale = atoi(strs[0].c_str());
		refresh_interval = atof(strs[1].c_str());

		cout<<"scale " << scale << " ";
		cout<<"refresh_interval " << refresh_interval << endl;

		int cellnum = atoi(content[1]);
		cout<<strs[2];
		if(strcmp(strs[2].c_str(),"random\n") != 0)
		{
			cout<<"file generate"<<endl;
			for(int i = 0; i < cellnum; i++)
			{
				Position pos;
				string str1 = content[i+2];
				strs = split(str1 ," ");
				pos.x = atoi(strs[0].c_str());
				pos.y = atoi(strs[1].c_str());
				originalCells.insert(pos);
			}
		}
		else
		{
			cout<<"random generate"<<endl;
			RandomGenerateOriginalCells(cellnum);
		}
		cout<<"cell num " << originalCells.size()<<endl;
		Initializaiton();
	}

	void Initializaiton()
	{
		all_space = new bool*[scale];
		default_space = new bool*[scale];
		for(int i = 0; i < scale; i++)
		{
			all_space[i] = new bool[scale];
			default_space[i] = new bool[scale];
		}

		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				all_space[i][j] = false;
				default_space[i][j] = false;
			}
		}

		for(set<Position>::iterator it = originalCells.begin(); it != originalCells.end(); it++)
		{
			all_space[it->x][it->y] = true;
		}

	}

	void RefreshNextState()
	{
		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				default_space[i][j] = false;
			}
		}

		for(int i = 0 ; i < scale; i++)
		{
			for(int j = 0; j < scale; j++)
			{
				default_space[i][j] = CalculateCellNextState(i, j);
			}
		}

		bool **tmp = all_space;
		all_space = default_space;
		default_space = tmp;
	}

	void MainLogic()
	{
		while(CheckIfStopped())
		{
			usleep(refresh_interval * 1000 * 1000);
			PaintAllSpace();
			RefreshNextState();
		}
	}

	bool CheckIfStopped()
	{
		bool result = false;
		for(int i = 0; i < scale; i++)
		{
			for(int j = 0; j < scale; j++)
			{
				if(all_space[i][j])
				{
					result = true;
				}
			}
		}
		return result;
	}

	void PaintAllSpace()
	{
		char alive = '@';
		char dead = ' ';
		system("clear");
		for(int i = 0 ; i < scale*2; i++)
		{
			cout<<"-";
		}
		cout<<endl;
		for(int i = 0 ; i < scale ; i ++)
		{
			cout<<"|";
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
			cout<<"|" << endl;
		}
		for(int i = 0 ; i < scale*2; i++)
		{
			cout<<"-";
		}
		cout<<endl;

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
		return false;
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
	set<Position> originalCells;
	bool **all_space;
	float refresh_interval;
	bool **default_space;
};



#endif /* SRC_LIFEGAME_H_ */
