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
const int MaxInfectionCards = 48;	//one for each city
const int MaxPlayerCards = 59;		//48 city, 6 epidemic, 5 special event
int outbreaks;			//Total outbreaks that have occurred
int infectionRate;		//Current rate of infections (how many infection cards are drawn)
int researchStations;	//Number of stations on the board



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
Card InfecionDeck[MaxInfectionCards];
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

#pragma endregion Up

		//start game
	cout << "Game start!\n";
	getchar();
	sitrep();
	getchar();

	bool end = false;
	int p = -1;
	//Loop of players playing until a win or loss
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