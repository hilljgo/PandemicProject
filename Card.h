#pragma once

#include <iostream>
#include <string>
using namespace std;


//For player deck, make array with one card for each city, (4,5,or6) epidemic cards, and 5 special event cards
	//For now we can leave special event cards out and add them in later
//For infection deck, make array with one card for each city

class Card	
{	
public:
	string name;	//Name of City or event or "Epidemic"
	int color;		//0-Epidemic, 1-Blue, 2-Yellow, 3-Black, 4-Red, 5-special event; 
	int status;		//Deck, Hand, Discard

	Card()
	{
		name = "";
		color = 0;
		status = 0;
	}

    void iniInfectDeck(Card InfectionDeck[48]){
        //Initialize Infection Deck
        
        //BLUE
        InfectionDeck[0].name = "San Fransisco";
        InfectionDeck[0].color = 1;
        InfectionDeck[0].status = 0;
        
        InfectionDeck[1].name = "Chicago";
        InfectionDeck[1].color = 1;
        InfectionDeck[1].status = 0;
        
        InfectionDeck[2].name = "Montreal";
        InfectionDeck[2].color = 1;
        InfectionDeck[2].status = 0;
        
        InfectionDeck[3].name = "New York";
        InfectionDeck[3].color = 1;
        InfectionDeck[3].status = 0;
        
        InfectionDeck[4].name = "Washington";
        InfectionDeck[4].color = 1;
        InfectionDeck[4].status = 0;
        
        InfectionDeck[5].name = "Atlanta";
        InfectionDeck[5].color = 1;
        InfectionDeck[5].status = 0;
        
        InfectionDeck[6].name = "London";
        InfectionDeck[6].color = 1;
        InfectionDeck[6].status = 0;
        
        InfectionDeck[7].name = "Madrid";
        InfectionDeck[7].color = 1;
        InfectionDeck[7].status = 0;
        
        InfectionDeck[8].name = "Paris";
        InfectionDeck[8].color = 1;
        InfectionDeck[8].status = 0;
        
        InfectionDeck[9].name = "Essen";
        InfectionDeck[9].color = 1;
        InfectionDeck[9].status = 0;
        
        InfectionDeck[10].name = "Milan";
        InfectionDeck[10].color = 1;
        InfectionDeck[10].status = 0;
        
        InfectionDeck[11].name = "St. Petersburg";
        InfectionDeck[11].color = 1;
        InfectionDeck[11].status = 0;
        
        //YELLOW
        InfectionDeck[12].name = "Los Angeles";
        InfectionDeck[12].color = 2;
        InfectionDeck[12].status = 0;
        
        InfectionDeck[13].name = "Mexico City";
        InfectionDeck[13].color = 2;
        InfectionDeck[13].status = 0;
        
        InfectionDeck[14].name = "Miami";
        InfectionDeck[14].color = 2;
        InfectionDeck[14].status = 0;
        
        InfectionDeck[15].name = "Bogota";
        InfectionDeck[15].color = 2;
        InfectionDeck[15].status = 0;
        
        InfectionDeck[16].name = "Lima";
        InfectionDeck[16].color = 2;
        InfectionDeck[16].status = 0;
        
        InfectionDeck[17].name = "Buenos Aires";
        InfectionDeck[17].color = 2;
        InfectionDeck[17].status = 0;
        
        InfectionDeck[18].name = "Sao Paulo";
        InfectionDeck[18].color = 2;
        InfectionDeck[18].status = 0;
        
        InfectionDeck[19].name = "Lagos";
        InfectionDeck[19].color = 2;
        InfectionDeck[19].status = 0;
        
        InfectionDeck[20].name = "Khartoum";
        InfectionDeck[20].color = 2;
        InfectionDeck[20].status = 0;
        
        InfectionDeck[21].name = "Johannesburg";
        InfectionDeck[21].color = 2;
        InfectionDeck[21].status = 0;
        
        InfectionDeck[22].name = "Kinshasa";
        InfectionDeck[22].color = 2;
        InfectionDeck[22].status = 0;
        
        InfectionDeck[23].name = "Santiago";
        InfectionDeck[23].color = 2;
        InfectionDeck[23].status = 0;
        
        //BLACK
        
        InfectionDeck[24].name = "Algiers";
        InfectionDeck[24].color = 3;
        InfectionDeck[24].status = 0;
        
        InfectionDeck[25].name = "Istanbul";
        InfectionDeck[25].color = 3;
        InfectionDeck[25].status = 0;
        
        InfectionDeck[26].name = "Cairo";
        InfectionDeck[26].color = 3;
        InfectionDeck[26].status = 0;
        
        InfectionDeck[27].name = "Moscow";
        InfectionDeck[27].color = 3;
        InfectionDeck[27].status = 0;
        
        InfectionDeck[28].name = "Tehran";
        InfectionDeck[28].color = 3;
        InfectionDeck[28].status = 0;
        
        InfectionDeck[29].name = "Baghdad";
        InfectionDeck[29].color = 3;
        InfectionDeck[29].status = 0;
        
        InfectionDeck[30].name = "Karachi";
        InfectionDeck[30].color = 3;
        InfectionDeck[30].status = 0;
        
        InfectionDeck[31].name = "Riyadh";
        InfectionDeck[31].color = 3;
        InfectionDeck[31].status = 0;
        
        InfectionDeck[32].name = "Delhi";
        InfectionDeck[32].color = 3;
        InfectionDeck[32].status = 0;
        
        InfectionDeck[33].name = "Kolkata";
        InfectionDeck[33].color = 3;
        InfectionDeck[33].status = 0;
        
        InfectionDeck[34].name = "Mumbai";
        InfectionDeck[34].color = 3;
        InfectionDeck[34].status = 0;
        
        InfectionDeck[35].name = "Chennai";
        InfectionDeck[35].color = 3;
        InfectionDeck[35].status = 0;
        
        //RED
        InfectionDeck[36].name = "Beijing";
        InfectionDeck[36].color = 4;
        InfectionDeck[36].status = 0;
        
        InfectionDeck[37].name = "Seoul";
        InfectionDeck[37].color = 4;
        InfectionDeck[37].status = 0;
        
        InfectionDeck[38].name = "Tokyo";
        InfectionDeck[38].color = 4;
        InfectionDeck[38].status = 0;
        
        InfectionDeck[39].name = "Shanghai";
        InfectionDeck[39].color = 4;
        InfectionDeck[39].status = 0;
        
        InfectionDeck[40].name = "Hong Kong";
        InfectionDeck[40].color = 4;
        InfectionDeck[40].status = 0;
        
        InfectionDeck[41].name = "Taipei";
        InfectionDeck[41].color = 4;
        InfectionDeck[41].status = 0;
        
        InfectionDeck[42].name = "Osaka";
        InfectionDeck[42].color = 4;
        InfectionDeck[42].status = 0;
        
        InfectionDeck[43].name = "Bangkok";
        InfectionDeck[43].color = 4;
        InfectionDeck[43].status = 0;
        
        InfectionDeck[44].name = "Ho Chi Minh";
        InfectionDeck[44].color = 4;
        InfectionDeck[44].status = 0;
        
        InfectionDeck[45].name = "Manila";
        InfectionDeck[45].color = 4;
        InfectionDeck[45].status = 0;
        
        InfectionDeck[46].name = "Jakarta";
        InfectionDeck[46].color = 4;
        InfectionDeck[46].status = 0;
        
        InfectionDeck[47].name = "Sydney";
        InfectionDeck[47].color = 4;
        InfectionDeck[47].status = 0;

    }
    
