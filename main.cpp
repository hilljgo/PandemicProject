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
    
    //Initialize cities + connections & cards
    
    earth->cities(earth);
    InfecionDeck->iniInfectDeck(InfecionDeck);
    PlayerDeck->iniPlayerDeck(PlayerDeck);
    
	int choice = 0;
/*
// Display connections of cities
 
    for (int i = 0; i < 48; i++){
        cout << endl;
        
        cout << earth[i].name << ":\n" << earth[i].connectOne->name << endl;
        
        if(earth[i].connectTwo)
            cout << earth[i].connectTwo->name << endl;
       
        if(earth[i].connectThree)
            cout << earth[i].connectThree->name << endl;
        
        if(earth[i].connectFour)
            cout << earth[i].connectFour->name << endl;
        
        if(earth[i].connectFive)
            cout << earth[i].connectFive->name << endl;
        
        if(earth[i].connectSix)
            cout << earth[i].connectSix->name << endl;
        
        cout<<endl;
    }
*/
    
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
	cout << "How many players will play? (2-4) ";
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
    
#pragma endregion was built in 7 days
    
    //Initialize outbreak & infection rate
	outbreaks = 0;
	infectionRate = 2;
	researchStations = 1;
    earth[5].researchStation = true;
    
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
				if( players[p].hand[i].color == 1 || players[p].hand[i].color == 2
                   || players[p].hand[i].color == 3 || players[p].hand[i].color == 4 )
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
            
			cout << "9. Pass\nChoose a number: ";
            
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
                        players[p].direct(earth);
                        break;
                    case 3:
                        players[p].charter(earth);
                        break;
                    case 4:
                        players[p].shuttle(earth);
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