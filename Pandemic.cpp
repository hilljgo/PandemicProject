#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Player.h"
#include "City.h"
#include "Card.h"
#include "Disease.h"
using namespace std;

void randSP();
void save(int);
void infection();
void infect(City&, int);
void sitrep();
void epidemic();
void outbreak(City, int);
void draw(Player&, bool);
void discard(Player&);
const int MaxResearchStations = 6;
const int MaxInfectionCards = 48;        //one for each city
const int MaxPlayerCards = 59;                //48 city, 6 epidemic, 5 special event
int outbreaks;                        //Total outbreaks that have occurred
int infectionRate;                //Current rate of infections (how many infection cards are drawn)
int researchStations;        //Number of stations on the board
int numPlayers;



Disease diseases[5] = { Disease(), Disease("Blue"), Disease("Yellow"), Disease("Black"),Disease("Red") };
City earth[48];
Card InfecionDeck[MaxInfectionCards];
Card PlayerDeck[MaxPlayerCards];
Player players[4];


int main()
{
        srand(time(NULL));
        earth->cities(earth);
        InfecionDeck->iniInfectDeck(InfecionDeck);
        PlayerDeck->iniPlayerDeck(PlayerDeck);
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
        if( choice == 1 )
        {
                PlayerDeck[52].status = 3;
                PlayerDeck[53].status = 3;
        }
        else if( choice == 2 )
        {
                PlayerDeck[53].status = 3;
        }

                //Choose how many players
        choice = 0;
        cout << "How many players will play? (2-4) ";
        cin >> choice;
		numPlayers = choice;

        while ( choice != 2 && choice != 3 && choice != 4 )
        {
                cout << "Invalid choice, choose again.";
                cin >> choice;
        }
                //Give players their roles and non-epidemic player cards
        for(int i = 0; i < choice; i++)
        {
                players[i].color = (rand() % 7 + 1);
                players[i].currentCity = &earth[5];
                draw(players[i], true);
        }
        
            //// Randomly assigns Job / Special Ability
        randSP();
        
        choice = 0;

                //Initialize outbreak & infection rate
        outbreaks = 0;
        infectionRate = 2;
        researchStations = 1;

		
			
                //Initial infections
        for( int i = 0; i < 3; i++ )
        {
                int d;
                do
                {
                        d = rand() % MaxInfectionCards;
                }while( InfecionDeck[d].status != 0 );
                for( int j = 0; j < 3; j++ )
                {
                        infect(earth[d],InfecionDeck[d].color);
						InfecionDeck[d].status = 2;
						
						
                }
        }
        for( int i = 0; i < 3; i++ )
        {
                int d;
                do
                {
                        d = rand() % MaxInfectionCards;
                }while( InfecionDeck[d].status != 0 );
                for( int j = 0; j < 2; j++ )
                {
                        infect(earth[d],InfecionDeck[d].color);
						InfecionDeck[d].status = 2;
						
                }
        }
        for( int i = 0; i < 3; i++ )
        {
                int d;
                do
                {
                        d = rand() % MaxInfectionCards;
                }while( InfecionDeck[d].status != 0 );
                for( int j = 0; j < 1; j++ )
                {
                        infect(earth[d],InfecionDeck[d].color);
						InfecionDeck[d].status = 2;
						
                }
				
        }

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
                        bool showing[9];
                        for( int i = 0; i < 9; i++ )
                                showing[i] = false;
                        showing[0] = showing[8] = true;
                        
						//Display player's cards & location
                        cout << "\nPlayer " << p+1 << "'s cards in hand:\n";
                        for(int i = 0; i < 7; i++)
                        {
                                if( players[p].hand[i] && players[p].hand[i]->status == 1 )
                                        cout << players[p].hand[i]->name << endl;
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
                                if( players[p].hand[i] != NULL && (players[p].hand[i]->color > 0 && players[p].hand[i]->color < 5) )
                                        show = true;
                        }
                        if( show == true )
                        {
                                showing[1] = true;
                                cout << "2. Direct\n";
                        }
                        
                        show = false;
                        for( int i = 0; i < 7; i++ )
                        {
                                if( players[p].hand[i] && players[p].hand[i]->name == players[p].currentCity->name )
                                        show = true;
                        }
                        if( show == true )
                        {
                                showing[2] = true;
                                cout << "3. Charter\n";
                        }
                        
                        show = false;
                        if( players[p].currentCity->researchStation == true && researchStations > 1)
                                show = true;
                        if( show == true )
                        {
                                showing[3] = true;
                                cout << "4. Shuttle\n";
                        }
                        
                        show = false;
                        if( players[p].currentCity->researchStation == false )
                        {                                
                                for( int i = 0; i < 7; i++ )
                                {
                                        if( players[p].hand[i] && players[p].hand[i]->name == players[p].currentCity->name)
                                                show = true;
                                }
                        }
                        if( show == true )
                        {
                                showing[4] = true;
                                cout << "5. Build\n";
                        }

                        show = false;
                        if( players[p].currentCity->BlueCubes > 0 || players[p].currentCity->YellowCubes > 0 ||
                                players[p].currentCity->BlackCubes > 0 || players[p].currentCity->RedCubes)
                                show = true;
                        if( show == true )
                        {
                                showing[5] = true;
                                cout << "6. Treat\n";
                        }

                        show = false;
                        for( int k = 0; k < 7; k++ )
                        {
                                if( players[p].hand[k] && players[p].hand[k]->name == players[p].currentCity->name )
                                {
                                        for( int i = 0, j = 0; i < 4; i++ )
                                        {
                                                if( players[p].currentCity == players[i].currentCity )
                                                        j++;
                                                if( j > 1 )
                                                        show = true;
                                        }
                                        k = 7;
                                }
                        }
                        if( show == true )
                        {
                                showing[6] = true;
                                cout << "7. Share\n";
                        }

                        show = false;
                        if( players[p].currentCity->researchStation == true )
                        {
                                int blu = 0, yel = 0, bla = 0, red = 0;
                                for( int i = 0; i < 7; i++ )
                                {
                                        if( players[p].hand[i] )
                                        {
                                                switch (players[p].hand[i]->color)
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
                        }
                        if( show == true )
                        {
                                showing[7] = true;
                                cout << "8. Cure\n";
                        }

                        cout << "9. Pass\n0. Special Ability\nChoose a number:";

                        choice = 0;
                        do
                        {
                                cin >> choice;
                                if( showing[choice-1] == true )
                                {
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
                                                players[p].share(players, p);
                                                break;
                                        case 8:
                                                players[p].cure();
                                                break;
                                        case 9:
                                                players[p].pass();
                                                break;
                                        case 0:
                                        	players[p].special();
                                        	break;
                                        default:
                                                cout << "Invalid choice. Please choose again\n";
                                        }
                                }
                                else
                                {
                                        cout << "Invalid choice. Please choose again\n";
                                        choice = 100;
                                }
                        }while( choice == 100 );
                        //Check if all diseases are cured for a win.
                        end = true;
                        for( int i = 0; i < 5; i++ )
                        {
                                if( diseases[i].status == 1 )
                                        end = false;
                        }
                        if( end == true )
                        {
                                cout << "Congratulations!! You have found the cures for all of the diseases!\n";
                                cout << "YOU WIN!!\n";
                                return 0;
                        }
                }
                draw(players[p], false);
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
                int d;
                do
                {
                        d = rand() % MaxInfectionCards;
                        //if card status is "Discard", choose another
                }while( InfecionDeck[d].status != 0 );
                //place a cube on the city
                infect(earth[d],InfecionDeck[d].color);

                for (int j = 0; j < 48; j++)
                {
                        earth[j].outbreak = false;
                }
                //change card's status to "Discard"
                InfecionDeck[d].status = 2;
        }
}

