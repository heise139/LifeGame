/*
 * UnityTest.h
 *
 *  Created on: Jun 3, 2017
 *      Author: root
 */
#include "../LifeGame.h"
#include "assert.h"

#ifndef SRC_UNITYTEST_H_
#define SRC_UNITYTEST_H_


class UnitTest
{
public:
	static void AroundCellCountTest()
	{
		LifeGame lg;
		int scale = 4;
		lg.scale = 4;
		lg.all_space = new bool*[scale];
		for(int i = 0; i < scale; i++)
		{
			lg.all_space[i] = new bool[scale];
		}

		for(int i = 0 ; i< scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				lg.all_space[i][j] = false;
			}
		}

		//GIVEN
		Position pos1(1, 1);
		Position pos2(0 ,1);
		Position pos3(0, 0);
		lg.all_space[1][1] = true;
		lg.all_space[0][1] = true;
		lg.all_space[1][2] = true;
		lg.all_space[2][2] = true;

		//lg.PaintAllSpace();
		int result1 = lg.AroundCellCount(pos1.x, pos1.y);
		int result2 = lg.AroundCellCount(pos2.x, pos2.y);
		int result3 = lg.AroundCellCount(pos3.x, pos3.y);
		assert(result1 == 3);
		assert(result2 == 2);
		assert(result3 == 2);
		cout<<"AroundCellCountTest passed"<<endl;
	}

	static void CalculateCellNextState()
	{
		LifeGame lg;
		int scale = 4;
		lg.scale = 4;
		lg.all_space = new bool*[scale];
		for(int i = 0; i < scale; i++)
		{
			lg.all_space[i] = new bool[scale];
		}

		for(int i = 0 ; i< scale; i++)
		{
			for(int j = 0 ; j < scale; j++)
			{
				lg.all_space[i][j] = false;
			}
		}

		Position pos1(1, 1);
		Position pos2(0 ,1);
		Position pos3(0, 0);
		lg.all_space[1][1] = true;
		lg.all_space[0][1] = true;
		lg.all_space[1][2] = true;
		lg.all_space[2][2] = true;

		bool result1 = lg.CalculateCellNextState(pos1.x, pos1.y);
		bool result2 = lg.CalculateCellNextState(pos2.x, pos2.y);
		bool result3 = lg.CalculateCellNextState(pos3.x, pos3.y);

		assert(result1 == true);
		assert(result2 == true);
		assert(result3 == false);
		cout<<"CalculateCellNextState passed"<<endl;
	}
};



#endif /* SRC_UNITYTEST_H_ */
