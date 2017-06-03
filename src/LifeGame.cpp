/*
 * LifeGame.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: root
 */
#include "LifeGame.h"
#include "lib_io.h"

int main(int argc, char* argv[])
{
	 int line_num;
	 char *topo[MAX_EDGE_NUM];
	 char *topo_file = argv[1];

	 line_num = read_file(topo, MAX_EDGE_NUM, topo_file);

	LifeGame lg;
	lg.InitFromFile(topo, line_num);
	lg.MainLogic();
}