void infect(City &city, int d)
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
        else if( (city.BlueCubes == 3 && d == 1) || (city.YellowCubes == 3 && d == 2)
                || (city.BlackCubes == 3 && d == 3) || (city.RedCubes == 3 && d == 4) )
        {
                //if 3 cubes already, outbreak to connected cities
                outbreak(city, d);
        }
        else
        {
                cout << city.name << " has been infected with the ";
                switch (d)
                {
                case 1:
                        city.BlueCubes++;
                        cout << "blue disease.\n";
                        break;
                case 2:
                        city.YellowCubes++;
                        cout << "yellow disease.\n";
                        break;
                case 3:
                        city.BlackCubes++;
                        cout << "black disease.\n";
                        break;
                case 4:
                        city.RedCubes++;
                        cout << "red disease.\n";
                        break;
                }

				

                diseases[d].cubes--;
                if( diseases[d].cubes <= 0 )
                {
                        cout << "The " << diseases[d].name << " Disease has spread too much."
                                << "You Lose.\n";
                        save(numPlayers);
						exit(0);
                }
        }
}

void outbreak(City city, int d)
{
        //outbreak can't chain cities that have outbreaked during current infection card
        if( city.outbreak == false )
        {
                city.outbreak = true;
                cout << "An outbreak occurs at " << city.name <<  "!\n";
                outbreaks++;
                if( outbreaks >= 8 )
                {
                        cout << "There have been too many outbreaks. You Lose.\n";
                        save(numPlayers);
						exit(0);
                }
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
        int d;
        do
        {
                d = rand() % MaxInfectionCards;
        }while( InfecionDeck[d].status != 0 );
        for( int i = 0; i < 3; i++ )
                infect(earth[d],InfecionDeck[d].color);
        for( int i = 0; i < MaxInfectionCards; i++ )
                InfecionDeck[i].status = 0;
}

void sitrep()
{
        cout << "\nCurrent situation of Earth:\n";
        cout << "List of cities + level of infection\n";
        for (int i = 0; i < 40; i ++)
                cout << '-';
        cout << endl;
        //goes through the city array
        //displays how many disease cubes on each city & if there is a Research Station there
        //needs >=1 cubes to be displayed.
        for (int i = 0; i < 48; i++)
        {
                if( earth[i].BlueCubes > 0 || earth[i].YellowCubes > 0
                        || earth[i].BlackCubes > 0 || earth[i].RedCubes > 0
                        || earth[i].researchStation == true)
                {
                        cout << earth[i].name << ": ";
                        if( earth[i].researchStation == true )
                                cout << " <-Research Station->\n";
                        else
                                cout << endl;
                        if( earth[i].BlueCubes > 0 )
                                cout << "\tBlue = " << earth[i].BlueCubes;
                        if( earth[i].YellowCubes > 0 )
                                cout << "\tYellow = " << earth[i].YellowCubes;
                        if( earth[i].BlackCubes > 0 )
                                cout << "\tBlack = " << earth[i].BlackCubes;
                        if( earth[i].RedCubes > 0 )
                                cout << "\tRed = " << earth[i].RedCubes;
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
        
void draw(Player &play, bool beginning) //Player draws 2 cards
{
                //If <2 cards in player deck, player's lose
        
                //Add two cards to player's hand
                        //If epidemic is drawn, discard it instead and do epidemic
                //If current hand is >7, player discards until 7
        for( int i = 0; i < 2; i++ )
        {
                int count = 0;
                for( int k = 0; k < MaxPlayerCards; k++ )
                {
                        if( PlayerDeck[k].status != 0 )
                                count++;
                }
                if( count == MaxPlayerCards )
                {
                        cout << "There are no more cards to draw. Time has run out. You Lose.\n";
                        save(numPlayers);
						exit(0);
                }

                for( int j = 0; j <= play.maxHand; j++ )
                {
                        if( play.hand[j] == NULL )
                        {
                                srand(time(NULL));
                                int d;
                                again:
                                do
                                {
                                        d = rand() % MaxPlayerCards;
                                }while( PlayerDeck[d].status != 0 );
                                if( PlayerDeck[d].color != 0 )
                                {
                                        play.hand[j] = &PlayerDeck[d];
                                        PlayerDeck[d].status++;
                                        if( !beginning )
                                                cout << "You drew a " << PlayerDeck[d].name << " Card\n";
                                        if( j == play.maxHand )
                                        {
                                                discard(play);
                                        }
                                        else if( !beginning )
                                                getchar();
                                }
                                else if( beginning )
                                        goto again;
                                else
                                {
                                        cout << "You drew an Epidemic Card.\n";
                                        epidemic();
                                        PlayerDeck[d].status = 2;
                                }
                                j = play.maxHand+1;
                        }
                }
        }
}

void discard(Player &play)
{
        int choice;
        cout << "You have too many cards in your hand.\n";
        for( int i = 0; i <= play.maxHand; i++ )
        {
                if( play.hand[i] )
                        cout << i+1 << ". " << play.hand[i]->name << endl;
        }
        choice = 100;
        do
        {
                cout << "Please choose a";
                if( choice == 10 )
                        cout << "nother";
                cout << " card to discard: ";
                cin >> choice;
                if( choice >= 1 && choice <= play.maxHand+1 )
                {
                        play.hand[choice-1]->status = 2;
                        play.hand[choice-1] = play.hand[play.maxHand];
                        play.hand[play.maxHand] = NULL;
                }
                else
                {
                        cout << "Invalid choice.\n";
                        choice = 10;
                }
        }while( choice == 10 );
}

void save(int numPlayers)
{
	ofstream saveFile;
						saveFile.open("save.txt");
						
						//saving number of players
						saveFile << "numPlayers = " << numPlayers << endl;
						


						//saving outbreaks
						saveFile << "outbreaks = " << outbreaks << endl;
						
						//saving infection rate
						saveFile << "infectionRate = " << infectionRate << endl;
						
						//saving research stations
						saveFile << "researchStations = " << researchStations << endl;
						
						//saving location
						for(int i = 0; i < numPlayers; i++)
						{
							saveFile << "Player " << i+1 <<  "at " << players[i].currentCity->name << endl;
						}
						
						//saving special ability
						for(int i = 0; i < numPlayers; i++)
						{
							saveFile << "Player " << i+1 << "specialAbility = " << players[i].specialAbility << endl;
						}

						//saving hands
						for(int i = 0; i < numPlayers; i++)
						{
							saveFile << "PLAYER" << i+1 << "'S HAND:" << endl;
							for(int x = 0; x < 2; x++)
							{
								saveFile << players[i].hand[x]->name << endl;
							}
						}
		
						saveFile << "RESEARCH STATIONS" << endl;
						for(int i = 0; i < 49; i++)
						{
							if(earth[i].researchStation == true)
							{
								saveFile << earth[i].name << endl;
							}
						}

						//total blue cubes
						
						saveFile << "Total Blue cubes: " << diseases[1].cubes << endl;
						//total yellow cubes 
						saveFile << "Total Yellow cubes: " <<  diseases[2].cubes << endl;
						//total black cubes
						saveFile << "Total Black cubes: " << diseases[3].cubes << endl;
						//total red cubes
						saveFile << "Total Red cubes: " << diseases[4].cubes << endl;
						
						//saving infection cubes
						saveFile << "NUMBER OF CUBES PER CITY" << endl;
						for(int i = 0; i < 48; i++)
						{
							
							saveFile << earth[i].name << " " << earth[i].BlackCubes << " " << earth[i].BlueCubes << " " << earth[i].RedCubes << " " << earth[i].YellowCubes << endl; 
							

							/*if(earth[i].BlackCubes >= 1)
							{
								
								saveFile << earth[i]. << " has " << earth[i].BlackCubes << " black cubes" << endl;
							}
							if(earth[i].RedCubes >= 1)
							{
								saveFile << earth[i].name << " has " << earth[i].RedCubes << " red cubes" << endl;
							}
							if(earth[i].BlueCubes >= 1)
							{
								saveFile << earth[i].name << " has " << earth[i].BlueCubes << " blue cubes" << endl;
							}
							if(earth[i].YellowCubes >= 1)
							{	
								saveFile << earth[i].name << " has " << earth[i].YellowCubes << " yellow cubes" << endl;
							}
							*/
						}
						saveFile << "INFECTION DECK STATUS'" << endl;
						//infection cards status'
						for(int i = 0; i < MaxInfectionCards; i++)
						{
							saveFile << InfecionDeck[i].status << endl;
						}

						saveFile << "PLAYER DECK STATUS" << endl;
						for(int i = 0; i < MaxPlayerCards; i++)
						{
							saveFile << PlayerDeck[i].status << endl;
						}




						saveFile.close();

}

void load()
{
	ifstream loadFile;
	loadFile.open("save.txt");
	int value;
	string cityName[4];
	

	while(!loadFile.eof())
	{
		loadFile >> value;
		numPlayers = value;
		
		loadFile >> value;
		outbreaks = value;
		
		loadFile >> value;
		infectionRate = value;
		
		//load each players current city names
		for(int i = 0; i < numPlayers; i++)
		{
			loadFile >> cityName[i];
		}

		//take string from file, search earth array for that name, set players currentCity to that city
		for(int i = 0; i < numPlayers; i++)
		{
			for(int j = 0; j < 48; j++)
			{
				if(cityName[i] == earth[j].name)
				{
					players[i].currentCity = &earth[j];
				}
			}
		}
		
		//loading each players special ability
		for(int i = 0; i < numPlayers; i++)
		{
			loadFile >> value;
			/**
			players[i].specialAbility = value;
			**/
		}

	}
}
void randSP(){
    players[1].specialAbility = rand() % 4 + 1; // random # 1-4
    
    do {
        players[2].specialAbility = rand() % 4 + 1; // random # 1-4
    }while(players[2].specialAbility == players[1].specialAbility); // reassign while p1 = p2
    
    
    do {
        players[3].specialAbility = rand() % 4 + 1; // random # 1-4
    } while ((players[3].specialAbility == players[2].specialAbility) &&
             (players[3].specialAbility == players[1].specialAbility));
    
    do {
        players[4].specialAbility = rand() % 4 + 1; // random # 1-4
    } while ((players[4].specialAbility == players[3].specialAbility) &&
             (players[4].specialAbility == players[2].specialAbility) &&
             (players[4].specialAbility == players[1].specialAbility));
}
