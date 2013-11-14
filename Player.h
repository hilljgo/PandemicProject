#include <iostream>
#include <string>
#include "City.h"
#include "Card.h"
using namespace std;

class Player
{
public:
	int color;				//Which role this player is
	int actions;			//How many actions this player has left
	const int maxActions = 4;
	Card hand[7];			//Cards in this player's hand
	const int maxHand = 7;
	City *currentCity;		//City this player is in
    
	//may add parameters for actions
    
	Player()
	{
		color = 0; //should be assigned randomly
		actions = 4;
		currentCity = NULL; //should be assigned to Atlanta via main
	}
    
	//moves player to connecting city
	void move()
	{
		//Always shown
        
		cout << "Available cities to drive/ferry to:/n";
		cout << "1. " << currentCity->connectOne << endl;
		if( currentCity->connectTwo )
			cout << "2. " << currentCity->connectTwo << endl;
		if( currentCity->connectThree )
			cout << "3. " << currentCity->connectThree << endl;
		if( currentCity->connectFour )
			cout << "4. " << currentCity->connectFour << endl;
		if( currentCity->connectFive )
			cout << "5. " << currentCity->connectFive << endl;
		int n;
		cout << "City number to move to/n";
		cin >> n;
		//Statements to make current city the appropriate city & decrease actions
		//0 should go back to initial player action menu without decreasing
	}
	
	void direct(City earth[48])//Player discards city card to go to that city
	{
        int city; // city to fly to
        
		//Not shown if player has no city cards in hand
        
		//display available cities player can fly to
        //warn player that they will discard the coresponding city card
        cout << "Available Cities to Directly Fly to "
        << "[Direct Flights Remove City Card From Hand] : " << endl;
        
        //goes through hand
        for (int i = 0; i < maxHand; i++)
            // displays only city cards
            if (hand[i].color != 0 || hand[i].color != 5)
                cout << "  [" << i+1 << "]  " << hand[i].name << endl;
		//player chooses a number
        cout << "\nChoose City [#] or 0 to go back to action menu : ";
        cin >> city;
        
		//change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << hand[city-1].name << endl;
            
///Have to change because hand array becomes pointers
            hand[city-1].status = 2; // marks card as discarded
            
            for (int i = 0; i < 48; i++) {
                if(hand[city-1].name == earth[i].name)
                    currentCity = &earth[i];
            }
            actions--;
        }
        
	}
	
	void charter(City earth[48])//Player discards current city card to go to any city
	{
        int city;
		//Not shown if player does not have current city card
        cout << "Charter a flight to a city by discarding current city card "
        << "[City card will be discarded from hand]: " << endl;
        
		//display all cities
        for (int i = 0; i < 48; i++) {
            cout << '[' << i+1 << ']' << earth[i].name << endl;
            if (i == 11 || i == 23 || i == 35)
                cout << endl;
        }
        
		//player chooses which
        cout << "\nEnter # or 0 to go back to action menu: ";
        cin >> city;
        
		//change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << earth[city-1].name << endl;
//tweak to handle hand pointers
            currentCity = &earth[city-1];
            for( int i = 0; i < 7; i++ )
			{
				if( hand[i].name == currentCity->name )
					cout << "something" << endl;
			}
            actions--;
        }
        
	}
	
	void shuttle(City earth[48])//If research station in current city, moves player to another research station
	{
        int stations[6]; // tracks stations city #
        int city; // player's choice
        int a = 0; // counter for research stations
        
		//Not shown if current city does not have a research station
        cout << "Shuttle from one research station to another: " << endl;
        
		//display all other cities with research stations
        for(int i = 0; i < 48; i++)
            if (earth[i].researchStation == true){
                cout << '[' << i+1 << ']' << earth[i].name << endl;
                stations[a] = i;
                a++;
            }
		//player chooses a number
        cout << "Enter # or 0 to go back to actions menu: ";
        cin >> city;
        
		//change current city & decrease actions or go back to actions menu
        if (city != 0){
            cout << "\n Flying From " << currentCity->name << " to " << earth[stations[city-1]].name << endl;
            
            currentCity = &earth[stations[city-1]];
            actions--;
        }
	}
	
	void build()//Builds a research station in current city
	{
		//Not shown if research station already built
        
		//Display current cities with research stations
		//Yes or no to build one in current city
		//Change city's researchStation to true
		//If researchStations = 6, let player choose another research station to remove
		//decrease actions or back to actions menu
	}
	
	void treat()//Removes disease cube from current city
	{
		//Not shown if no disease cubes on current city
        
		//Display current city's infection level of each disease
		//Choose number to remove one or all (if cured) cube(s) of disease
		//decrease actions or back to actions menu
	}
	
	void share()//Give or take a current city card to/from another player in the same city
	{
		//Not shown if no other players in current city
        
		//Display give or take if able to
        //Player chooses which
		//Display available cards to give/take
        //Player chooses
        //If current hand is >7, player chooses to discard until 7
		//Decrease actions or back to actions menu
	}
	
	void cure()//Player discards 5 same color cards to cure disease of same color
	{
		//Show if on a research station AND >=5 same color city cards AND disease is still live
        
		//warn player that they will discard 5 cards
        //if >5 same color city cards, player chooses which to keep
		//change color's disease to cured
		//Decrease actions or back to actions menu
        
	}
	
	void pass()//Player does nothing for an action
	{
		//Always shown
		
		//player confirmation
		//decrease actions or back to actions menu
	}
	
	//Maybe put this in main to make it easier to epidemic?
	void draw() //Player draws 2 cards
	{
		//If <2 cards in player deck, player's lose
        
		//Add two cards to player's hand
        //If epidemic is drawn, discard it instead and do epidemic
		//If current hand is >7, player discards until 7
	}
};
