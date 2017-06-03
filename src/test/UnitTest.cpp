/*
 * UnitTest.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: root
 */
#include "UnitTest.h"

#ifdef UNIT_TEST
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
	UnitTest::AroundCellCountTest();
	UnitTest::CalculateCellNextState();
}
#endif



