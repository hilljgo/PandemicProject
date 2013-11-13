#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "City.h"
#include "Card.h"
using namespace std;

void infection();
void infect(City, int);
void sitrep();
void epidemic();
void outbreak(City, int);
const int MaxResearchStations = 6;
const int MaxInfectionCards = 47;        //one for each city (counting from 0)
const int MaxPlayerCards = 58;                //48 city, 6 epidemic, 5 special event (counting from 0)
int outbreaks;                        //Total outbreaks that have occurred
int infectionRate;                //Current rate of infections (how many infection cards are drawn)
int researchStations;        //Number of stations on the board



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

Disease diseases[5] = { Disease(), Disease("Blue"), Disease("Yellow"), Disease("Black"),Disease("Red") };
City earth[48];
Card InfectionDeck[MaxInfectionCards];
Card PlayerDeck[MaxPlayerCards];
Player players[4];


int main()
{
        unsigned seed = time(0);
        srand(seed);

        int choice = 0;
#pragma region Set
        //Initial set-up
                //Choose difficulty (4,5,6 Epidemic cards in player deck)
        cout << "Choose your difficulty:\n";
        cout << "1. Easy\n2. Medium\n3. Hard\n";
        cin >> choice;
        while ( choice != 1 && choice != 2 && choice != 3 )
        {
                cout << "Invalid choice, choose again.";
                cin >> choice;
        }
                //Set the deck with 4,5,6 epidemic cards
                //---NEED PLAYER DECK ARRAY---

                //Choose how many players
        choice = 0;
        cout << "How many players will play? (1-4) ";
        cin >> choice;
        while ( choice != 2 && choice != 3 && choice != 4 )
        {
                cout << "Invalid choice, choose again.";
                cin >> choice;
        }
                //Give players their roles and non-epidemic player cards
                //---NEED PLAYER DECK ARRAY---
        for(int i = 0; i < choice; i++)
        {
                players[i].color = (1 + rand() % 7);
                players[i].currentCity = &earth[5];
        }

        choice = 0;

#pragma region Earth
                //Initialize cities + connections

        //Blue Cities 0-11
        earth[0].name = "San Fransisco";
        earth[0].connectOne = &earth[1]; // Chicago
        earth[0].connectTwo = &earth[12]; // Los Angeles
        earth[0].connectThree = &earth[45]; // Manila
        earth[0].connectFour = &earth[38];  // Tokyo

        earth[1].name = "Chicago";
        earth[1].connectOne = &earth[2]; // Montreal
        earth[1].connectTwo = &earth[5]; // Atlanta
        earth[1].connectThree = &earth[13]; // Mexico City
        earth[1].connectFour = &earth[12]; // LA
        earth[1].connectFive = &earth[0]; // SF

        earth[2].name = "Montreal";
        earth[2].connectOne = &earth[4]; // Washington
        earth[2].connectTwo = &earth[14]; // Miami
        earth[2].connectThree = &earth[1]; // Chicago

        earth[3].name = "New York";
        earth[3].connectOne = &earth[3]; // New York
        earth[3].connectTwo = &earth[4]; // Washington
        earth[3].connectThree = &earth[1]; // Chicago
        
        earth[4].name = "Washington";
        earth[4].connectOne = &earth[3]; // New York
        earth[4].connectTwo = &earth[14]; // Miami
        earth[4].connectThree = &earth[5]; // Atlanta
        earth[4].connectFour = &earth[2]; // Montreal
        
        earth[5].name = "Atlanta";
        earth[5].connectOne = &earth[6]; // London
        earth[5].connectTwo = &earth[7]; // Madrid
        earth[5].connectThree = &earth[4]; // Washington
        earth[5].connectFour = &earth[2]; // Montreal
        earth[5].researchStation = true;
        
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
        earth[10].connectThree = &earth[9]; // Essen

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

#pragma endregion was built in 7 days

                //Initialize outbreak & infection rate
        outbreaks = 0;
        infectionRate = 2;
        researchStations = 1;
                //Initial infections
                //---NEED INFECTION DECK ARRAY
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


		//**INITIALIZE PLAYER DECK**



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

		

#pragma endregion Up

                //start game
        cout << "Game start!\n";
        getchar();
        sitrep();
        getchar();

        bool end = false;
        int p = -1;
        //Loop of players playing until a win or loss
        
		//deal cards
		
		while(end == false)
        {
                //Loop for one player's turn until actions run out
                if( players[p+1].color > 0 )
                        p++;
                else
                        p = 0;
                
                players[p].actions = 4;
                while( players[p].actions > 0 )
                {
                        //Display player's cards & location
                        cout << "\nPlayer " << p+1 << "'s cards in hand:\n";
                        for(int i = 0; i < 7; i++)
                        {
                                if( players[p].hand[i].status == 2 )
                                        cout << players[p].hand[i].name << endl;
                        }
                        cout << "\nPlayer " << p+1 << "'s location: " << players[p].currentCity->name;
                        cout << "\nPlayer " << p+1 << " has " << players[p].actions << " action(s) left.\n\n";

                        //display available actions (drive/ferry, flights, others)
                                //actions that the player can't do will not be displayed
                                //(ex. charter flight not shown if player does not have current city card)

                        cout << "1. Move\n";
                        
                        bool show = false;
                        for( int i = 0; i < 7; i++ )
                        {
                                if( players[p].hand[i].status == 2 )
                                        show = true;
                        }
                        if( show == true )
                                cout << "2. Direct\n";
                        
                        show = false;
                        for( int i = 0; i < 7; i++ )
                        {
                                if( players[p].hand[i].name == players[p].currentCity->name )
                                        show = true;
                        }
                        if( show == true )
                                cout << "3. Charter\n";
                        
                        show = false;
                        if( players[p].currentCity->researchStation == true && researchStations > 1)
                                show = true;
                        if( show == true )
                                cout << "4. Shuttle\n";
                        
                        show = false;
                        if( players[p].currentCity->researchStation == false )
                        {                                
                                for( int i = 0; i < 7; i++ )
                                {
                                        if( players[p].hand[i].name == players[p].currentCity->name)
                                                show = true;
                                }
                        }
                        if( show == true )
                                cout << "5. Build\n";

                        show = false;
                        if( players[p].currentCity->cubes > 0 )
                                show = true;
                        if( show == true )
                                cout << "6. Treat\n";

                        show = false;
                        for( int i = 0, j = 0; i < 4; i++ )
                        {
                                if( players[p].currentCity == players[i].currentCity )
                                        j++;
                                if( j > 1 )
                                        show = true;
                        }
                        if( show == true )
                                cout << "7. Share\n";

                        show = false;
                        if( players[p].currentCity->researchStation == true )
                        {
                                int blu = 0, yel = 0, bla = 0, red = 0;
                                for( int i = 0; i < 7; i++ )
                                {
                                        switch (players[p].hand[i].color)
                                        {
                                        case 1:
                                                blu++;
                                                break;
                                        case 2:
                                                yel++;
                                                break;
                                        case 3:
                                                bla++;
                                                break;
                                        case 4:
                                                red++;
                                                break;
                                        default:
                                                ;
                                        }
                                        if( blu >= 5 || yel >= 5 || bla >= 5 || red >= 5 )
                                                show = true;
                                }
                        }
                        if( show == true )
                                cout << "8. Cure\n";

                        cout << "9. Pass\nChoose a number.";

                        choice = 0;
                        do
                        {
                                cin >> choice;
                                switch (choice)
                                {
                                case 1:
                                        players[p].move();
                                        break;
                                case 2:
                                        players[p].direct();
                                        break;
                                case 3:
                                        players[p].charter();
                                        break;
                                case 4:
                                        players[p].shuttle();
                                        break;
                                case 5:
                                        players[p].build();
                                        break;
                                case 6:
                                        players[p].treat();
                                        break;
                                case 7:
                                        players[p].share();
                                        break;
                                case 8:
                                        players[p].cure();
                                        break;
                                case 9:
                                        players[p].pass();
                                        break;
                                default:
                                        cout << "Invalid choice. Please choose again\n";
                                }
                        }while( choice != 1 && choice != 2 && choice != 3 &&
                                        choice != 4 && choice != 5 && choice != 6 && 
                                        choice != 7 && choice != 8 && choice != 9 );
                }
                players[p].draw();
                infection();
        }
        
        return 0;
}

