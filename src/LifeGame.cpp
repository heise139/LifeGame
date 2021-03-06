/*
 * LifeGame.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: root
 */
#include "LifeGame.h"
#include "lib_io.h"

#ifndef UNIT_TEST

vector<string> split(string& str,const char* c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,c);
    }
    delete cstr;
    return res;
}


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
#endif




