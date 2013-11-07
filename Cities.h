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
    	earth[24].name = "Algiers";
	earth[24].connectOne = &earth[7]; // Madrid
	earth[24].connectTwo = &earth[8]; // Paris
	earth[24].connectThree = &earth[25]; // Istanbul
	earth[24].connectFour = &earth[26];  // Cairo
    
    	earth[25].name = "Istanbul";
	earth[25].connectOne = &earth[24]; // Algiers
	earth[25].connectTwo = &earth[27]; // Moscow
	earth[25].connectThree = &earth[10]; // Milan
	earth[25].connectFour = &earth[26];  // Cairo
    	earth[25].connectFive = &earth[29]; // Baghdad
	earth[25].connectSix = &earth[11];  // St.Petersburg
    
    	earth[26].name = "Cairo";
	earth[26].connectOne = &earth[24]; // Algiers
	earth[26].connectTwo = &earth[29]; // Baghdad
	earth[26].connectThree = &earth[25]; // Istanbul
	earth[26].connectFour = &earth[31];  // Riyadh
    
	 earth[27].name = "Moscow";
	earth[27].connectOne = &earth[28]; // Tehran
	earth[27].connectTwo = &earth[11]; // St.Petersburg
	earth[27].connectThree = &earth[25]; // Istanbul
    
    	earth[28].name = "Tehran";
	earth[28].connectOne = &earth[27]; // Moscow
	earth[28].connectTwo = &earth[29]; // Baghdad
	earth[28].connectThree = &earth[32]; // Delhi
	earth[28].connectFour = &earth[30];  // Karachi
    
    	earth[29].name = "Baghdad";
	earth[29].connectOne = &earth[28]; // Tehran
	earth[29].connectTwo = &earth[30]; // Karachi
	earth[29].connectThree = &earth[25]; // Istanbul
	earth[29].connectFour = &earth[31];  // Riyadh
    	earth[29].connectFive = &earth[26]; // Cairo
    
    	earth[30].name = "Karachi";
	earth[30].connectOne = &earth[28]; // Tehran
	earth[30].connectTwo = &earth[29]; // Baghdad
	earth[30].connectThree = &earth[32]; // Delhi
	earth[30].connectFour = &earth[31];  // Riyadh
    	earth[30].connectFive = &earth[34]; // Mumbai
    
    	earth[31].name = "Riyadh";
	earth[31].connectOne = &earth[29]; // Baghdad
	earth[31].connectTwo = &earth[30]; // Karachi
	earth[31].connectThree = &earth[26]; // Cairo
    
	earth[32].name = "Delhi";
	earth[32].connectOne = &earth[28]; // Tehran
	earth[32].connectTwo = &earth[30]; // Karachi
	earth[32].connectThree = &earth[33]; // Kolkata
	earth[32].connectFour = &earth[34];  // Mumbai
	earth[32].connectFive = &earth[35]; // Chennai
    
    	earth[33].name = "Kolkata";
	earth[33].connectOne = &earth[43]; // Bangkok
	earth[33].connectTwo = &earth[40]; // Hong Kong
	earth[33].connectThree = &earth[32]; // Delhi
	earth[33].connectFour = &earth[35];  // Chennai
    
    	earth[34].name = "Mumbai";
	earth[34].connectOne = &earth[32]; // Delhi
	earth[34].connectTwo = &earth[30]; // Karachi
	earth[34].connectThree = &earth[35]; // Chennai
    
    	earth[35].name = "Chennai";
	earth[35].connectOne = &earth[43]; // Bangkok
	earth[35].connectTwo = &earth[32]; // Delhi
	earth[35].connectThree = &earth[33]; // Kolkata
	earth[35].connectFour = &earth[34];  // Mumbai
    	earth[35].connectFive = &earth[46]; // Jakarta
    
	//Red Cities 36-47
    
    	earth[36].name = "Beijing";
	earth[36].connectOne = &earth[37]; // Seoul
	earth[36].connectTwo = &earth[39]; // Shanghai
    
	earth[37].name = "Seoul";
	earth[37].connectOne = &earth[39]; // Shanghai
	earth[37].connectTwo = &earth[36]; // Beijing
	earth[37].connectThree = &earth[38]; // Tokyo
    
    	earth[38].name = "Tokyo";
	earth[38].connectOne = &earth[37]; // Seoul
	earth[38].connectTwo = &earth[39]; // Shanghai
	earth[38].connectThree = &earth[42]; // Osaka
	earth[38].connectFour = &earth[0];  // San Francisco
    
    	earth[39].name = "Shanghai";
	earth[39].connectOne = &earth[37]; // Seoul
	earth[39].connectTwo = &earth[36]; // Beijing
    	earth[39].connectThree = &earth[41]; // Taipei
	earth[39].connectFour = &earth[40];  // Hongkong
    	earth[39].connectFive = &earth[38]; // Tokyo
    
    	earth[40].name = "Hong Kong";
	earth[40].connectOne = &earth[39]; // Shanghai
	earth[40].connectTwo = &earth[43]; // Bangkok
	earth[40].connectThree = &earth[41]; // Taipei
    	earth[40].connectFour = &earth[33]; // Kolkata
    	earth[40].connectFive = &earth[45]; // Manila
    	earth[40].connectSix = &earth[44]; // Ho Chi Minh City
    
    	earth[41].name = "Taipei";
	earth[41].connectOne = &earth[42]; // Osaka
	earth[41].connectTwo = &earth[39]; // Shanghai
	earth[41].connectThree = &earth[40]; // Hong Kong
	earth[41].connectFour = &earth[45];  // Manila
    
    	earth[42].name = "Osaka";
	earth[42].connectOne = &earth[38]; // Tokyo
	earth[42].connectTwo = &earth[41]; // Taipei
    
    	earth[43].name = "Bangkok";
	earth[43].connectOne = &earth[35]; // Chennai
	earth[43].connectTwo = &earth[33]; // Kolkata
	earth[43].connectThree = &earth[40]; // Hong Kong
	earth[43].connectFour = &earth[44];  // Ho Chi Minh City
    	earth[43].connectFive = &earth[46]; // Jakarta
    
    	earth[44].name = "Ho Chi Minh City";
	earth[44].connectOne = &earth[42]; // Jakarta
	earth[44].connectTwo = &earth[43]; // Bangkok
	earth[44].connectThree = &earth[40]; // Hong Kong
	earth[44].connectFour = &earth[45];  // Manila
    
    	earth[45].name = "Manila";
	earth[45].connectOne = &earth[0]; // San Francisco
	earth[45].connectTwo = &earth[41]; // Taipei
	earth[45].connectThree = &earth[40]; // Hong Kong
	earth[45].connectFour = &earth[44];  // Ho Chi Minh City
    	earth[45].connectFive = &earth[47]; // Sydney
    
    	earth[46].name = "Jakarta";
	earth[46].connectOne = &earth[35]; // Chennai
	earth[46].connectTwo = &earth[43]; // Bangkok
	earth[46].connectThree = &earth[44]; // Ho Chi Minh City
	earth[46].connectFour = &earth[47];  // Sydney
    
    	earth[47].name = "Sydney";
	earth[47].connectOne = &earth[45]; // Manila
	earth[47].connectTwo = &earth[46]; // Jakarta
    	earth[46].connectThree = &earth[12]; // LA

}