void infection()
{
        //draws (infection rate) infection cards
        for (int i = 0; i < infectionRate; i++)
        {
                //Random choice in Card array
                //---NEED INFECTION DECK ARRAY---
                        //if card status is "Discard", choose another
                int c = 0; // City number matching the card, 0 for now
                int d = 0; // Color of city&card, 0 for now
                //place a cube on the city
                infect(earth[c], d);

                for (int j = 0; j < 48; j++)
                {
                        earth[j].outbreak = false;
                }
                //change card's status to "Discard"(3)
                //---NEED INFECTION DECK ARRAY---
        }
}

void infect(City city, int d)
{
        if ( diseases[d].status == 3 )
        {
                //if deasease is eradicated, do nothing
                cout << "No spread of ";
                if ( d == 1 )
                        cout << "blue";
                else if (d == 2)
                        cout << "yellow";
                else if (d == 3)
                        cout << "black";
                else
                        cout << "red";
                cout << " disease because the disease is eradicated!";
        }
        else if( city.cubes == 3 )
        {
                //if 3 cubes already, outbreak to connected cities
                outbreak(city, d);
        }
        else
        {
                cout << city.name << " becomes "; 
                if( city.cubes > 0 )
                        cout << "more ";
                cout << "infected.";
                city.cubes += 1;
        }
}

void outbreak(City city, int d)
{
        //outbreak can't chain cities that have outbreaked during current infection card
        if( city.outbreak == false )
        {
                city.outbreak = true;
                cout << "An outbreak occurs at " << city.name <<  "!\n";
                infect(*city.connectOne, d);
                if (city.connectTwo)
                        infect(*city.connectTwo, d);
                if (city.connectThree)
                        infect(*city.connectThree, d);
                if (city.connectFour)
                        infect(*city.connectFour, d);
                if (city.connectFive)
                        infect(*city.connectFive, d);
        }
        //a city can gain multiple cubes from a single outbreak chain
}

void epidemic()
{
        infectionRate++;
        //Infect a random city and reshuffle Infection deck
        //NEED INFECTION DECK ARRAY
}

void sitrep()
{
        cout << "Current situation of Earth:\n";
        cout << "List of cities + level of infection\n";
        for (int i = 0; i < 40; i ++)
                cout << '-';
        cout << endl;
        //goes through the city array
        //displays how many disease cubes on each city & if there is a Research Station there
        //needs >=1 cubes to be displayed.
        for (int i = 0; i < 48; i++)
        {
                if( earth[i].cubes > 0 || earth[i].researchStation == true)
                {
                        cout << earth[i].name << ": " << earth[i].cubes;
                        if( earth[i].researchStation == true )
                                cout << " <-Research Station->\n";
                        else
                                cout << endl;
                }
        }
        //Display Player Locations
        for( int i = 0; i < 4; i++ )
        {
                if( players[i].color > 0 )
                        cout << "\nPlayer " << i+1 << " is at " << players[i].currentCity->name;
        }
}