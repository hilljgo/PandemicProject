#pragma once

#include <iostream>
#include <string>
using namespace std;

class Disease
{
public:
	string name;
	int cubes; //24 max, if < 0, game over
	int status; //Live, cured, eradicated

	Disease()
	{
		name = "";
		cubes = 24;
		status = 3;
	}
	Disease(string n)
	{
		name = n;
		cubes = 24;
		status = 1;
	}
};