    void iniPlayerDeck(Card PlayerDeck[58]){
        //BLUE
        PlayerDeck[0].name = "San Fransisco";
        PlayerDeck[0].color = 1;
        PlayerDeck[0].status = 0;
        
        PlayerDeck[1].name = "Chicago";
        PlayerDeck[1].color = 1;
        PlayerDeck[1].status = 0;
        
        PlayerDeck[2].name = "Montreal";
        PlayerDeck[2].color = 1;
        PlayerDeck[2].status = 0;
        
        PlayerDeck[3].name = "New York";
        PlayerDeck[3].color = 1;
        PlayerDeck[3].status = 0;
        
        PlayerDeck[4].name = "Washington";
        PlayerDeck[4].color = 1;
        PlayerDeck[4].status = 0;
        
        PlayerDeck[5].name = "Atlanta";
        PlayerDeck[5].color = 1;
        PlayerDeck[5].status = 0;
        
        PlayerDeck[6].name = "London";
        PlayerDeck[6].color = 1;
        PlayerDeck[6].status = 0;
        
        PlayerDeck[7].name = "Madrid";
        PlayerDeck[7].color = 1;
        PlayerDeck[7].status = 0;
        
        PlayerDeck[8].name = "Paris";
        PlayerDeck[8].color = 1;
        PlayerDeck[8].status = 0;
        
        PlayerDeck[9].name = "Essen";
        PlayerDeck[9].color = 1;
        PlayerDeck[9].status = 0;
        
        PlayerDeck[10].name = "Milan";
        PlayerDeck[10].color = 1;
        PlayerDeck[10].status = 0;
        
        PlayerDeck[11].name = "St. Petersburg";
        PlayerDeck[11].color = 1;
        PlayerDeck[11].status = 0;
        
        //YELLOW
        PlayerDeck[12].name = "Los Angeles";
        PlayerDeck[12].color = 2;
        PlayerDeck[12].status = 0;
        
        PlayerDeck[13].name = "Mexico City";
        PlayerDeck[13].color = 2;
        PlayerDeck[13].status = 0;
        
        PlayerDeck[14].name = "Miami";
        PlayerDeck[14].color = 2;
        PlayerDeck[14].status = 0;
        
        PlayerDeck[15].name = "Bogota";
        PlayerDeck[15].color = 2;
        PlayerDeck[15].status = 0;
        
        PlayerDeck[16].name = "Lima";
        PlayerDeck[16].color = 2;
        PlayerDeck[16].status = 0;
        
        PlayerDeck[17].name = "Buenos Aires";
        PlayerDeck[17].color = 2;
        PlayerDeck[17].status = 0;
        
        PlayerDeck[18].name = "Sao Paulo";
        PlayerDeck[18].color = 2;
        PlayerDeck[18].status = 0;
        
        PlayerDeck[19].name = "Lagos";
        PlayerDeck[19].color = 2;
        PlayerDeck[19].status = 0;
        
        PlayerDeck[20].name = "Khartoum";
        PlayerDeck[20].color = 2;
        PlayerDeck[20].status = 0;
        
        PlayerDeck[21].name = "Johannesburg";
        PlayerDeck[21].color = 2;
        PlayerDeck[21].status = 0;
        
        PlayerDeck[22].name = "Kinshasa";
        PlayerDeck[22].color = 2;
        PlayerDeck[22].status = 0;
        
        PlayerDeck[23].name = "Santiago";
        PlayerDeck[23].color = 2;
        PlayerDeck[23].status = 0;
        
        //BLACK
        
        PlayerDeck[24].name = "Algiers";
        PlayerDeck[24].color = 3;
        PlayerDeck[24].status = 0;
        
        PlayerDeck[25].name = "Istanbul";
        PlayerDeck[25].color = 3;
        PlayerDeck[25].status = 0;
        
        PlayerDeck[26].name = "Cairo";
        PlayerDeck[26].color = 3;
        PlayerDeck[26].status = 0;
        
        PlayerDeck[27].name = "Moscow";
        PlayerDeck[27].color = 3;
        PlayerDeck[27].status = 0;
        
        PlayerDeck[28].name = "Tehran";
        PlayerDeck[28].color = 3;
        PlayerDeck[28].status = 0;
        
        PlayerDeck[29].name = "Baghdad";
        PlayerDeck[29].color = 3;
        PlayerDeck[29].status = 0;
        
        PlayerDeck[30].name = "Karachi";
        PlayerDeck[30].color = 3;
        PlayerDeck[30].status = 0;
        
        PlayerDeck[31].name = "Riyadh";
        PlayerDeck[31].color = 3;
        PlayerDeck[31].status = 0;
        
        PlayerDeck[32].name = "Delhi";
        PlayerDeck[32].color = 3;
        PlayerDeck[32].status = 0;
        
        PlayerDeck[33].name = "Kolkata";
        PlayerDeck[33].color = 3;
        PlayerDeck[33].status = 0;
        
        PlayerDeck[34].name = "Mumbai";
        PlayerDeck[34].color = 3;
        PlayerDeck[34].status = 0;
        
        PlayerDeck[35].name = "Chennai";
        PlayerDeck[35].color = 3;
        PlayerDeck[35].status = 0;
        
        //RED
        PlayerDeck[36].name = "Beijing";
        PlayerDeck[36].color = 4;
        PlayerDeck[36].status = 0;
        
        PlayerDeck[37].name = "Seoul";
        PlayerDeck[37].color = 4;
        PlayerDeck[37].status = 0;
        
        PlayerDeck[38].name = "Tokyo";
        PlayerDeck[38].color = 4;
        PlayerDeck[38].status = 0;
        
        PlayerDeck[39].name = "Shanghai";
        PlayerDeck[39].color = 4;
        PlayerDeck[39].status = 0;
        
        PlayerDeck[40].name = "Hong Kong";
        PlayerDeck[40].color = 4;
        PlayerDeck[40].status = 0;
        
        PlayerDeck[41].name = "Taipei";
        PlayerDeck[41].color = 4;
        PlayerDeck[41].status = 0;
        
        PlayerDeck[42].name = "Osaka";
        PlayerDeck[42].color = 4;
        PlayerDeck[42].status = 0;
        
        PlayerDeck[43].name = "Bangkok";
        PlayerDeck[43].color = 4;
        PlayerDeck[43].status = 0;
        
        PlayerDeck[44].name = "Ho Chi Minh";
        PlayerDeck[44].color = 4;
        PlayerDeck[44].status = 0;
        
        PlayerDeck[45].name = "Manila";
        PlayerDeck[45].color = 4;
        PlayerDeck[45].status = 0;
        
        PlayerDeck[46].name = "Jakarta";
        PlayerDeck[46].color = 4;
        PlayerDeck[46].status = 0;
        
        PlayerDeck[47].name = "Sydney";
        PlayerDeck[47].color = 4;
        PlayerDeck[47].status = 0;
        
        PlayerDeck[48].name = "Epidemic";
        PlayerDeck[48].color = 0;
        PlayerDeck[48].status = 0;
        
        PlayerDeck[49].name = "Epidemic";
        PlayerDeck[49].color = 0;
        PlayerDeck[49].status = 0;
        
        PlayerDeck[50].name = "Epidemic";
        PlayerDeck[50].color = 0;
        PlayerDeck[50].status = 0;
        
        PlayerDeck[51].name = "Epidemic";
        PlayerDeck[51].color = 0;
        PlayerDeck[51].status = 0;
        
        PlayerDeck[52].name = "Epidemic";
        PlayerDeck[52].color = 0;
        PlayerDeck[52].status = 0;
        
        PlayerDeck[53].name = "Epidemic";
        PlayerDeck[53].color = 0;
        PlayerDeck[53].status = 0;
        
        PlayerDeck[54].name = "Government Grant"; //Add 1 research station to any city (no discared needed)
        PlayerDeck[54].color = 5;
        PlayerDeck[54].status = 0;
        
        PlayerDeck[55].name = "Airlift"; // Move any 1 player to any city. Get permission before moving another players pawn
        PlayerDeck[55].color = 5;
        PlayerDeck[55].status = 0;
        
        PlayerDeck[56].name = "Forcast"; // Draw, look at, and rearrange the top 6 cards of the infection deck. put them back on top
        PlayerDeck[56].color = 5;
        PlayerDeck[56].status = 0;
        
        PlayerDeck[57].name = "One Quiet Night"; // Skip the nect infect cities step (skip infection step)
        PlayerDeck[57].color = 5;
        PlayerDeck[57].status = 0;
        
        PlayerDeck[58].name = "Resilient Population"; // remove any 1 card in the infection discard pile from the game. You may play this between the infect and intensify steps of an epidemic
        PlayerDeck[58].color = 5;
        PlayerDeck[58].status = 0;
    }
};
