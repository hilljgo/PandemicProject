#pragma once

#include <iostream>
#include <string>
using namespace std;

class City
{
public:
	string name;		//This city's name
	City *connectOne;	//The connections of this city
	City *connectTwo;
	City *connectThree;
	City *connectFour;
	City *connectFive;
	City *connectSix;
	int BlueCubes, YellowCubes, BlackCubes, RedCubes;		//Number of disease cubes on the city
	bool outbreak;		//If this city outbreaked during current infection
	bool researchStation;//If this city has a research Center


	City()
	{
		name = "";
		connectOne = connectTwo = connectThree = connectFour = connectFive = connectSix = NULL;
		BlueCubes = YellowCubes = BlackCubes = RedCubes = 0;
		outbreak = false;
		researchStation = false;
	}
};