#include <iostream>
#include <string>
#include "City.h"
using namespace std;

void cities()
{
	City earth[48];

	//Each city is the number on Joeven's Colored Order doc - 1

	//Blue Cities 0-11
	earth[0].name = "San Fransisco";
	earth[0].connectOne = &earth[1]; // Chicago
	earth[0].connectTwo = &earth[12]; // Milan
	earth[0].connectThree = &earth[45]; // Manila
	earth[0].connectFour = &earth[38];  // Tokyo

	earth[1].name = "Chicago";
	earth[1].connectOne = &earth[2]; // Montreal
	earth[1].connectTwo = &earth[5]; // Atlanta
	earth[1].connectThree = &earth[13]; // Mexico City
	earth[1].connectFour = &earth[12]; // LA
	earth[1].connectFive = &earth[0]; // SF

	earth[2].name = "Atlanta";
	earth[2].connectOne = &earth[4]; // Washington
	earth[2].connectTwo = &earth[14]; // Miami
	earth[2].connectThree = &earth[1]; // Chicago

	earth[3].name = "Montreal";
	earth[3].connectOne = &earth[3]; // New York
	earth[3].connectTwo = &earth[4]; // Washington
	earth[3].connectThree = &earth[1]; // Chicago
	
	earth[4].name = "Washington";
	earth[4].connectOne = &earth[3]; // New York
	earth[4].connectTwo = &earth[14]; // Miami
	earth[4].connectThree = &earth[5]; // Atlanta
	earth[4].connectFour = &earth[2]; // Montreal
	
	earth[5].name = "New York";
	earth[5].connectOne = &earth[6]; // London
	earth[5].connectTwo = &earth[7]; // Madrid
	earth[5].connectThree = &earth[4]; // Washington
	earth[5].connectFour = &earth[2]; // Montreal
	
	earth[6].name = "London";
	earth[6].connectOne = &earth[9]; // Essen
	earth[6].connectTwo = &earth[8]; // Paris
	earth[6].connectThree = &earth[7]; // Madrid
	earth[6].connectFour = &earth[3]; // New York
	
	earth[7].name = "Madrid";
	earth[7].connectOne = &earth[6]; // London
	earth[7].connectTwo = &earth[8]; // Paris
	earth[7].connectThree = &earth[24]; // Algiers
	earth[7].connectFour = &earth[18]; // Sao Paulo
	earth[7].connectFive = &earth[3]; // New York
	
	earth[8].name = "Paris";
	earth[8].connectOne = &earth[9]; // Essen
	earth[8].connectTwo = &earth[10]; // Milan
	earth[8].connectThree = &earth[24]; // Algiers
	earth[8].connectFour = &earth[7]; // Madrid
	earth[8].connectFive = &earth[6]; // London
	
	earth[9].name = "Essen";
	earth[9].connectOne = &earth[11]; // St. Petersburg
	earth[9].connectTwo = &earth[10]; // Milan
	earth[9].connectThree = &earth[8]; // Paris
	earth[9].connectFour = &earth[6]; // London

	
	earth[10].name = "Milan";
	earth[10].connectOne = &earth[25]; // Istanbul
	earth[10].connectTwo = &earth[8]; // Paris
	earth[10].connectThree = &earth[9]; // Essend

	earth[11].name = "St. Petersburg";
	earth[11].connectOne = &earth[27]; // Moscow
	earth[11].connectTwo = &earth[25]; // Istanbul
	earth[11].connectThree = &earth[9]; // Essen

	//Yellow Cities 12-23
	earth[12].name = "Los Angeles";
	earth[12].connectOne = &earth[0]; // SF
	earth[12].connectTwo = &earth[1]; // Chicago
	earth[12].connectTwo = &earth[47]; // Sydney
	earth[12].connectThree = &earth[13]; // Mexico City
	
	earth[13].name = "Mexico City";
	earth[13].connectOne = &earth[12]; // LA
	earth[13].connectTwo = &earth[1]; // Chicago
	earth[13].connectTwo = &earth[14]; // Miami
	earth[13].connectTwo = &earth[15]; // Bogota
	earth[13].connectThree = &earth[16]; // Lima
	
	earth[14].name = "Miami";
	earth[14].connectOne = &earth[0]; // SF
	earth[14].connectTwo = &earth[1]; // Chicago
	earth[14].connectTwo = &earth[15]; // Bogota
	earth[14].connectThree = &earth[4]; // Washington
	
	earth[15].name = "Bogota";
	earth[15].connectOne = &earth[14]; // Miami
	earth[15].connectTwo = &earth[16]; // Lima
	earth[15].connectTwo = &earth[13]; // Mexico City 
	earth[15].connectThree = &earth[18]; // Sau Paulo
	earth[15].connectTwo = &earth[17]; // Buenos Aires
	
	earth[16].name = "Lima";
	earth[16].connectOne = &earth[15]; // Bogota
	earth[16].connectTwo = &earth[13]; // Mexico City 
	earth[16].connectThree = &earth[23]; // Santiago
	
	earth[17].name = "Buenos Aires";
	earth[17].connectThree = &earth[18]; // Sau Paulo
	earth[17].connectTwo = &earth[15]; // Bogota
	
	earth[18].name = "Sao Paulo";
	earth[18].connectOne = &earth[7]; // Madrid
	earth[18].connectTwo = &earth[19]; // Lagos
	earth[18].connectThree = &earth[15]; // Bogota
	earth[18].connectTwo = &earth[17]; // Buenos Aires
	
	earth[19].name = "Lagos";
	earth[19].connectOne = &earth[18]; // Sao Paulo
	earth[19].connectTwo = &earth[20]; // Khartoum
	earth[19].connectThree = &earth[22]; // Kinshasa
	
	earth[20].name = "Khartoum";
	earth[20].connectOne = &earth[19]; // Lagos
	earth[20].connectTwo = &earth[21]; // Johannesburg
	earth[20].connectThree = &earth[22]; // Kinshasa
	earth[20].connectOne = &earth[26]; // Cairo
	
	earth[21].name = "Johannesburg";
	earth[21].connectTwo = &earth[20]; // Khartoum
	earth[21].connectThree = &earth[22]; // Kinshasa
	
	earth[22].name = "Kinshasa";
	earth[22].connectOne = &earth[19]; // Lagos
	earth[22].connectTwo = &earth[21]; // Johannesburg
	earth[22].connectThree = &earth[20]; // Khartoum
	
	earth[23].name = "Santiago";
	earth[23].connectTwo = &earth[16]; // Lima

	//Black Cities 24-35
	//Red Cities 36-47
}
